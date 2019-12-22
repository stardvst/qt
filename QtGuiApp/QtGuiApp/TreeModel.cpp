#include "TreeModel.h"

#include "TreeItem.h"

TreeModel::TreeModel(QObject *parent /* = nullptr */)
	: QAbstractItemModel(parent)
{
	const auto rootData = QVector<QVariant>{} << "Number" << "Data";
	m_pRootItem = new TreeItem{ rootData };

	// only place to add data to model
	setupModelData();
}

TreeModel::~TreeModel()
{
	delete m_pRootItem;
}

QModelIndex TreeModel::index(const int row, const int column, const QModelIndex &parent /* = QModelIndex() */) const
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex{};

	const auto parentItem = getItem(parent);
	if (const auto childItem = parentItem->child(row))
		return createIndex(row, column, childItem);

	return QModelIndex{};
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex{};

	const auto childItem = getItem(index);
	const auto parentItem = childItem->parentItem();

	// don't return a model index corresponding to the root item
	if (parentItem == m_pRootItem)
		return QModelIndex{};

	return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent /* = QModelIndex() */) const
{
	const auto parentItem = getItem(parent);
	return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent /* = QModelIndex() */) const
{
	// all items have the same number of columns
	return m_pRootItem->columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, const int role /* = Qt::DisplayRole */) const
{
	if (!index.isValid())
		return QVariant{};

	if (role != Qt::DisplayRole)
		return QVariant{};

	const auto item = static_cast<TreeItem *>(index.internalPointer());
	return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QVariant TreeModel::headerData(const int section, const Qt::Orientation orientation, const int role /* = Qt::DisplayRole */) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return m_pRootItem->data(section);

	return QVariant{};
}

void TreeModel::setupModelData() const
{
	auto parent = m_pRootItem;
	parent->insertRows(parent->childCount(), 1, parent->columnCount());
	const auto itemOne = parent->child(parent->childCount() - 1);
	itemOne->setData(0, 1);
	itemOne->setData(1, "First item");

	parent = itemOne;
	parent->insertRows(parent->childCount(), 1, parent->columnCount());
	const auto itemTwo = parent->child(parent->childCount() - 1);
	itemTwo->setData(0, 2);
	itemTwo->setData(1, "Second item");

	parent = itemTwo;
	parent->insertRows(parent->childCount(), 1, parent->columnCount());
	const auto itemThree = parent->child(parent->childCount() - 1);
	itemThree->setData(0, 3);
	itemThree->setData(1, "Third item");

	parent = m_pRootItem;
	parent->insertRows(parent->childCount(), 1, parent->columnCount());
	const auto itemFour = parent->child(parent->childCount() - 1);
	itemFour->setData(0, 4);
	itemFour->setData(1, "Fourth item");

	parent = itemFour;
	parent->insertRows(parent->childCount(), 1, parent->columnCount());
	const auto itemFive = parent->child(parent->childCount() - 1);
	itemFive->setData(0, QString::fromStdString(std::string(100, 'a') + "\naaa"));
	itemFive->setData(1, "Fifth item");
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role /* = Qt::EditRole */)
{
	if (role != Qt::EditRole)
		return false;

	auto item = getItem(index);
	const auto result = item->setData(index.column(), value);
	if (result)
		emit dataChanged(index, index);

	return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
	const QVariant &value, int role)
{
	if (role != Qt::EditRole || orientation != Qt::Horizontal)
		return false;

	const auto result = m_pRootItem->setData(section, value);
	if (result)
		emit headerDataChanged(orientation, section, section);

	return result;
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
	if (index.isValid())
	{
		if (const auto item = static_cast<TreeItem *>(index.internalPointer()))
			return item;
	}

	return m_pRootItem;
}

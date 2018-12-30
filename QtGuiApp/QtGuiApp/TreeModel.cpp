#include "TreeModel.h"

#include "TreeItem.h"

TreeModel::TreeModel(QObject *parent /* = nullptr */)
	: QAbstractItemModel(parent)
{
	const auto rootData = QList<QVariant>{} << "Number";
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
	if (!hasIndex(row, column, parent))
		return QModelIndex{};

	// the parent item pointer
	const auto parentItem = !parent.isValid()
		? m_pRootItem
		: static_cast<TreeItem *>(parent.internalPointer());

	// the child item pointer
	if (const auto childItem = parentItem->child(row))
		return createIndex(row, column, childItem);

	return QModelIndex{};
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex{};

	const auto childItem = static_cast<TreeItem *>(index.internalPointer());
	const auto parentItem = childItem->parentItem();

	// don't return a model index corresponding to the root item
	if (parentItem == m_pRootItem)
		return QModelIndex{};

	return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent /* = QModelIndex() */) const
{
	if (parent.column() > 0)
		return 0;

	const auto parentItem = !parent.isValid()
		? m_pRootItem
		: static_cast<TreeItem *>(parent.internalPointer());

	return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent /* = QModelIndex() */) const
{
	if (parent.isValid())
		return static_cast<TreeItem *>(parent.internalPointer())->columnCount();

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

	return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(const int section, const Qt::Orientation orientation, const int role /* = Qt::DisplayRole */) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return m_pRootItem->data(section);

	return QVariant{};
}

void TreeModel::setupModelData() const
{
	const auto itemOne = new TreeItem({ 1 }, m_pRootItem);
	m_pRootItem->appendChild(itemOne);

	const auto itemTwo = new TreeItem({ 2 }, itemOne);
	itemOne->appendChild(itemTwo);

	const auto itemThree = new TreeItem({ 3 }, itemTwo);
	itemTwo->appendChild(itemThree);

	const auto itemFour = new TreeItem({ 4 }, m_pRootItem);
	m_pRootItem->appendChild(itemFour);

	const auto itemFive = new TreeItem({ 5 }, itemFour);
	itemFour->appendChild(itemFive);
}

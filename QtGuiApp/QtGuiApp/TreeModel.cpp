#include "TreeModel.h"

#include "TreeItem.h"

TreeModel::TreeModel(const QString &data, QObject *parent /* = nullptr */)
	: QAbstractItemModel(parent)
{
	const auto rootData = QList<QVariant>{} << "Title" << "Summary";
	m_pRootItem = new TreeItem{ rootData };

	// only place to add data to model
	setupModelData(data.split(QStringLiteral("\n" )), m_pRootItem);
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

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
	auto parents = QList<TreeItem*>{} << parent;
	auto indentations = QList<int>{} << 0;;

	auto number = 0;

	while (number < lines.count()) {
		auto position = 0;
		while (position < lines[number].length())
		{
			if (lines[number].at(position) != ' ')
				break;
			position++;
		}

		const auto lineData = lines[number].mid(position).trimmed();
		if (!lineData.isEmpty())
		{
			// Read the column data from the rest of the line
			const auto columnStrings = lineData.split(QStringLiteral("\t"), QString::SkipEmptyParts);
			QList<QVariant> columnData;
			for (auto column = 0; column < columnStrings.count(); ++column)
				columnData << columnStrings[column];

			if (position > indentations.last())
			{
				// The last child of the current parent is now the new parent
				// unless the current parent has no children
				if (parents.last()->childCount())
				{
					parents << parents.last()->child(parents.last()->childCount() - 1);
					indentations << position;
				}
			}
			else {
				while (position < indentations.last() && !parents.isEmpty()) {
					parents.pop_back();
					indentations.pop_back();
				}
			}

			// Append a new item to the current parent's list of children
			parents.last()->appendChild(new TreeItem(columnData, parents.last()));
		}

		++number;
	}
}
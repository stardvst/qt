#include "TreeItem.h"
#include <utility>

TreeItem::TreeItem(QVector<QVariant> data, TreeItem *parent /* = nullptr */)
	: m_itemData(std::move(data))
	, m_parentItem(parent)
{
}

TreeItem::~TreeItem()
{
	qDeleteAll(m_childItems);
}

TreeItem *TreeItem::child(const int row) const
{
	return m_childItems.value(row);
}

int TreeItem::childCount() const
{
	return m_childItems.count();
}

int TreeItem::row() const
{
	if (m_parentItem)
		return m_parentItem->m_childItems.indexOf(const_cast<TreeItem *>(this));
		
	return 0;
}

int TreeItem::columnCount() const
{
	return m_itemData.count();
}

QVariant TreeItem::data(const int column) const
{
	return m_itemData.value(column);
}

TreeItem *TreeItem::parentItem() const
{
	return m_parentItem;
}

bool TreeItem::setData(const int column, const QVariant &value)
{
	return column >= 0 && column < m_itemData.size() && (m_itemData[column] = value, true);
}

bool TreeItem::insertRows(const int position, const int count, const int columns)
{
	if (position < 0 || position > m_childItems.size())
		return false;

	for (auto row = 0; row < count; ++row)
	{
		// create a new row with columns number of columns
		const QVector<QVariant> newData(columns);
		m_childItems.insert(position, new TreeItem{ newData, this });
	}

	return true;
}

bool TreeItem::removeRows(const int position, const int count)
{
	if (position < 0 || position > m_itemData.size())
		return false;

	for (auto row = 0; row < count; ++row)
		delete m_childItems.takeAt(position);

	return true;
}

bool TreeItem::insertColumns(const int position, const int columns)
{
	if (position < 0 || position > m_childItems.size())
		return false;

	for (auto column = 0; column < columns; ++column)
		m_itemData.insert(position, QVariant{});

	for (auto child : m_childItems)
		child->insertColumns(position, columns);

	return true;
}

bool TreeItem::removeColumns(const int position, const int columns)
{
	if (position < 0 || position > m_childItems.size())
		return false;

	for (auto column = 0; column < columns; ++column)
		m_itemData.remove(position);

	for (auto child : m_childItems)
		child->removeColumns(position, columns);

	return true;
}

#include "TreeItem.h"
#include <utility>

TreeItem::TreeItem(QList<QVariant> data, TreeItem *parent /* = nullptr */)
	: m_itemData(std::move(data))
	, m_parentItem(parent)
{
}

TreeItem::~TreeItem()
{
	qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *child)
{
	m_childItems.append(child);
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

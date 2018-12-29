#pragma once

#include <QVariant>

class TreeItem
{
public:
	explicit TreeItem(QList<QVariant> data, TreeItem *parent = nullptr);
	~TreeItem();

	void appendChild(TreeItem *child);

	TreeItem *child(int row) const;
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	int row() const;
	TreeItem *parentItem() const;

private:
	QList<TreeItem *> m_childItems;
	QList<QVariant> m_itemData;
	TreeItem *m_parentItem = nullptr;
};

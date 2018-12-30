#pragma once

#include <QVariant>
#include <QVector>

class TreeItem
{
public:
	explicit TreeItem(QVector<QVariant> data, TreeItem *parent = nullptr);
	~TreeItem();

	bool insertRows(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	bool removeRows(int position, int count);
	bool removeColumns(int position, int columns);

	TreeItem *child(int row) const;
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	int row() const;
	int column() const;
	TreeItem *parentItem() const;

	bool setData(int column, const QVariant &value);

private:
	QList<TreeItem *> m_childItems;
	QVector<QVariant> m_itemData;
	TreeItem *m_parentItem = nullptr;
};

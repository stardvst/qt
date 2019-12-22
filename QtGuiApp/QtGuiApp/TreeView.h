#pragma once

#include <QTreeView>

class TreeModel;

class TreeView : public QTreeView
{
public:
	explicit TreeView(QWidget *parent = nullptr) noexcept;

	void setModel(QAbstractItemModel *model) override;

private slots:
	void onItemExpanded(const QModelIndex &index);

private:
	TreeModel *m_pTreeModel = nullptr;
};

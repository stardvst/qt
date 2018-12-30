#pragma once

#include <QAbstractItemModel>

class TreeItem;

/*
 * A read-only tree model
 */
class TreeModel final : public QAbstractItemModel
{
	Q_OBJECT
public:
	explicit TreeModel(QObject *parent = nullptr);
	TreeModel(const TreeModel &other) = delete;
	TreeModel &operator=(const TreeModel &other) = delete;
	TreeModel(TreeModel &&other) = delete;
	TreeModel &operator=(TreeModel &&other) = delete;
	~TreeModel() override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &index) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	// implement to make the model editable
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
	bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

	//// allow the model to change the dimensions
	//bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
	//bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
	//bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
	//bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

private:
	void setupModelData() const;
	TreeItem *getItem(const QModelIndex &index) const;

	TreeItem *m_pRootItem{};
};

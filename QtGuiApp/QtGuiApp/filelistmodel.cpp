#include "filelistmodel.h"

#include <QApplication>
#include <QBrush>
#include <QDir>
#include <QPalette>

FileListModel::FileListModel(QObject *parent)
	: QAbstractListModel(parent)
{
}

int FileListModel::rowCount(const QModelIndex & /* parent */) const
{
	return fileCount;
}

QVariant FileListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= fileList.size() || index.row() < 0)
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		return fileList.at(index.row());
	}
	else if (role == Qt::BackgroundRole)
	{
		int batch = (index.row() / 20) % 2;
		if (batch == 0)
			return qApp->palette().base();
		else
			return qApp->palette().alternateBase();
	}
	return QVariant();
}

bool FileListModel::canFetchMore(const QModelIndex &index) const
{
	if (index.isValid())
		return false;

	return fileCount < fileList.size();
}

void FileListModel::fetchMore(const QModelIndex & /* index */)
{
	int remainder = fileList.size() - fileCount;
	int itemsToFetch = qMin(20, remainder);

	if (itemsToFetch <= 0)
		return;

	beginInsertRows(QModelIndex(), fileCount, fileCount + itemsToFetch - 1);

	fileCount += itemsToFetch;

	endInsertRows();

	emit numberPopulated(itemsToFetch);
}

void FileListModel::setDirPath(const QString &path)
{
	QDir dir(path);

	beginResetModel();
	fileList = dir.entryList();
	fileCount = 0;
	endResetModel();
}
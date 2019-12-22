#pragma once

#include <QThread>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class queryExecutor : public QObject
{
	Q_OBJECT
public:
	explicit queryExecutor(QObject *parent = nullptr) noexcept;

	void setDatabase(const QString &sDbPath);

public slots:
	void execute(const QString &query, const QHash<QString, QString> &mapBoundVals);

signals:
	void finished(bool success, const QList<QSqlRecord> &records);

private:
	QSqlDatabase m_db;
};

class QueryThread : public QThread
{
	Q_OBJECT
public:
	explicit QueryThread(const QString &sDbPath) noexcept;

protected:
	void run() override;

signals:
	void queryFinished(bool success, const QList<QSqlRecord> &records);

public slots:
	void execute(const QString &query, const QHash<QString, QString> &mapBoundVals);

private:
	queryExecutor m_queryExecutor;
	QString m_sDbPath;
};
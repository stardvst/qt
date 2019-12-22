#include "Thread.h"

#include <QSqlRecord>

queryExecutor::queryExecutor(QObject *parent /* = nullptr */) noexcept
{
}

void queryExecutor::setDatabase(const QString &sDbPath)
{
	// create a thread-specific connection
	m_db = QSqlDatabase::addDatabase("QSQLITE", QString("%1_%2")
		.arg(sDbPath)
		.arg(QString::number((quint64)QThread::currentThreadId(), 16)));

	qDebug() << "conn name" << QString("%1_%2")
		.arg(sDbPath)
		.arg(QString::number((quint64)QThread::currentThreadId(), 16));

	m_db.setDatabaseName(sDbPath);

	if (!m_db.open())
	{
		qDebug() << "db not open:" << m_db.lastError().text();
	}
}

void queryExecutor::execute(const QString &query, const QHash<QString, QString> &mapBoundVals)
{
	QList<QSqlRecord> records;
	QSqlQuery sqlQuery(m_db);
	sqlQuery.prepare(query);

	for (const auto &sPlaceholder : mapBoundVals.keys())
	{
		auto bound = mapBoundVals[sPlaceholder];
		sqlQuery.bindValue(sPlaceholder, bound);
	}

	if (!sqlQuery.exec())
	{
		qDebug() << "query failed:" << sqlQuery.lastError().text();
		emit finished(false, records);
		return;
	}

	while (sqlQuery.next())
		records.push_back(sqlQuery.record());

	emit finished(true, records);
}

QueryThread::QueryThread(const QString &sDbPath) noexcept
	: m_sDbPath(sDbPath)
{
}

void QueryThread::execute(const QString &query, const QHash<QString, QString> &mapBoundVals)
{
	// forward the execution to the worker
	m_queryExecutor.execute(query, mapBoundVals);
}

void QueryThread::run()
{
	qDebug() << "started thread" << QThread::currentThreadId();

	m_queryExecutor.setDatabase(m_sDbPath);

	// forward final signal
	connect(&m_queryExecutor, &queryExecutor::finished, this, &QueryThread::queryFinished);

	exec();
}

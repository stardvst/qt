#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

bool createConnection()
{
	if (!QSqlDatabase::drivers().contains("QSQLITE"))
		QMessageBox::critical(nullptr, "Unable to load database", "This demo needs the SQLITE driver");

	auto db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("musicdb");
	if (!db.open())
	{
		QMessageBox::critical(nullptr, QObject::tr("Database Error"), db.lastError().text());
		return false;
	}

	QSqlQuery query;
	if (db.tables().contains("artist"))
		query.exec("DROP TABLE artist;");

	if (!query.exec("CREATE TABLE artist (ID integer primary key, Name varchar, Age integer);"))
	{
		qDebug() << query.lastError().text();
		return false;
	}

	/*
	 * Oracle-syntax
	 */
	//if (!query.prepare(QLatin1String("INSERT INTO artist (Name, Age) VALUES(:Name, :Age); ")))
	//{
	//	qDebug() << query.lastError().text();
	//	return false;
	//}

	//query.bindValue(":Name", QLatin1String("Billie Eilish"));
	//query.bindValue(":Age", 17);
	//query.exec();

	//query.bindValue(":Name", QLatin1String("Demi Lovato"));
	//query.bindValue(":Age", 26);
	//query.exec();

	//query.bindValue(":Name", QLatin1String("Christina Perri"));
	//query.bindValue(":Age", 32);
	//query.exec();

	/*
	 * ODBC-style
	 */
	if (!query.prepare(QLatin1String("INSERT INTO artist (Name, Age) VALUES(?, ?); ")))
	{
		qDebug() << query.lastError().text();
		return false;
	}

	query.addBindValue(QLatin1String("Billie Eilish"));
	query.addBindValue(17);
	query.exec();

	query.addBindValue(QLatin1String("Demi Lovato"));
	query.addBindValue(26);
	query.exec();

	query.addBindValue(QLatin1String("Christina Perri"));
	query.addBindValue(32);
	query.exec();

	query.exec("SELECT Name, Age FROM artist WHERE Age >= 20;");
	
	while (query.next())
	{
		const QString artistName = query.value(0).toString();
		const int artistAge = query.value(1).toInt();
		qDebug() << artistName << ' ' << artistAge;
	}

	return true;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	if (!createConnection())
		return 1;

	return QApplication::exec();
}

#include <QApplication>
#include <QMessageBox>
#include <QtSql>
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

	auto driver = QSqlDatabase::database().driver();
	if (driver->hasFeature(QSqlDriver::Transactions))
		driver->beginTransaction();

	QSqlQuery query;

	QSqlTableModel model(nullptr, db);
	model.setTable("artist");
	model.setFilter("Name = 'Billie Eilish'");
	model.select();

	auto id = 0;
	if (model.rowCount())
		id = model.record(0).value("ID").toInt();

	if (!db.tables().contains("albums"))
	{
		if (!query.exec(
			"CREATE TABLE albums(ID INTEGER PRIMARY KEY AUTOINCREMENT, Title VARCHAR, ArtistID INTEGER,"
			"FOREIGN KEY (ArtistID)"
			"REFERENCES artist(ID));"))
		{
			qDebug() << query.lastError().text();
			return false;
		}
	}

	model.setTable("albums");
	int row = 0;
	model.insertRow(row);
	model.setData(model.index(row, 0), 1);
	model.setData(model.index(row, 1), QLatin1String("When we all fall asleep, where do we go?"));
	model.setData(model.index(row, 2), id);
	model.submitAll();

	model.select();
	if (model.rowCount())
	{
		auto record = model.record(0);
		model.setTable("artist");
		model.setFilter(QString("ID = %1").arg(id));
		model.select();
		if (model.rowCount())
		{
			qDebug()
				<< record.value("ID").toInt()
				<< model.record(0).value("Name").toString()
				<< record.value("Title").toString();
		}
	}

	if (driver->hasFeature(QSqlDriver::Transactions))
		driver->commitTransaction();

	return true;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	if (!createConnection())
		return 1;

	return QApplication::exec();
}

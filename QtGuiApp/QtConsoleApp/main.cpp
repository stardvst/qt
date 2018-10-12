#include <QCoreApplication>
#include <QTimer>

#include "DownloadManager.h"

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);

	DownloadManager manager;
	QTimer::singleShot(0, &manager, &DownloadManager::execute);

	return app.exec();
}
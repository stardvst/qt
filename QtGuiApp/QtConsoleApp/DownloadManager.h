#ifndef DOWNLOAD_MANAGER_H
#define DOWNLOAD_MANAGER_H

#include <QNetworkAccessManager>

class QSslError;

class DownloadManager : public QObject
{
	Q_OBJECT

private:
	QNetworkAccessManager manager;
	QVector<QNetworkReply *> currentDownloads;

public:
	DownloadManager();
	void doDownload(const QUrl &url);
	bool saveToDisk(const QString &filename, QIODevice *data);

	static QString fileNameForSaving(const QUrl &url);
	static bool isHttpRedirect(QNetworkReply *reply);

public slots:
	void execute();
	void downloadFinished(QNetworkReply *reply);
	void sslErrors(const QList<QSslError> &sslErrors);
};

#endif // !DOWNLOAD_MANAGER_H

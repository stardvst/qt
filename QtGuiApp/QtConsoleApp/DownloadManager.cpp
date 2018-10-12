#include "DownloadManager.h"

#include <cstdio>

#include <QtCore>
#include <QtNetwork>

DownloadManager::DownloadManager()
{
	connect(&manager, &QNetworkAccessManager::finished, [this](QNetworkReply *reply) { downloadFinished(reply); });
}

void DownloadManager::doDownload(const QUrl &url)
{
	QNetworkRequest request(url);
	auto reply = manager.get(request);

#if QT_CONFIG(ssl)
	connect(reply, &QNetworkReply::sslErrors, [this](const QList<QSslError> errors) { sslErrors(errors); });
#endif

	currentDownloads.append(reply);
}

void DownloadManager::execute()
{
	QStringList args = QCoreApplication::instance()->arguments();
	args.removeFirst(); // skip program's name
	if (args.isEmpty())
	{
		printf("Qt Download example - downloads all URLs in parallel\n"
			"Usage: download url1 [url2... urlN]\n\n"
			"Downloads the URLs passed in the command-line to the local directory\n"
			"If the target file already exists, a .0, .1, .2, etc. is appended to\n"
			"differentiate.\n");
		QCoreApplication::instance()->quit();
		return;
	}

	for (const auto &arg : qAsConst(args))
	{
		const auto url = QUrl::fromEncoded(arg.toLocal8Bit());
		doDownload(url);
	}
}

void DownloadManager::sslErrors(const QList<QSslError> &errors)
{
#if QT_CONFIG(ssl)
	for (const auto &error : errors)
		fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
	Q_UNUSED(errors);
#endif
}

void DownloadManager::downloadFinished(QNetworkReply *reply)
{
	const auto url = reply->url();
	if (reply->error())
	{
		fprintf(stderr, "Download of %s failed: %s\n",
			url.toEncoded().constData(),
			qPrintable(reply->errorString()));
	}
	else if (isHttpRedirect(reply))
	{
		fputs("Request was redirected.\n", stderr);
	}
	else
	{
		const auto filename = fileNameForSaving(url);
		if (saveToDisk(filename, reply))
		{
			printf("Download of %s succeeded (saved to %s)\n",
				url.toEncoded().constData(), qPrintable(filename));
		}
	}

	currentDownloads.removeAll(reply);
	reply->deleteLater();

	// all downloads finished
	if (currentDownloads.isEmpty())
		QCoreApplication::instance()->quit();
}

QString DownloadManager::fileNameForSaving(const QUrl &url)
{
	const auto path = url.path();
	auto basename = QFileInfo(path).fileName();

	if (basename.isEmpty())
		basename = "download";

	if (QFile::exists(basename))
	{
		auto idx = 0;
		basename += '.';
		while (QFile::exists(basename + QString::number(idx)))
			++idx;

		basename += QString::number(idx);
	}

	return basename;
}

bool DownloadManager::saveToDisk(const QString &filename, QIODevice *data)
{
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))
	{
		fprintf(stderr, "Could not open %s for writing: %s\n",
			qPrintable(filename),
			qPrintable(file.errorString()));
		return false;
	}

	file.write(data->readAll());
	file.close();

	return true;
}

bool DownloadManager::isHttpRedirect(QNetworkReply *reply)
{
	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	return statusCode == 301 || statusCode == 302 || statusCode == 303
		|| statusCode == 305 || statusCode == 307 || statusCode == 308;
}

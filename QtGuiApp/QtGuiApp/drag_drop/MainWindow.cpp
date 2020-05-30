#include "MainWindow.h"

#include <QTextEdit>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDebug>

MainWindow::MainWindow() noexcept
	: m_pTextEdit(new QTextEdit)
{
	m_pTextEdit->setAcceptDrops(false);
	setAcceptDrops(true);

	setWindowTitle("Text Editor");
	setCentralWidget(m_pTextEdit);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;

	QString fileName = urls.first().toLocalFile();
	if (fileName.isEmpty())
		return;

	if (readFile(fileName))
		setWindowTitle(tr("%1 - %2").arg(fileName).arg(tr("Drag File")));
}

bool MainWindow::readFile(const QString &fileName)
{
	qDebug() << __FUNCTION__ << fileName;
	return true;
}

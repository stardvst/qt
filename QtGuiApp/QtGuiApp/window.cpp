#include "filelistmodel.h"
#include "window.h"

#include <QtWidgets>

Window::Window(QWidget *parent)
	: QWidget(parent)
{
	FileListModel *model = new FileListModel(this);
	model->setDirPath(QLibraryInfo::location(QLibraryInfo::PrefixPath));

	QLabel *label = new QLabel(tr("&Directory:"));
	QLineEdit *lineEdit = new QLineEdit;
	label->setBuddy(lineEdit);

	QListView *view = new QListView;
	view->setModel(model);

	logViewer = new QTextBrowser;
	logViewer->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));

	connect(lineEdit, &QLineEdit::textChanged,
		model, &FileListModel::setDirPath);
	connect(lineEdit, &QLineEdit::textChanged,
		logViewer, &QTextEdit::clear);
	connect(model, &FileListModel::numberPopulated,
		this, &Window::updateLog);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(label, 0, 0);
	layout->addWidget(lineEdit, 0, 1);
	layout->addWidget(view, 1, 0, 1, 2);
	layout->addWidget(logViewer, 2, 0, 1, 2);

	setLayout(layout);
	setWindowTitle(tr("Fetch More Example"));
}

void Window::updateLog(int number)
{
	logViewer->append(tr("%1 items added.").arg(number));
}
#include <QApplication>
#include <QFileDialog>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QFileDialog fd;
	fd.setOptions(QFileDialog::Option::DontUseNativeDialog |
		QFileDialog::Option::DontUseCustomDirectoryIcons |
		QFileDialog::Option::DontConfirmOverwrite);
	fd.setViewMode(QFileDialog::List);
	fd.setFileMode(QFileDialog::AnyFile);
	fd.setAcceptMode(QFileDialog::AcceptSave);
	fd.setResolveSymlinks(true);
	fd.show();

	return app.exec();
}

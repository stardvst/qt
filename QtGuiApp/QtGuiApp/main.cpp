#include <QApplication>
#include <QTreeView>
#include "TreeModel.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	TreeModel model;
	QTreeView view;
	view.setModel(&model);
	view.setWindowTitle(QObject::tr("Simple 1-2-3-4-5 Tree Model"));
	view.setAnimated(true);
	view.show();
	
	return QApplication::exec();
}

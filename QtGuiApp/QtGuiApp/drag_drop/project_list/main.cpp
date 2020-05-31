#include <QApplication>

#include "ProjectListWidget.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	ProjectListWidget listWidget;
	listWidget.addItem("First item");
	listWidget.addItem("Second item");
	listWidget.addItem("Third item");
	listWidget.show();
	return app.exec();
}

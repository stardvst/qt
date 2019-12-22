#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QPushButton>

#include "window.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Window w;
	w.show();
	return app.exec();
}

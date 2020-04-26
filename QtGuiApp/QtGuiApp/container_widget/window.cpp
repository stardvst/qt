#include "window.h"

#include <QtWidgets>

#include "ContainerWidget.h"

Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	showMaximized();
	QLabel *lab1 = new QLabel("Label1");
	QLabel *lab2 = new QLabel("Label2");
	TContainer *con1 = new TContainer(this, QPoint(10, 10), lab1);
	TContainer *con2 = new TContainer(this, QPoint(20, 50), lab2);
}

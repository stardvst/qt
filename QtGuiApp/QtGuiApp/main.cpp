#include <QApplication>
#include "qlayout.h"
#include "qwidget.h"

#include "hexspinbox.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	auto window = new QWidget;

	auto hexSpinBox = new HexSpinBox;

	hexSpinBox->setValue(35);

	auto layout = new QHBoxLayout;
	layout->addWidget(hexSpinBox);
	window->setLayout(layout);

	window->show();

	return app.exec();
}

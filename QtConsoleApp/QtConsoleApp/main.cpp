#include <QApplication>
#include "qlayout.h"
#include "qwidget.h"

#include "hexspinbox.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QWidget *const window = new QWidget;

    HexSpinBox *const hexSpinBox = new HexSpinBox;

    hexSpinBox->setValue(35);

    QHBoxLayout *const layout = new QHBoxLayout;
    layout->addWidget(hexSpinBox);
    window->setLayout(layout);

    window->show();

    return app.exec();
}

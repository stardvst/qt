#include <QtWidgets\qapplication.h>
#include <QtWidgets\qlabel.h>


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QLabel *label = new QLabel("Hello World!");
    label->show();
    return app.exec();
}
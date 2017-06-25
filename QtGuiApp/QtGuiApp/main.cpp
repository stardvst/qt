#include <QtWidgets\qapplication.h>

#include "FindDialog.hpp"


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    FindDialog *dialog = new FindDialog;
    dialog->show();
    return app.exec();
}
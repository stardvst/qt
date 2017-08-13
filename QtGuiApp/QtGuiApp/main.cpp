#include <qapplication.h>
#include <qtextedit.h>
#include <qsplitter.h>

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    QTextEdit *editor1 = new QTextEdit;
    QTextEdit *editor2 = new QTextEdit;
    QTextEdit *editor3 = new QTextEdit;

    QSplitter splitter(Qt::Horizontal);
    splitter.addWidget(editor1);
    splitter.addWidget(editor2);
    splitter.addWidget(editor3);

    splitter.show();

    return app.exec();
}
#include <qapplication.h>
#include <qpushbutton.h>
#include <qlayout.h>

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(200, 100);

    QPushButton *buttonInfo = new QPushButton("Info", &window);
    //buttonInfo->setGeometry(10, 10, 80, 30);
    buttonInfo->setMaximumWidth(80);

    QPushButton *buttonQuit = new QPushButton("Quit", &window);
    //buttonQuit->setGeometry(10, 10, 110, 30);
    buttonQuit->setMinimumWidth(110);

    QObject::connect(buttonInfo, SIGNAL(clicked()), qApp, SLOT(aboutQt()));
    QObject::connect(buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    QVBoxLayout *vlayout = new QVBoxLayout;

    hlayout->addWidget(buttonInfo, 0, Qt::AlignHCenter);

    vlayout->addLayout(hlayout);
    vlayout->addWidget(buttonQuit);
    vlayout->setAlignment(Qt::AlignCenter);

    window.setLayout(vlayout);
    window.show();

    return app.exec();
}
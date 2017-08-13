#include <qfilesystemmodel.h>
#include <qapplication.h>
#include <qmainwindow.h>
#include <qtableview.h>
#include <qtreeview.h>
#include <qlistview.h>
#include <qsplitter.h>

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    QSplitter *topSplitter = new QSplitter(Qt::Horizontal);

    QTreeView *tree = new QTreeView(topSplitter);
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));

    QListView *list = new QListView(topSplitter);
    list->setModel(model);
    list->setRootIndex(model->index(QDir::currentPath()));

    QTableView *table = new QTableView;
    table->setModel(model);
    table->setRootIndex(model->index(QDir::currentPath()));

    QSplitter *mainSplitter = new QSplitter(Qt::Vertical);
    mainSplitter->addWidget(topSplitter);
    mainSplitter->addWidget(table);
    mainSplitter->setStretchFactor(1, 1); // i want to give table more space ;)
     
    QMainWindow window;
    window.setWindowTitle("Two views onto the same file system model");
    window.setCentralWidget(mainSplitter);
    window.show();
    
    return app.exec();
}
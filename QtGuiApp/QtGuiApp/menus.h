#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QActionGroup;
class QAction;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow();

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent *event) override;
#endif // !QT_NO_CONTEXTMENU

private slots :
    void newFile();
    void open();
    void save();
    void print();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void justify();
    void center();
    void setLineSpacing();
    void setParagraphSpacing();
    void about();
    void aboutQt();

private:
    void createActions();
    void createMenus();

private:
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *helpMenu;

    QActionGroup *alignmentGroup;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *printAction;
    QAction *exitAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *boldAction;
    QAction *italicAction;
    QAction *leftAlignAction;
    QAction *rightAlignAction;
    QAction *justifyAction;
    QAction *centerAction;
    QAction *setLineSpacingAction;
    QAction *setParagraphSpacingAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

    QLabel *infoLabel;
};

#endif // !MAINWINDOW_H

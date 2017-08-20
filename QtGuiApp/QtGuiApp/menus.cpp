#include <QtWidgets>

#include "menus.h"

MainWindow::MainWindow() {

    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(QObject::tr("<i>Choose a menu option, or right-click to "
                                       "invoke a context menu</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);

    widget->setLayout(layout);

    createActions();
    createMenus();

    QString message = QObject::tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);

    setWindowTitle(QObject::tr("Menus"));
    setMinimumSize(160, 160);
    resize(480, 320);
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event) {

    QMenu menu(this);
    menu.addAction(cutAction);
    menu.addAction(copyAction);
    menu.addAction(pasteAction);
    menu.exec(event->globalPos());
}
#endif // !QT_NO_CONTEXTMENU

void MainWindow::newFile() {
    infoLabel->setText(QObject::tr("Invoked <b>File|New</b>"));
}

void MainWindow::open() {
    infoLabel->setText(QObject::tr("Invoked <b>File|Open</b>"));
}

void MainWindow::save() {
    infoLabel->setText(QObject::tr("Invoked <b>File|Save</b>"));
}

void MainWindow::print() {
    infoLabel->setText(QObject::tr("Invoked <b>File|Print</b>"));
}

void MainWindow::undo() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Undo</b>"));
}

void MainWindow::redo() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Redo</b>"));
}

void MainWindow::cut() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Cut</b>"));
}

void MainWindow::copy() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Copy</b>"));
}

void MainWindow::paste() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Paste</b>"));
}

void MainWindow::bold() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Format|Bold</b>"));
}

void MainWindow::italic() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Format|Italic</b>"));
}

void MainWindow::leftAlign() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Format|Left Align</b>"));
}

void MainWindow::rightAlign() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Format|Right Align</b>"));
}

void MainWindow::justify() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Format|Justify</b>"));
}

void MainWindow::center() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Format|Center</b>"));
}

void MainWindow::setLineSpacing() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Format|Set Line Spacing</b>"));
}

void MainWindow::setParagraphSpacing() {
    infoLabel->setText(QObject::tr("Invoked <b>Edit|Format|Set Paragraph Spacing</b>"));
}

void MainWindow::about() {
    infoLabel->setText(QObject::tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, QObject::tr("About Menu"),
                       QObject::tr("The <b>Menu</b> example shows how to create "
                                   "menu-bar menus and context menus."));
}

void MainWindow::aboutQt() {
    infoLabel->setText(QObject::tr("Invoked <b>Help|About Qt</b>"));
}

void MainWindow::createActions() {
    /* file menu actions */
    newAction = new QAction(QObject::tr("&New"), this);
    newAction->setShortcuts(QKeySequence::New);
    newAction->setStatusTip(QObject::tr("Create a new file"));
    QObject::connect(newAction, &QAction::triggered, this, &MainWindow::newFile);

    openAction = new QAction(QObject::tr("&Open..."), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(QObject::tr("Open an existing file"));
    QObject::connect(openAction, &QAction::triggered, this, &MainWindow::open);

    saveAction = new QAction(QObject::tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(QObject::tr("Save the document to disk"));
    QObject::connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    printAction = new QAction(QObject::tr("&Print..."), this);
    printAction->setShortcuts(QKeySequence::Print);
    printAction->setStatusTip(QObject::tr("Print the document"));
    QObject::connect(printAction, &QAction::triggered, this, &MainWindow::print);

    exitAction = new QAction(QObject::tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(QObject::tr("Exit the application"));
    QObject::connect(exitAction, &QAction::triggered, this, &QWidget::close); // exit

    /* edit menu actions */
    undoAction = new QAction(QObject::tr("&Undo"), this);
    undoAction->setShortcuts(QKeySequence::Undo);
    undoAction->setStatusTip(QObject::tr("Undo the last operation"));
    QObject::connect(undoAction, &QAction::triggered, this, &MainWindow::undo);

    redoAction = new QAction(QObject::tr("&Redo"), this);
    redoAction->setShortcuts(QKeySequence::Redo);
    redoAction->setStatusTip(QObject::tr("Redo the last operation"));
    QObject::connect(redoAction, &QAction::triggered, this, &MainWindow::redo);

    cutAction = new QAction(QObject::tr("Cu&t"), this);
    cutAction->setShortcuts(QKeySequence::Cut);
    cutAction->setStatusTip(QObject::tr("Cut the current selection's contents to the clipboard"));
    QObject::connect(cutAction, &QAction::triggered, this, &MainWindow::cut);

    copyAction = new QAction(QObject::tr("&Copy"), this);
    copyAction->setShortcuts(QKeySequence::Copy);
    copyAction->setStatusTip(QObject::tr("Copy the current selection's contents to the clipboard"));
    QObject::connect(copyAction, &QAction::triggered, this, &MainWindow::copy);

    pasteAction = new QAction(QObject::tr("&Paste"), this);
    pasteAction->setShortcuts(QKeySequence::Paste);
    pasteAction->setStatusTip(QObject::tr("Paste the clipboard's contents into the current selection"));
    QObject::connect(pasteAction, &QAction::triggered, this, &MainWindow::paste);

    /* font related actions */
    boldAction = new QAction(QObject::tr("&Bold"), this);
    boldAction->setCheckable(true);
    boldAction->setShortcut(QKeySequence::Bold);
    boldAction->setStatusTip(QObject::tr("Make the text bold"));
    QObject::connect(boldAction, &QAction::triggered, this, &MainWindow::bold);

    QFont boldFont = boldAction->font();
    boldFont.setBold(true);
    boldAction->setFont(boldFont);

    italicAction = new QAction(QObject::tr("&Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setStatusTip(QObject::tr("Make the text italic"));
    QObject::connect(italicAction, &QAction::triggered, this, &MainWindow::italic);

    QFont italicFont = italicAction->font();
    italicFont.setItalic(true);
    italicAction->setFont(italicFont);

    setLineSpacingAction = new QAction(QObject::tr("Set &Line Spacing..."), this);
    setLineSpacingAction->setStatusTip(QObject::tr("Change the gap between the lines of a paragraph"));
    QObject::connect(setLineSpacingAction, &QAction::triggered, this, &MainWindow::setLineSpacing);

    setParagraphSpacingAction = new QAction(QObject::tr("Set &Paragraph Spacing..."), this);
    setParagraphSpacingAction->setStatusTip(QObject::tr("Change the gap between paragraphs"));
    QObject::connect(setParagraphSpacingAction, &QAction::triggered, this, &MainWindow::setParagraphSpacing);

    /* help menu actions */
    aboutAction = new QAction(QObject::tr("&About"), this);
    aboutAction->setStatusTip(QObject::tr("Show the application's About box"));
    QObject::connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

    aboutQtAction = new QAction(QObject::tr("About &Qt"), this);
    aboutQtAction->setStatusTip(QObject::tr("Show the Qt library's About box"));
    QObject::connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
    QObject::connect(aboutQtAction, &QAction::triggered, this, &MainWindow::aboutQt);

    /* alignment actions */
    leftAlignAction = new QAction(QObject::tr("&Left Align"), this);
    leftAlignAction->setCheckable(true);
    leftAlignAction->setShortcut(QObject::tr("Ctrl+L"));
    leftAlignAction->setStatusTip(QObject::tr("Left align the selected text"));
    QObject::connect(leftAlignAction, &QAction::triggered, this, &MainWindow::leftAlign);

    rightAlignAction = new QAction(QObject::tr("&Right Align"), this);
    rightAlignAction->setCheckable(true);
    rightAlignAction->setShortcut(QObject::tr("Ctrl+R"));
    rightAlignAction->setStatusTip(QObject::tr("Right align the selected text"));
    QObject::connect(rightAlignAction, &QAction::triggered, this, &MainWindow::rightAlign);

    justifyAction = new QAction(QObject::tr("&Justify"), this);
    justifyAction->setCheckable(true);
    justifyAction->setShortcut(QObject::tr("Ctrl+J"));
    justifyAction->setStatusTip(QObject::tr("Justify the selected text"));
    QObject::connect(justifyAction, &QAction::triggered, this, &MainWindow::justify);

    centerAction = new QAction(QObject::tr("&Center"), this);
    centerAction->setCheckable(true);
    centerAction->setShortcut(QObject::tr("Ctrl+E"));
    centerAction->setStatusTip(QObject::tr("Center the selected text"));
    QObject::connect(centerAction, &QAction::triggered, this, &MainWindow::center);

    /* alignment group */
    alignmentGroup = new QActionGroup(this); // actiongroup is exclusive by default
    alignmentGroup->addAction(leftAlignAction);
    alignmentGroup->addAction(rightAlignAction);
    alignmentGroup->addAction(justifyAction);
    alignmentGroup->addAction(centerAction);
    leftAlignAction->setChecked(true);
}

void MainWindow::createMenus() {

    fileMenu = menuBar()->addMenu(QObject::tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(QObject::tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();

    formatMenu = editMenu->addMenu(QObject::tr("&Format"));
    formatMenu->addAction(boldAction);
    formatMenu->addAction(italicAction);
    formatMenu->addSeparator()->setText(QObject::tr("Alignment"));
    formatMenu->addAction(leftAlignAction);
    formatMenu->addAction(rightAlignAction);
    formatMenu->addAction(justifyAction);
    formatMenu->addAction(centerAction);
    formatMenu->addSeparator();
    formatMenu->addAction(setLineSpacingAction);
    formatMenu->addAction(setParagraphSpacingAction);

    helpMenu = menuBar()->addMenu(QObject::tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}


#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <qdialog.h>

#include "ui_gotocelldialog.h"


class GoToCellDialog : public QDialog, public Ui::GoToCellDialog {

    Q_OBJECT

public:
    GoToCellDialog(QWidget *parent = 0);

    private slots:
    void on_lineEdit_textChanged();
};

#endif // !GOTOCELLDIALOG_H

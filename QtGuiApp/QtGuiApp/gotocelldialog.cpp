#include <QtGui>

#include "gotocelldialog.h"


GoToCellDialog::GoToCellDialog(QWidget *parent) 
    : QDialog(parent) {
    setupUi(this);

    QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
    lineEdit->setValidator(new QRegExpValidator(regExp, this));

    QObject::connect(lineEdit, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void GoToCellDialog::on_lineEdit_textChanged() {
    okButton->setEnabled(lineEdit->hasAcceptableInput());
}
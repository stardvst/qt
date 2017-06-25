#ifndef FINDDIALOG_HPP
#define FINDDIALOG_HPP

#include <QtWidgets\qpushbutton.h>
#include <QtWidgets\qcheckbox.h>
#include <QtWidgets\qlineedit.h>
#include <QtWidgets\qdialog.h>
#include <QtWidgets\qlabel.h>


class FindDialog : public QDialog {

    Q_OBJECT

public:
    FindDialog(QWidget *parent = 0);
signals:
    void findNext(const QString &str, Qt::CaseSensitivity);
    void findPrevious(const QString &str, Qt::CaseSensitivity);
private slots:
    void findClicked();
    void enableFindButton(const QString &text);
private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
};

#endif

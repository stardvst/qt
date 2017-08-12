#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/qwidget.h>

class QPushButton;

class Window : public QWidget {

    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);

signals:
    void counterReached();

    private slots:
    void slotButtonClicked(bool checked);

private:
    int m_counter;
    QPushButton *m_button;
};

#endif // WINDOW_H

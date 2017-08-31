#ifndef TICKER_H
#define TICKER_H

#include <qwidget.h>

class Ticker : public QWidget {

    Q_OBJECT
        Q_PROPERTY(QString text READ text WRITE setText)

public:
    Ticker(QWidget *parent = nullptr);

    void setText(const QString &text);
    QString text() const { return m_text; }
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private:
    QString m_text;
    int m_offset;
    int m_timerId;
};

#endif // !TICKER_H

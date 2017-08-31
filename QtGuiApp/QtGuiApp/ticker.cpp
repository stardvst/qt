#include <QtGui>

#include "ticker.h"

Ticker::Ticker(QWidget *parent) 
    : QWidget(parent)
    , m_offset(0)
    , m_timerId(0)
{}

void Ticker::setText(const QString &text) {
    m_text = text;
    update();
    updateGeometry();
}

QSize Ticker::sizeHint() const {
    return fontMetrics().size(0, text()); // info about widget's font
}

void Ticker::paintEvent(QPaintEvent * /* event */) {
    QPainter painter(this);

    int textWidth = fontMetrics().width(text());
    if(textWidth < 1) {
        return;
    }

    int x = -m_offset;
    while(x < width()) {
        painter.drawText(x, 0, textWidth, height(), Qt::AlignLeft | Qt::AlignVCenter, text());
        x += textWidth;
    }
}

void Ticker::showEvent(QShowEvent * /* event */) {
    m_timerId = startTimer(30);
}

void Ticker::timerEvent(QTimerEvent *event) {
    if(event->timerId() == m_timerId) {
        ++m_offset;
        if(m_offset >= fontMetrics().width(text())) {
            m_offset = 0;
        }
        scroll(-1, 0);
    } else {
        QWidget::timerEvent(event);
    }
}

void Ticker::hideEvent(QHideEvent * /* event */) {
    killTimer(m_timerId);
    m_timerId = 0;
}
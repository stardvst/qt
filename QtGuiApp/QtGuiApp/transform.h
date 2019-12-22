#pragma once

#include <QWidget>
#include <QPainter>

class Widget : public QWidget
{
protected:
	void paintEvent(QPaintEvent *event) override
	{
		QPainter painter(this);
		painter.setPen(QPen(Qt::blue, 1, Qt::DashLine));
		painter.drawRect(0, 0, 100, 100);

		painter.rotate(45);

		painter.setFont(QFont("Helvetica", 24));
		painter.setPen(QPen(Qt::black, 1));
		painter.drawText(20, 10, "QMatrix");
	}
};

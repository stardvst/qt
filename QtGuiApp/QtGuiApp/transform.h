#pragma once

#include <QWidget>
#include <QPainter>
#include <QMatrix>

class Widget : public QWidget
{
protected:
	void paintEvent(QPaintEvent *event) override
	{
		QPainter painter(this);
		painter.setPen(QPen(Qt::blue, 1, Qt::DashLine));
		painter.drawRect(0, 0, 100, 100);

		double pi = 3.14;
		double a = pi / 180 * 45.0;
		double sina = sin(a);
		double cosa = cos(a);

		QTransform transTransform(1, 0, 0, 1, 50.0, 50.0);
		QTransform rotTransform(cosa, sina, -sina, cosa, 0, 0);
		QTransform scaleTransform(0.5, 0, 0, 1.0, 0, 0);

		// order is important
		QTransform transform = scaleTransform * rotTransform * transTransform;
		painter.setTransform(transform);

		painter.setFont(QFont("Helvetica", 24));
		painter.setPen(QPen(Qt::black, 1));
		painter.drawText(20, 10, "QTransform");
	}
};

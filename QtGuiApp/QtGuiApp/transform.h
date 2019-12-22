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

		//QMatrix matrix;
		//matrix.translate(50, 50);
		//matrix.rotate(45);
		//matrix.scale(0.5, 1.0);

		double pi = 3.14;
		double a = pi / 180 * 45.0;
		double sina = sin(a);
		double cosa = cos(a);

		QMatrix transMatrix(1, 0, 0, 1, 50.0, 50.0);
		QMatrix rotMatrix(cosa, sina, -sina, cosa, 0, 0);
		QMatrix scaleMatrix(0.5, 0, 0, 1.0, 0, 0);

		// order is important
		QMatrix matrix = scaleMatrix * rotMatrix * transMatrix;
		painter.setMatrix(matrix);

		painter.setFont(QFont("Helvetica", 24));
		painter.setPen(QPen(Qt::black, 1));
		painter.drawText(20, 10, "QMatrix");
	}
};

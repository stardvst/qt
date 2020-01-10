#include <QApplication>
#include <QPolygon>
#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QVector<QPointF> fpts;
	fpts.push_back({ 0.4, 2.8 });
	fpts.push_back({ 7.6, 8.2 });
	fpts.push_back({ 11.6, 8.2 });
	fpts.push_back({ 4.4, 2.8 });

	QPolygonF fmarginedPoly(fpts);

	fpts.clear();
	fpts.push_back({ 3, 5 });
	fpts.push_back({ 3, 6 });
	fpts.push_back({ 5, 6 });
	fpts.push_back({ 5, 5 });
	QPolygonF shape1(fpts);
	auto fintersect = fmarginedPoly.intersected(shape1);
	qDebug() << fintersect;

	fpts.clear();
	fpts.push_back({ 6, 6 });
	fpts.push_back({ 6, 8 });
	fpts.push_back({ 10, 8 });
	fpts.push_back({ 10, 6 });
	QPolygonF shape2(fpts);
	fintersect = fmarginedPoly.intersected(shape2);
	qDebug() << fintersect;

	fpts.clear();
	fpts.push_back({ 8, 4 });
	fpts.push_back({ 8, 5 });
	fpts.push_back({ 10, 5 });
	fpts.push_back({ 10, 4 });
	QPolygonF shape3(fpts);
	fintersect = fmarginedPoly.intersected(shape3);
	qDebug() << fintersect;

	//////////////////////////////////////////////////////////////////////////
	// vertical
	//

	fpts.clear();
	fpts.push_back({ 1, 1 });
	fpts.push_back({ 1, 9 });
	fpts.push_back({ 5, 9 });
	fpts.push_back({ 5, 1 });
	fmarginedPoly = QPolygonF(fpts);

	fpts.clear();
	fpts.push_back({ 4, 4 });
	fpts.push_back({ 4, 5 });
	fpts.push_back({ 7, 5 });
	fpts.push_back({ 7, 4 });
	QPolygonF shape4(fpts);
	fintersect = fmarginedPoly.intersected(shape4);
	qDebug() << fintersect;

	fpts.clear();
	fpts.push_back({ 2, 6 });
	fpts.push_back({ 2, 8 });
	fpts.push_back({ 4, 7 });
	fpts.push_back({ 4, 6 });
	QPolygonF shape5(fpts);
	fintersect = fmarginedPoly.intersected(shape5);
	qDebug() << fintersect;

	fpts.clear();
	fpts.push_back({ 6, 1 });
	fpts.push_back({ 6, 2 });
	fpts.push_back({ 8, 2 });
	fpts.push_back({ 8, 1 });
	QPolygonF shape6(fpts);
	fintersect = fmarginedPoly.intersected(shape6);
	qDebug() << fintersect;

	//////////////////////////////////////////////////////////////////////////
	// horizontal
	//

	fpts.clear();
	fpts.push_back({ 6, 3 });
	fpts.push_back({ 6, 7 });
	fpts.push_back({ 14, 7 });
	fpts.push_back({ 14, 3 });
	fmarginedPoly = QPolygonF(fpts);

	fpts.clear();
	fpts.push_back({ 4, 4 });
	fpts.push_back({ 4, 5 });
	fpts.push_back({ 7, 5 });
	fpts.push_back({ 7, 4 });
	QPolygonF shape7(fpts);
	fintersect = fmarginedPoly.intersected(shape7);
	qDebug() << fintersect;

	fpts.clear();
	fpts.push_back({ 11, 4 });
	fpts.push_back({ 11, 6 });
	fpts.push_back({ 13, 6 });
	fpts.push_back({ 13, 4 });
	QPolygonF shape8(fpts);
	fintersect = fmarginedPoly.intersected(shape8);
	qDebug() << fintersect;

	fpts.clear();
	fpts.push_back({ 6, 1 });
	fpts.push_back({ 6, 2 });
	fpts.push_back({ 8, 2 });
	fpts.push_back({ 8, 1 });
	QPolygonF shape9(fpts);
	fintersect = fmarginedPoly.intersected(shape9);
	qDebug() << fintersect;

	//////////////////////////////////////////////////////////////////////////
	// positive slope
	//

	fpts.clear();
	fpts.push_back({ -0.632456, 0.102633 });
	fpts.push_back({ 1.632456, 6.897367 });
	fpts.push_back({ 5.632456, 6.897367 });
	fpts.push_back({ 3.367544, 0.102633 });
	fmarginedPoly = QPolygonF(fpts);

	fpts.clear();
	fpts.push_back({ 4, 3 });
	fpts.push_back({ 4, 4 });
	fpts.push_back({ 6, 4 });
	fpts.push_back({ 6, 3 });
	QPolygonF shape10(fpts);
	fintersect = fmarginedPoly.intersected(shape10);
	qDebug() << fintersect;

	fpts.clear();
	fpts.push_back({ 1, 1 });
	fpts.push_back({ 1, 3 });
	fpts.push_back({ 3, 3 });
	fpts.push_back({ 3, 1 });
	QPolygonF shape11(fpts);
	fintersect = fmarginedPoly.intersected(shape11);
	qDebug() << fintersect;

	fpts.clear();
	fpts.push_back({ 5, 1 });
	fpts.push_back({ 5, 2 });
	fpts.push_back({ 7, 2 });
	fpts.push_back({ 7, 1 });
	QPolygonF shape12(fpts);
	fintersect = fmarginedPoly.intersected(shape12);
	qDebug() << fintersect;

	//////////////////////////////////////////////////////////////////////////
	// positive slope
	//

	fpts.clear();
	fpts.push_back({ 10.4, 0.58 });
	fpts.push_back({ 4.58, 6.58 });
	fpts.push_back({ 8.58, 6.58 });
	fpts.push_back({ 14.4, 0.58 });
	fmarginedPoly = QPolygonF(fpts);

	fpts.clear();
	fpts.push_back({ 10, 4 });
	fpts.push_back({ 10, 6 });
	fpts.push_back({ 12, 6 });
	fpts.push_back({ 12, 4 });
	QPolygonF shape13(fpts);
	fintersect = fmarginedPoly.intersected(shape13);
	qDebug() << fintersect;

	fpts.clear();
	fpts.push_back({ 7, 5 });
	fpts.push_back({ 7, 6 });
	fpts.push_back({ 8, 6 });
	fpts.push_back({ 8, 5 });
	QPolygonF shape14(fpts);
	fintersect = fmarginedPoly.intersected(shape14);
	qDebug() << fintersect;

	fpts.clear();
	fpts.push_back({ 5, 1 });
	fpts.push_back({ 5, 2 });
	fpts.push_back({ 7, 2 });
	fpts.push_back({ 7, 1 });
	QPolygonF shape15(fpts);
	fintersect = fmarginedPoly.intersected(shape15);
	qDebug() << fintersect;

	return app.exec();
}

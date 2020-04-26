#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QtGui>
#include <QVBoxLayout>
#include <QMenu>

enum modes
{
	NONE = 0,
	MOVE = 1,
	RESIZETL = 2,
	RESIZET = 3,
	RESIZETR = 4,
	RESIZER = 5,
	RESIZEBR = 6,
	RESIZEB = 7,
	RESIZEBL = 8,
	RESIZEL = 9
};

class ContainerWidget : public QWidget
{
	Q_OBJECT

public:
	ContainerWidget(QWidget *parent, QPoint p, QWidget *cWidget = 0);
	~ContainerWidget();
	QWidget *childWidget;
	QMenu *menu;
	void setChildWidget(QWidget *cWidget);

protected:
	void setCursorShape(const QPoint &e_pos);
	bool eventFilter(QObject *obj, QEvent *evt);
	void keyPressEvent(QKeyEvent *);
	void focusInEvent(QFocusEvent *);
	void focusOutEvent(QFocusEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void popupShow(const QPoint &pt);

	QPoint position;
	QVBoxLayout *vLayout;
	int mode;
	bool m_infocus;
	bool m_showMenu;
	bool m_isEditing;

signals:
	void inFocus(bool mode);
	void outFocus(bool mode);
	void newGeometry(QRect rect);
};


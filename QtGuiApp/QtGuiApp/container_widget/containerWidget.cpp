#include "containerWidget.h"

#include <QApplication>

ContainerWidget::ContainerWidget(QWidget *parent, QPoint p, QWidget *cWidget) : QWidget(parent)
{
	mode = NONE;
	childWidget = cWidget;
	setAttribute(Qt::WA_DeleteOnClose);
	setVisible(true);
	setAutoFillBackground(false);
	setMouseTracking(true);
	setFocusPolicy(Qt::ClickFocus);
	setFocus();
	move(p);

	vLayout = new QVBoxLayout(this);
	if (cWidget != 0)
	{
		cWidget->setParent(this);
		cWidget->releaseMouse();
		cWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
		vLayout->addWidget(cWidget);
		vLayout->setContentsMargins(0, 0, 0, 0);
	}
	setLayout(vLayout);

	m_infocus = true;
	m_showMenu = false;
	m_isEditing = true;
	installEventFilter(parent);
}

ContainerWidget::~ContainerWidget()
{
	delete vLayout;
}

void ContainerWidget::setChildWidget(QWidget *cWidget)
{
	if (cWidget != 0)
	{
		childWidget = cWidget;
		childWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
		childWidget->setParent(this);
		vLayout->addWidget(cWidget);
		vLayout->setContentsMargins(0, 0, 0, 0);
	}
}

void ContainerWidget::popupShow(const QPoint &pt)
{
	if (menu->isEmpty()) return;
	QPoint global = mapToGlobal(pt);
	m_showMenu = true;
	menu->exec(global);
	m_showMenu = false;
}

void ContainerWidget::focusInEvent(QFocusEvent *)
{
	m_infocus = true;
	parentWidget()->installEventFilter(this);
	parentWidget()->repaint();
	emit inFocus(true);
}

void ContainerWidget::focusOutEvent(QFocusEvent *)
{
	if (!m_isEditing) return;
	if (m_showMenu) return;
	mode = NONE;
	emit outFocus(false);
	m_infocus = false;
}

bool ContainerWidget::eventFilter(QObject *obj, QEvent *evt)
{
	if (m_infocus)
	{
		QWidget *w = parentWidget();
		if (w == obj && evt->type() == QEvent::Paint)
		{
			// Draw container selection
			QPainter painter(w);
			QPoint p = mapTo(w, QPoint(-3, -3));
			QPoint LT = w->mapFrom(w, p);
			QPoint LB = w->mapFrom(w, QPoint(p.x(), p.y() + height()));
			QPoint RB = w->mapFrom(w, QPoint(p.x() + width(), p.y() + height()));
			QPoint RT = w->mapFrom(w, QPoint(p.x() + width(), p.y()));

			painter.fillRect(LT.x(), LT.y(), 6, 6, QColor("black"));
			painter.fillRect(LB.x(), LB.y(), 6, 6, QColor("black"));
			painter.fillRect(RB.x(), RB.y(), 6, 6, QColor("black"));
			painter.fillRect(RT.x(), RT.y(), 6, 6, QColor("black"));
			return QWidget::eventFilter(obj, evt);
		}
	}
	return QWidget::eventFilter(obj, evt);
}

void ContainerWidget::mousePressEvent(QMouseEvent *e)
{
	position = QPoint(e->globalX() - geometry().x(), e->globalY() - geometry().y());
	if (!m_isEditing) return;
	if (!m_infocus) return;
	if (!e->buttons() && Qt::LeftButton)
	{
		setCursorShape(e->pos());
		return;
	}
	if (e->button() == Qt::RightButton)
	{
		popupShow(e->pos());
		e->accept();
	}
}

void ContainerWidget::keyPressEvent(QKeyEvent *e)
{
	if (!m_isEditing) return;
	if (e->key() == Qt::Key_Delete)
	{
		deleteLater();
	}
	// Moving container with arrows
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		QPoint newPos(x(), y());
		if (e->key() == Qt::Key_Up) newPos.setY(newPos.y() - 1);
		if (e->key() == Qt::Key_Down) newPos.setY(newPos.y() + 1);
		if (e->key() == Qt::Key_Left) newPos.setX(newPos.x() - 1);
		if (e->key() == Qt::Key_Right) newPos.setX(newPos.x() + 1);
		move(newPos);
	}
	if (QApplication::keyboardModifiers() == Qt::ShiftModifier)
	{
		if (e->key() == Qt::Key_Up) resize(width(), height() - 1);
		if (e->key() == Qt::Key_Down) resize(width(), height() + 1);
		if (e->key() == Qt::Key_Left) resize(width() - 1, height());
		if (e->key() == Qt::Key_Right) resize(width() + 1, height());
	}
	emit newGeometry(geometry());
}

void ContainerWidget::setCursorShape(const QPoint &e_pos)
{
	const int diff = 3;
	if (
		//Left-Bottom
		((e_pos.y() > y() + height() - diff) &&     //Bottom
			(e_pos.x() < x() + diff)) ||               //Left
		   //Right-Bottom
		((e_pos.y() > y() + height() - diff) &&     //Bottom
			(e_pos.x() > x() + width() - diff)) ||     //Right
		   //Left-Top
		((e_pos.y() < y() + diff) &&                //Top
			(e_pos.x() < x() + diff)) ||               //Left
		   //Right-Top
		((e_pos.y() < y() + diff) &&                //Top
			(e_pos.x() > x() + width() - diff))        //Right
		)
	{
		//Left-Bottom
		if ((e_pos.y() > y() + height() - diff) &&      //Bottom
			(e_pos.x() < x() + diff))               //Left
		{
			mode = RESIZEBL;
			setCursor(QCursor(Qt::SizeBDiagCursor));
		}
		//Right-Bottom
		if ((e_pos.y() > y() + height() - diff) &&      //Bottom
			(e_pos.x() > x() + width() - diff))     //Right
		{
			mode = RESIZEBR;
			setCursor(QCursor(Qt::SizeFDiagCursor));
		}
		//Left-Top
		if ((e_pos.y() < y() + diff) &&                 //Top
			(e_pos.x() < x() + diff))               //Left
		{
			mode = RESIZETL;
			setCursor(QCursor(Qt::SizeFDiagCursor));
		}
		//Right-Top
		if ((e_pos.y() < y() + diff) &&                 //Top
			(e_pos.x() > x() + width() - diff))     //Right
		{
			mode = RESIZETR;
			setCursor(QCursor(Qt::SizeBDiagCursor));
		}
	}
	// check cursor horizontal position
	else if ((e_pos.x() < x() + diff) ||                //Left
		((e_pos.x() > x() + width() - diff)))      //Right
	{
		if (e_pos.x() < x() + diff)
		{                   //Left
			setCursor(QCursor(Qt::SizeHorCursor));
			mode = RESIZEL;
		}
		else
		{                                        //Right
			setCursor(QCursor(Qt::SizeHorCursor));
			mode = RESIZER;
		}
	}
	// check cursor vertical position
	else if (((e_pos.y() > y() + height() - diff)) ||   //Bottom
		(e_pos.y() < y() + diff))                  //Top
	{
		if (e_pos.y() < y() + diff)
		{                   //Top
			setCursor(QCursor(Qt::SizeVerCursor));
			mode = RESIZET;
		}
		else
		{                                        //Bottom
			setCursor(QCursor(Qt::SizeVerCursor));
			mode = RESIZEB;
		}
	}
	else
	{
		setCursor(QCursor(Qt::ArrowCursor));
		mode = MOVE;
	}
}

void ContainerWidget::mouseReleaseEvent(QMouseEvent *e)
{
	QWidget::mouseReleaseEvent(e);
}

void ContainerWidget::mouseMoveEvent(QMouseEvent *e)
{
	QWidget::mouseMoveEvent(e);
	if (!m_isEditing) return;
	if (!m_infocus) return;
	if (!e->buttons() && Qt::LeftButton)
	{
		QPoint p = QPoint(e->x() + geometry().x(), e->y() + geometry().y());
		setCursorShape(p);
		return;
	}

	if ((mode == MOVE || mode == NONE) && e->buttons() && Qt::LeftButton)
	{
		QPoint toMove = e->globalPos() - position;
		if (toMove.x() < 0) return;
		if (toMove.y() < 0) return;
		if (toMove.x() > parentWidget()->width() - width()) return;
		move(toMove);
		emit newGeometry(geometry());
		parentWidget()->repaint();
		return;
	}
	if ((mode != MOVE) && e->buttons() && Qt::LeftButton)
	{
		switch (mode)
		{
			case RESIZETL:
			{    //Left-Top
				int newwidth = e->globalX() - position.x() - geometry().x();
				int newheight = e->globalY() - position.y() - geometry().y();
				QPoint toMove = e->globalPos() - position;
				resize(geometry().width() - newwidth, geometry().height() - newheight);
				move(toMove.x(), toMove.y());
				break;
			}
			case RESIZETR:
			{    //Right-Top
				int newheight = e->globalY() - position.y() - geometry().y();
				QPoint toMove = e->globalPos() - position;
				resize(e->x(), geometry().height() - newheight);
				move(x(), toMove.y());
				break;
			}
			case RESIZEBL:
			{    //Left-Bottom
				int newwidth = e->globalX() - position.x() - geometry().x();
				QPoint toMove = e->globalPos() - position;
				resize(geometry().width() - newwidth, e->y());
				move(toMove.x(), y());
				break;
			}
			case RESIZEB:
			{     //Bottom
				resize(width(), e->y());
				break;
			}
			case RESIZEL:
			{     //Left
				int newwidth = e->globalX() - position.x() - geometry().x();
				QPoint toMove = e->globalPos() - position;
				resize(geometry().width() - newwidth, height());
				move(toMove.x(), y());
				break;
			}
			case RESIZET:
			{     //Top
				int newheight = e->globalY() - position.y() - geometry().y();
				QPoint toMove = e->globalPos() - position;
				resize(width(), geometry().height() - newheight);
				move(x(), toMove.y());
				break;
			}
			case RESIZER:
			{     //Right
				resize(e->x(), height());
				break;
			}
			case RESIZEBR:
			{    //Right-Bottom
				resize(e->x(), e->y());
				break;
			}
		}
		parentWidget()->repaint();
	}
	emit newGeometry(geometry());
}

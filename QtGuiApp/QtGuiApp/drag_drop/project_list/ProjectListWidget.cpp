#include "ProjectListWidget.h"

#include <QMouseEvent>
#include <QApplication>
#include <QMimeData>
#include <QDrag>

ProjectListWidget::ProjectListWidget(QWidget *parent /* = nullptr */) noexcept
	: QListWidget(parent)
{
	setAcceptDrops(true);
}

void ProjectListWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		m_ptStartPos = event->pos();
	QListWidget::mousePressEvent(event);
}

void ProjectListWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		int distance = (event->pos() - m_ptStartPos).manhattanLength();
		if (distance >= QApplication::startDragDistance())
			performDrag();
	}
	QListWidget::mouseMoveEvent(event);
}

void ProjectListWidget::performDrag()
{
	if (auto item = currentItem())
	{
		auto mimeData = new QMimeData;
		mimeData->setText(item->text());

		auto drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->setPixmap(QPixmap(":/butterfly"));
		if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
			delete item;
	}
}

void ProjectListWidget::dragEnterEvent(QDragEnterEvent *event)
{
	auto src = qobject_cast<ProjectListWidget *>(event->source());
	if (src && src != this)
	{
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
}

void ProjectListWidget::dragMoveEvent(QDragMoveEvent *event)
{
	auto src = qobject_cast<ProjectListWidget *>(event->source());
	if (src && src != this)
	{
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
}

void ProjectListWidget::dropEvent(QDropEvent *event)
{
	auto src = qobject_cast<ProjectListWidget *>(event->source());
	if (src && src != this)
	{
		addItem(event->mimeData()->text());
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
}

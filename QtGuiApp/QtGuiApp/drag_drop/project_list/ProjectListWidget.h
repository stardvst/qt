#pragma once

#include <QListWidget>

class ProjectListWidget : public QListWidget
{
	Q_OBJECT

public:
	explicit ProjectListWidget(QWidget *parent = nullptr) noexcept;

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

	void dragEnterEvent(QDragEnterEvent *event) override;
	void dragMoveEvent(QDragMoveEvent *event) override;
	void dropEvent(QDropEvent *event) override;

private:
	void performDrag();

private:
	QPoint m_ptStartPos;

};

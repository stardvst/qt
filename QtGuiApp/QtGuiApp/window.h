#pragma once

#include <QWidget>

class QTextBrowser;

class Window : public QWidget
{
	Q_OBJECT

public:
	Window(QWidget *parent = nullptr);

public slots:
	void updateLog(int number);

private:
	QTextBrowser *logViewer = nullptr;
};

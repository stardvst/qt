#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtQuickApp.h"

class QtQuickApp : public QMainWindow
{
	Q_OBJECT

public:
	QtQuickApp(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtQuickAppClass ui;
};

#pragma once

#include <QMainWindow>

class QTextEdit;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow() noexcept;

protected:
	void dragEnterEvent(QDragEnterEvent *event) override;
	void dropEvent(QDropEvent *event) override;

private:
	bool readFile(const QString &fileName);

private:
	QTextEdit *m_pTextEdit = nullptr;

};

#pragma once

#include <QWidget>
#include <QPainter>

class QToolButton;
class QComboBox;
class QLabel;

class ImageComposer : public QWidget
{
	Q_OBJECT

public:
	ImageComposer();

private slots:
	void chooseSource();
	void chooseDestination();
	void recalculateResult();

private:
	void addOp(QPainter::CompositionMode mode, const QString &name);
	void chooseImage(const QString &title, QImage *image, QToolButton *button);
	void loadImage(const QString &fileName, QImage *image, QToolButton *button);
	QPainter::CompositionMode currentMode() const;
	QPoint imagePos(const QImage &image) const;

	QToolButton *m_sourceButton = nullptr;
	QToolButton *m_destinationButton = nullptr;
	QComboBox *m_operationCombobox = nullptr;
	QLabel *m_equalLabel = nullptr;
	QLabel *m_resultLabel = nullptr;

	QImage m_sourceImage;
	QImage m_destinationImage;
	QImage m_resultImage;
};
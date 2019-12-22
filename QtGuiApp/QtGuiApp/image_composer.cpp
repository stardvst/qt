#include "image_composer.h"

#include <QtWidgets>

static const QSize resultSize(200, 200);

ImageComposer::ImageComposer()
	: m_sourceButton(new QToolButton)
	, m_destinationButton(new QToolButton)
	, m_operationCombobox(new QComboBox)
	, m_equalLabel(new QLabel(tr("=")))
	, m_resultLabel(new QLabel)
	, m_resultImage(resultSize, QImage::Format_ARGB32_Premultiplied)
{
	m_sourceButton->setIconSize(resultSize);
	(void)connect(m_sourceButton, &QToolButton::clicked, this, &ImageComposer::chooseSource);

	(void)connect(m_operationCombobox, qOverload<int>(&QComboBox::activated), this, &ImageComposer::recalculateResult);

	(void)connect(m_destinationButton, &QToolButton::clicked, this, &ImageComposer::chooseDestination);

	m_destinationButton->setIconSize(resultSize);
	m_resultLabel->setMinimumWidth(resultSize.width());

	addOp(QPainter::CompositionMode_SourceOver, tr("SourceOver"));
	addOp(QPainter::CompositionMode_DestinationOver, tr("DestinationOver"));
	addOp(QPainter::CompositionMode_Clear, tr("Clear"));
	addOp(QPainter::CompositionMode_Source, tr("Source"));
	addOp(QPainter::CompositionMode_Destination, tr("Destination"));
	addOp(QPainter::CompositionMode_SourceIn, tr("SourceIn"));
	addOp(QPainter::CompositionMode_DestinationIn, tr("DestinationIn"));
	addOp(QPainter::CompositionMode_SourceOut, tr("SourceOut"));
	addOp(QPainter::CompositionMode_DestinationOut, tr("DestinationOut"));
	addOp(QPainter::CompositionMode_SourceAtop, tr("SourceAtop"));
	addOp(QPainter::CompositionMode_DestinationAtop, tr("DestinationAtop"));
	addOp(QPainter::CompositionMode_Xor, tr("XOR"));
	addOp(QPainter::CompositionMode_Plus, tr("Plus"));
	addOp(QPainter::CompositionMode_Multiply, tr("Multiply"));
	addOp(QPainter::CompositionMode_Screen, tr("Screen"));
	addOp(QPainter::CompositionMode_Overlay, tr("Overlay"));
	addOp(QPainter::CompositionMode_Darken, tr("Darken"));
	addOp(QPainter::CompositionMode_Lighten, tr("Lighten"));
	addOp(QPainter::CompositionMode_ColorDodge, tr("ColorDodge"));
	addOp(QPainter::CompositionMode_ColorBurn, tr("ColorBurn"));
	addOp(QPainter::CompositionMode_HardLight, tr("HardLight"));
	addOp(QPainter::CompositionMode_SoftLight, tr("SoftLight"));
	addOp(QPainter::CompositionMode_Difference, tr("Difference"));
	addOp(QPainter::CompositionMode_Exclusion, tr("Exclusion"));

	auto mainLayout = new QGridLayout;
	mainLayout->addWidget(m_sourceButton, 0, 0, 3, 1);
	mainLayout->addWidget(m_operationCombobox, 1, 1);
	mainLayout->addWidget(m_destinationButton, 0, 2, 3, 1);
	mainLayout->addWidget(m_equalLabel, 1, 3);
	mainLayout->addWidget(m_resultLabel, 0, 4, 3, 1);
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	setLayout(mainLayout);

	loadImage(":/butterfly", &m_sourceImage, m_sourceButton);
	loadImage(":/checker", &m_destinationImage, m_destinationButton);

	setWindowTitle(tr("Image Composition"));
}

void ImageComposer::chooseSource()
{
	chooseImage(tr("Choose Source Image"), &m_sourceImage, m_sourceButton);
}

void ImageComposer::chooseDestination()
{
	chooseImage(tr("Choose Destination Image"), &m_destinationImage, m_destinationButton);
}

void ImageComposer::recalculateResult()
{
	auto mode = currentMode();

	QPainter painter(&m_resultImage);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect(m_resultImage.rect(), Qt::transparent);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage(0, 0, m_destinationImage);
	painter.setCompositionMode(mode);
	painter.drawImage(0, 0, m_sourceImage);
	painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
	painter.fillRect(m_resultImage.rect(), Qt::white);
	painter.end();

	m_resultLabel->setPixmap(QPixmap::fromImage(m_resultImage));
}

void ImageComposer::addOp(const QPainter::CompositionMode mode, const QString &name)
{
	m_operationCombobox->addItem(name, mode);
}

void ImageComposer::chooseImage(const QString &title, QImage *image, QToolButton *button)
{
	const auto fileName = QFileDialog::getOpenFileName(this, title);
	if (!fileName.isEmpty())
		loadImage(fileName, image, button);
}

void ImageComposer::loadImage(const QString &fileName, QImage *image, QToolButton *button)
{
	image->load(fileName);

	*image = image->scaled(resultSize, Qt::KeepAspectRatio);

	QImage fixedImage(resultSize, QImage::Format_ARGB32_Premultiplied);
	QPainter painter(&fixedImage);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect(fixedImage.rect(), Qt::transparent);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage(imagePos(*image), *image);
	painter.end();

	button->setIcon(QPixmap::fromImage(fixedImage));

	*image = fixedImage;

	recalculateResult();
}

QPainter::CompositionMode ImageComposer::currentMode() const
{
	return static_cast<QPainter::CompositionMode>(m_operationCombobox->itemData(m_operationCombobox->currentIndex()).toInt());
}

QPoint ImageComposer::imagePos(const QImage &image) const
{
	return QPoint((resultSize.width() - image.width()) / 2, (resultSize.height() - image.height()) / 2);
}
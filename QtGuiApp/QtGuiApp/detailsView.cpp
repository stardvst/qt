#include "detailsView.h"

#include <QPushButton>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QSplitter>
#include <QLabel>
#include <QTableWidget>
#include <QTimer>

errorDetailsView::errorDetailsView(QString sWndTitle /* = QString() */,
	QWidget *parent /* = nullptr */) noexcept
	: QWidget(parent)
	, m_pMinMaxBtn(new QPushButton)
	, m_pTextArea(new QPlainTextEdit)
{
	// setup minimize button
	m_pMinMaxBtn->setFixedSize(QSize(12, 12));
	m_pMinMaxBtn->setIcon(QIcon(":/errorBrowser/icon_minimize"));
	m_pMinMaxBtn->setProperty("hidden", false);
	connect(m_pMinMaxBtn, &QPushButton::clicked, this, &errorDetailsView::onMinMaximize);

	// setup text area
	m_pTextArea->setReadOnly(true);

	// create the title bar layout
	auto pTitleBarLayout = new QHBoxLayout;
	pTitleBarLayout->setContentsMargins(0, 0, 3, 0);
	pTitleBarLayout->addWidget(new QLabel(sWndTitle));
	pTitleBarLayout->addWidget(m_pMinMaxBtn, 0, Qt::AlignRight);

	// create the main layout
	auto pMainLayout = new QVBoxLayout(this);
	pMainLayout->setContentsMargins(0, 0, 0, 0);
	pMainLayout->addLayout(pTitleBarLayout);
	pMainLayout->addWidget(m_pTextArea);
}

void errorDetailsView::onMinMaximize()
{
	// show/hide the text area based on previous state
	const bool bMinimized = m_pMinMaxBtn->property("hidden").toBool();
	if (bMinimized)
	{
		m_pTextArea->show();
		m_pMinMaxBtn->setIcon(QIcon(":/errorBrowser/icon_minimize"));
	}
	else
	{
		m_pTextArea->hide();
		m_pMinMaxBtn->setIcon(QIcon(":/errorBrowser/icon_maximize"));
	}

	// update the state
	m_pMinMaxBtn->setProperty("hidden", !bMinimized);

	emit minimizationChanged(!bMinimized);
}

errorViewer::errorViewer(QWidget *parent /* = nullptr */)
	: QWidget(parent)
	, m_pMainLayout(new QVBoxLayout(this))
{
	// setup the main layout
	m_pMainLayout->setContentsMargins(0, 0, 0, 0);

	// create vertical layout for right hand side view
	m_pTableSplitter = new QSplitter(Qt::Vertical, this);
	m_pTableSplitter->setCollapsible(0, false);
	m_pTableSplitter->setStretchFactor(0, 255);
	m_pTableSplitter->setStretchFactor(1, 0);

	// add the splitter to the layout
	m_pMainLayout->addWidget(m_pTableSplitter);

	m_pTableSplitter->insertWidget(0, new QTableWidget);

	m_pDetailsView = new errorDetailsView("Title");
	m_pTableSplitter->insertWidget(1, m_pDetailsView);
	// add a new connection
	connect(m_pDetailsView, &errorDetailsView::minimizationChanged,
		this, &errorViewer::adjustSplitterSizes);

	// the details view is visible, adjust the splitter sizes
	QTimer::singleShot(50, this, [this] { adjustSplitterSizes(false); });
}

void errorViewer::adjustSplitterSizes(bool bShowSingleWidget)
{
	if (bShowSingleWidget)
	{
		m_pTableSplitter->setSizes(
			QList<int>() << (height() * 0.93) << (height() * 0.07));
	}
	else
	{
		m_pTableSplitter->setSizes(
			QList<int>() << (height() * 0.8) << (height() * 0.2));
	}
}
#include "OpenGLWindow.h"

#include <QOpenGLPaintDevice>
#include <QPainter>

OpenGLWindow::OpenGLWindow(QWindow *parent /* = nullptr */)
	: QWindow(parent)
{
	// indicates that the window is to be used for OpenGL rendering,
	// and not for rendering raster content with QPainter using a QBackingStore
	setSurfaceType(QWindow::OpenGLSurface);
}

void OpenGLWindow::initialize()
{
}

void OpenGLWindow::render(QPainter *painter)
{
	Q_UNUSED(painter);
}

void OpenGLWindow::render()
{
	if (!m_pDevice)
		m_pDevice = new QOpenGLPaintDevice;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	m_pDevice->setSize(size());

	QPainter painter(m_pDevice);
	render(&painter);
}

void OpenGLWindow::setAnimating(bool bAnimating)
{
	m_bAnimating = bAnimating;

	if (m_bAnimating)
		renderLater();
}

void OpenGLWindow::renderLater()
{
	requestUpdate();
}

void OpenGLWindow::renderNow()
{
	if (!isExposed())
		return;

	bool bNeedsInit = false;

	if (!m_pContext)
	{
		m_pContext = new QOpenGLContext(this);
		m_pContext->setFormat(requestedFormat());
		m_pContext->create();

		bNeedsInit = true;
	}

	m_pContext->makeCurrent(this);

	if (bNeedsInit)
	{
		initializeOpenGLFunctions();
		initialize(); // for the sake of the sub class
	}

	render();

	// schedule for the rendered contents to be made visible
	m_pContext->swapBuffers(this);

	if (m_bAnimating)
		// schedule another update request
		renderLater();
}

bool OpenGLWindow::event(QEvent *event)
{
	switch (event->type())
	{
		case QEvent::UpdateRequest:
			renderNow();
			return true;
		default:
			return QWindow::event(event);
	}
}

void OpenGLWindow::exposeEvent(QExposeEvent *event)
{
	Q_UNUSED(event);

	if (isExposed())
		renderNow();
}

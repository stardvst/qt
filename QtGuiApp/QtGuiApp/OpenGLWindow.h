#pragma once

#include <QWindow>
#include <QOpenGLFunctions>

class QOpenGLContext;
class QOpenGLPaintDevice;

//////////////////////////////////////////////////////////////////////////
// By inheriting from QOpenGLFunctions the OpenGL functions it contains
// will get precedence, and you will not have to worry about resolving
// those functions if you want your application to work with OpenGL
// as well as OpenGL ES 2.0.

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit OpenGLWindow(QWindow *parent = nullptr);

	virtual void initialize();
	
	// For rendering with a QPainter
	virtual void render(QPainter *painter);

	// For OpenGL based rendering
	virtual void render();

	// Call render() at the vertical refresh rate
	void setAnimating(bool bAnimating);

public slots:
	// Render as soon as the event loop has finished processing the current batch of events
	void renderLater();

	// Render immediately
	void renderNow();

protected:
	bool event(QEvent *event) override;
	void exposeEvent(QExposeEvent *event) override;

private:
	bool m_bAnimating = false;

	QOpenGLContext *m_pContext = nullptr;
	QOpenGLPaintDevice *m_pDevice = nullptr;
};
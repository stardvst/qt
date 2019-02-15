#pragma once

#include "OpenGLWindow.h"

class QOpenGLShaderProgram;

class TriangleWindow : public OpenGLWindow
{
public:
	void initialize() override;
	void render() override;

private:
	GLuint m_iPosAttr;
	GLuint m_iColAttr;
	GLuint m_iMatrixUniform;

	QOpenGLShaderProgram *m_pProgram = nullptr;
	int m_iFrame = 0;
};

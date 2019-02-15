#include "TriangleWindow.h"

#include <QOpenGLShaderProgram>
#include <QScreen>

static const char *vertexShaderSource =
	"attribute highp vec4 posAttr;\n"
	"attribute lowp vec4 colAttr;\n"
	"varying lowp vec4 col;\n"
	"uniform highp mat4 matrix;\n"
	"void main() {\n"
	"   col = colAttr;\n"
	"   gl_Position = matrix * posAttr;\n"
	"}\n";

static const char *fragmentShaderSource =
	"varying lowp vec4 col;\n"
	"void main() {\n"
	"   gl_FragColor = col;\n"
	"}\n";

void TriangleWindow::initialize()
{
	m_pProgram = new QOpenGLShaderProgram;
	m_pProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	m_pProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
	m_pProgram->link();
	m_iPosAttr = m_pProgram->attributeLocation("posAttr");
	m_iColAttr = m_pProgram->attributeLocation("colAttr");
	m_iMatrixUniform = m_pProgram->uniformLocation("matrix");
}

void TriangleWindow::render()
{
	const qreal retinaScale = devicePixelRatio();
	glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	glClear(GL_COLOR_BUFFER_BIT);

	m_pProgram->bind();

	QMatrix4x4 matrix;
	matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	matrix.translate(0, 0, -2);
	matrix.rotate(100.0f * m_iFrame / screen()->refreshRate(), 0, 1, 0);

	m_pProgram->setUniformValue(m_iMatrixUniform, matrix);

	GLfloat vertices[] = {
		0.0f, 0.707f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	glVertexAttribPointer(m_iPosAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(m_iColAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	m_pProgram->release();

	++m_iFrame;
}

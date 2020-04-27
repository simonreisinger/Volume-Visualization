#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <glm.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>

#include <QGLWidget>

#include <QGLBuffer>

#include "Volume.h"

#include <5.3.1\QtWidgets\private\qopenglwidget_p.h>
#include <QOpenGLFunctions_3_3_Core>
#include <qopenglbuffer.h>
#include <QOpenGLShaderProgram>

using namespace std;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{

public:
    GLWidget(QWidget* parent = 0);
	~GLWidget();

	void setVolume(Volume* volume);

	const int GradientCentralDifference = 0;
	const int GradientSobel = 1;

	const int GradientCPU = 0;
	const int GradientGPU = 1;

	const int RenderMIP = 0;
	const int RenderAverage = 1;
	const int RenderFirstHit = 2;
	const int RenderAlpha = 3;
	const int RenderMIDA = 4;
	const int RenderGradient = 5;

	float ambientPower = 0.2f;
	float diffusePower = 6.0f;
	float specularPower = 4.0f;


	// ############## Settings ######################

	int GradientModeCalc = GradientCentralDifference;

	int GradientModeTarget = GradientCPU;

	const bool GradientEnabled = true;

	int renderTechnique = RenderMIP;//  RenderMIP; // TODO change this value for other frag shader

	// ##############################################

	void rotate(float rx, float ry, float rz);
	void translate(float tx, float ty, float tz);
	void scale(float sxyz);

	void setMida_gamma(float value);
	void setPercentageOfAlphaLayers(int value);
	void setName(string value);

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
	virtual void paintGL();
	void initializeTexture();

private:
    bool prepareShaderProgram( const QString& vertexShaderPath,
                               const QString& fragmentShaderPath );

	void printVector(glm::vec4 v);

	float deg2Rad(float deg);

    QOpenGLShaderProgram m_shader;
    QOpenGLBuffer m_vertexBuffer;
	Volume* m_Volume;
	GLuint handleVolume;
	GLuint handleGradient;

	QOpenGLFunctions_3_3_Core *gl;

	float* gradient;

	float z = 0.0;

	glm::mat4x4 cameraMat = glm::mat4x4(1.0);
	glm::mat4x4 rotateMat = glm::mat4x4(1.0);
	glm::mat4x4 translateMat = glm::mat4x4(1.0);
	glm::mat4x4 scaleMat = glm::mat4x4(1.0);

	float rotateFactor = 1.0f;
	float translateFactor = 0.01f;
	float scaleFactor = 0.1f;

	float mida_gamma = 0.0;
	int percentageOfAlphaLayers = 100;
	string name = "";
};

#endif // OPENGLWIDGET_H

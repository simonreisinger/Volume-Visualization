#include "glwidget.h"
#include <iostream>
#include <QCoreApplication>
#include <QKeyEvent>



GLWidget::GLWidget( QWidget* parent )
: QOpenGLWidget(parent), m_vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
}

GLWidget::~GLWidget() 
{
	gl->glDeleteTextures(1, &handleVolume);
	gl->glDeleteTextures(1, &handleGradient);

	delete gradient; gradient = nullptr;
}

void GLWidget::setVolume(Volume* volume) {

	if (m_Volume != nullptr) {
		delete m_Volume; m_Volume = nullptr;

		gl->glDeleteTextures(1, &handleVolume);
		gl->glDeleteTextures(1, &handleGradient);

		delete gradient; gradient = nullptr;
	}

	m_Volume = volume;

	int counter[101];
	for (int i = 0; i < 101; i++) {
		counter[i] = 0;
	}

	if (gl != nullptr) {
		initializeTexture();
	}
}

void GLWidget::initializeTexture() {

	// Texture im RAM
	gl->glGenTextures(1, &handleVolume);
	// Texture-Slot in der Grafikkarte
	gl->glActiveTexture(GL_TEXTURE0);
	// Define that texture type of the slot to use
	gl->glBindTexture(GL_TEXTURE_3D, handleVolume);

	gl->glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, m_Volume->width(), m_Volume->height(), m_Volume->depth(), 0, GL_RED, GL_FLOAT, m_Volume->voxelsArray());

	gl->glGenerateMipmap(GL_TEXTURE_3D);

	gl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	gl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	float degToRad = 2.0f * glm::pi<float>() / 360.0f;

	glm::mat4x4 proj = glm::ortho<float>(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	proj = glm::rotate(proj, deg2Rad(180), glm::vec3(1, 0, 0));
	cameraMat = proj;

	if (GradientEnabled) {
		// Texture im RAM
		gl->glGenTextures(1, &handleGradient);
		// Texture-Slot in der Grafikkarte
		gl->glActiveTexture(GL_TEXTURE1);
		// Define that texture type of the slot to use
		gl->glBindTexture(GL_TEXTURE_3D, handleGradient);

		gradient = new float[m_Volume->size() * 3];

		cout << "Calculating Gradient" << endl;

		int i = 0;
		for (int z = 0; z < m_Volume->depth(); z++) {
			for (int y = 0; y < m_Volume->height(); y++) {
				for (int x = 0; x < m_Volume->width(); x++) {
					if (i % (m_Volume->size() / 119) == 0) {
						cout << "*";
					}
					float gradient_x;
					float gradient_y;
					float gradient_z;
					if (GradientModeCalc == GradientSobel) {
						gradient_x = -4 * m_Volume->voxel(x - 1, y, z).getValue()
							- 2 * m_Volume->voxel(x - 1, y - 1, z).getValue()
							- 2 * m_Volume->voxel(x - 1, y + 1, z).getValue()
							- 2 * m_Volume->voxel(x - 1, y, z - 1).getValue()
							- 2 * m_Volume->voxel(x - 1, y, z + 1).getValue()
							- m_Volume->voxel(x - 1, y - 1, z - 1).getValue()
							- m_Volume->voxel(x - 1, y - 1, z + 1).getValue()
							- m_Volume->voxel(x - 1, y + 1, z - 1).getValue()
							- m_Volume->voxel(x - 1, y + 1, z + 1).getValue()
							+ 4 * m_Volume->voxel(x + 1, y, z).getValue()
							+ 2 * m_Volume->voxel(x + 1, y - 1, z).getValue()
							+ 2 * m_Volume->voxel(x + 1, y + 1, z).getValue()
							+ 2 * m_Volume->voxel(x + 1, y, z - 1).getValue()
							+ 2 * m_Volume->voxel(x + 1, y, z + 1).getValue()
							+ m_Volume->voxel(x + 1, y - 1, z - 1).getValue()
							+ m_Volume->voxel(x + 1, y - 1, z + 1).getValue()
							+ m_Volume->voxel(x + 1, y + 1, z - 1).getValue()
							+ m_Volume->voxel(x + 1, y + 1, z + 1).getValue();

						gradient_y = -4 * m_Volume->voxel(x, y - 1, z).getValue()
							- 2 * m_Volume->voxel(x - 1, y - 1, z).getValue()
							- 2 * m_Volume->voxel(x + 1, y - 1, z).getValue()
							- 2 * m_Volume->voxel(x, y - 1, z - 1).getValue()
							- 2 * m_Volume->voxel(x, y - 1, z + 1).getValue()
							- m_Volume->voxel(x - 1, y - 1, z - 1).getValue()
							- m_Volume->voxel(x - 1, y - 1, z + 1).getValue()
							- m_Volume->voxel(x + 1, y - 1, z - 1).getValue()
							- m_Volume->voxel(x + 1, y - 1, z + 1).getValue()
							+ 4 * m_Volume->voxel(x, y + 1, z).getValue()
							+ 2 * m_Volume->voxel(x - 1, y + 1, z).getValue()
							+ 2 * m_Volume->voxel(x + 1, y + 1, z).getValue()
							+ 2 * m_Volume->voxel(x, y + 1, z - 1).getValue()
							+ 2 * m_Volume->voxel(x, y + 1, z + 1).getValue()
							+ m_Volume->voxel(x - 1, y + 1, z - 1).getValue()
							+ m_Volume->voxel(x - 1, y + 1, z + 1).getValue()
							+ m_Volume->voxel(x + 1, y + 1, z - 1).getValue()
							+ m_Volume->voxel(x + 1, y + 1, z + 1).getValue();

						gradient_z = -4 * m_Volume->voxel(x, y, z - 1).getValue()
							- 2 * m_Volume->voxel(x - 1, y, z - 1).getValue()
							- 2 * m_Volume->voxel(x + 1, y, z - 1).getValue()
							- 2 * m_Volume->voxel(x, y - 1, z - 1).getValue()
							- 2 * m_Volume->voxel(x, y + 1, z - 1).getValue()
							- m_Volume->voxel(x - 1, y - 1, z - 1).getValue()
							- m_Volume->voxel(x - 1, y + 1, z - 1).getValue()
							- m_Volume->voxel(x + 1, y - 1, z - 1).getValue()
							- m_Volume->voxel(x + 1, y + 1, z - 1).getValue()
							+ 4 * m_Volume->voxel(x, y, z + 1).getValue()
							+ 2 * m_Volume->voxel(x - 1, y, z + 1).getValue()
							+ 2 * m_Volume->voxel(x + 1, y, z + 1).getValue()
							+ 2 * m_Volume->voxel(x, y - 1, z + 1).getValue()
							+ 2 * m_Volume->voxel(x, y + 1, z + 1).getValue()
							+ m_Volume->voxel(x - 1, y - 1, z + 1).getValue()
							+ m_Volume->voxel(x - 1, y + 1, z + 1).getValue()
							+ m_Volume->voxel(x + 1, y - 1, z + 1).getValue()
							+ m_Volume->voxel(x + 1, y + 1, z + 1).getValue();
					} else {
						gradient_x = -m_Volume->voxel(x - 1, y, z).getValue() + m_Volume->voxel(x + 1, y, z).getValue();
						gradient_y = -m_Volume->voxel(x, y - 1, z).getValue() + m_Volume->voxel(x, y + 1, z).getValue();
						gradient_z = -m_Volume->voxel(x, y, z - 1).getValue() + m_Volume->voxel(x, y, z + 1).getValue();
					}

					gradient[i * 3 + 0] = gradient_x;
					gradient[i * 3 + 1] = gradient_y;
					gradient[i * 3 + 2] = gradient_z;
					
					i++;
				}
			}
		}
		cout << endl;

		gl->glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, m_Volume->width(), m_Volume->height(), m_Volume->depth(), 0, GL_RGB, GL_FLOAT, gradient);

		gl->glGenerateMipmap(GL_TEXTURE_3D);

		gl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		gl->glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}

}

void GLWidget::initializeGL()
{
	gl = new QOpenGLFunctions_3_3_Core;

	gl->initializeOpenGLFunctions();

	// Set the clear color to black
	gl->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Prepare a complete shader program...
	if (!prepareShaderProgram("src/simple.vert", 
		"src/simple.frag"))
		return;

	// We need us some vertex data. Start simple with a triangle ;-)
	float points[] = { -1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f };

	m_vertexBuffer.create();
	m_vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	if (!m_vertexBuffer.bind())
	{
		qWarning() << "Could not bind vertex buffer to the context";
		return;
	}
	m_vertexBuffer.allocate(points, 6 * 4 * sizeof(float));

	// Bind the shader program so that we can associate variables from
	// our application to the shaders
	if (!m_shader.bind())
	{
		qWarning() << "Could not bind shader program to context";
		return;
	}

	// Enable the "vertex" attribute to bind it to our currently bound
	// vertex buffer.
	m_shader.setAttributeBuffer("vertex", GL_FLOAT, 0, 4);
	m_shader.enableAttributeArray("vertex");

	if (m_Volume != nullptr) {
		initializeTexture();
	}
}

void GLWidget::resizeGL( int w, int h )
{
	// Set the viewport to window dimensions
	gl->glViewport(0, 0, w, qMax(h, 1));
}

void GLWidget::paintGL()
{
	// Clear the buffer with the current clearing color
	gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_Volume != nullptr) {
		gl->glActiveTexture(GL_TEXTURE0);

		gl->glBindTexture(GL_TEXTURE_3D, handleVolume);

		auto volume_location = gl->glGetUniformLocation(m_shader.programId(), "volume");
		gl->glUniform1i(volume_location, 0);

		int alphaProfil;
		if (name.find("lobster") != std::string::npos) {
			alphaProfil = 1;
		}
		else if (name.find("head") != std::string::npos) {
			alphaProfil = 2;
		}
		else {
			alphaProfil = 0;
		}
		auto alphaProfil_location = gl->glGetUniformLocation(m_shader.programId(), "alphaProfil");
		gl->glUniform1i(alphaProfil_location, alphaProfil);
	
		auto mida_gamma_location = gl->glGetUniformLocation(m_shader.programId(), "mida_gamma");
		gl->glUniform1f(mida_gamma_location, mida_gamma);

		// TODO add alpha layers einblenden/ ausblenden
		auto percentageOfAlphaLayers_location = gl->glGetUniformLocation(m_shader.programId(), "percentageOfAlphaLayers");
		gl->glUniform1i(percentageOfAlphaLayers_location, percentageOfAlphaLayers);
	}
	
	auto renderTech_location = gl->glGetUniformLocation(m_shader.programId(), "renderTechnique");
	gl->glUniform1i(renderTech_location, renderTechnique);


	auto z_location = gl->glGetUniformLocation(m_shader.programId(), "z");
	gl->glUniform1f(z_location, abs(z));


	//cameraMat = glm::translate(cameraMat, glm::vec3(0, 0, 0.001));
	cameraMat = scaleMat * rotateMat * translateMat * cameraMat;

	auto cameraMat_location = gl->glGetUniformLocation(m_shader.programId(), "cameraMat");
	gl->glUniformMatrix4fv(cameraMat_location, 1, GL_FALSE, &cameraMat[0][0]);

	if (GradientEnabled) {
		gl->glActiveTexture(GL_TEXTURE1);

		gl->glBindTexture(GL_TEXTURE_3D, handleGradient);

		auto gradient_location = gl->glGetUniformLocation(m_shader.programId(), "gradient");
		gl->glUniform1i(gradient_location, 1);

		auto GradientModeTarget_location = gl->glGetUniformLocation(m_shader.programId(), "GradientModeTarget");
		gl->glUniform1i(GradientModeTarget_location, GradientModeTarget);

		auto GradientModeCalc_location = gl->glGetUniformLocation(m_shader.programId(), "GradientModeCalc");
		gl->glUniform1i(GradientModeCalc_location, GradientModeCalc);

		auto ambientPower_location = gl->glGetUniformLocation(m_shader.programId(), "ambientPower");
		gl->glUniform1f(ambientPower_location, ambientPower);

		auto diffusePower_location = gl->glGetUniformLocation(m_shader.programId(), "diffusePower");
		gl->glUniform1f(diffusePower_location, diffusePower);

		auto specularPower_location = gl->glGetUniformLocation(m_shader.programId(), "specularPower");
		gl->glUniform1f(specularPower_location, specularPower);
	}

	auto lightPos_location = gl->glGetUniformLocation(m_shader.programId(), "lightPos");
	gl->glUniform3f(lightPos_location, -2.0, 2.0, -2.0);

	// Draw stuff
	gl->glDrawArrays(GL_TRIANGLES, 0, 6);

	z += 0.005f;
	if (z > 1.0) {
		z = 0.0;
	}
}

bool GLWidget::prepareShaderProgram( const QString& vertexShaderPath,
                                     const QString& fragmentShaderPath )
{
	QString vertexShaderPathTmp = vertexShaderPath;
	QString fragmentShaderPathTmp = fragmentShaderPath;
	FILE *fp = NULL;
	fopen_s(&fp, vertexShaderPathTmp.toStdString().c_str(), "r");
	if (!fp)
	{
		vertexShaderPathTmp = "../../../" + vertexShaderPathTmp;
		fragmentShaderPathTmp = "../../../" + fragmentShaderPathTmp;
	}
	//fclose(fp);

    // First we load and compile the vertex shader...
	bool result;
	result = m_shader.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderPathTmp);
	if (!result)
		qWarning() << m_shader.log();

    // ...now the fragment shader...
	result = m_shader.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderPathTmp);
	if (!result)
		qWarning() << m_shader.log();

    // ...and finally we link them to resolve any references.
    result = m_shader.link();
    if ( !result )
        qWarning() << "Could not link shader program:" << m_shader.log();

    return result;
}

void GLWidget::printVector(glm::vec4 v) {
	cout << v.x << " " << v.y << " " << v.z << endl;
}

void GLWidget::rotate(float rx, float ry, float rz) {
	rotateMat = glm::rotate(glm::mat4x4(1.0f), deg2Rad(rx*rotateFactor), glm::vec3(1.0, 0.0, 0.0));
	rotateMat = glm::rotate(rotateMat, deg2Rad(ry*rotateFactor), glm::vec3(0.0, 1.0, 0.0));
	rotateMat = glm::rotate(rotateMat, deg2Rad(rz*rotateFactor), glm::vec3(0.0, 0.0, 1.0));
}

float GLWidget::deg2Rad(float deg) {
	return deg * 2.0f * glm::pi<float>() / 360.0f;
}

void GLWidget::translate(float tx, float ty, float tz) {
	translateMat = glm::translate(glm::mat4x4(1.0f), glm::vec3(tx*translateFactor, ty*translateFactor, tz*translateFactor));
}

void GLWidget::scale(float sxyz) {
	if (sxyz == 1) scaleMat = glm::mat4x4(1.0f);
	else scaleMat = glm::scale(glm::mat4x4(1.0f), glm::vec3(1.0f + sxyz * scaleFactor));
}

void  GLWidget::setMida_gamma(float value){
	mida_gamma = value;
}

void  GLWidget::setPercentageOfAlphaLayers(int value){
	percentageOfAlphaLayers = value;
}

void GLWidget::setName(string value) {
	name = value;
}
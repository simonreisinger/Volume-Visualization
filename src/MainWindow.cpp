#include "MainWindow.h"
#include <iostream>

#include <QFileDialog>

#include <QPainter>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), m_Volume(0), m_VectorField(0)
{
	m_Ui = new Ui_MainWindow();
	m_Ui->setupUi(this);
	w = m_Ui->openGLWidget;
	
	connect(m_Ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFileAction()));
	connect(m_Ui->actionClose, SIGNAL(triggered()), this, SLOT(closeAction()));
	connect(m_Ui->renderTechnique, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated), [=](const QString &text){ render(text); });
	connect(m_Ui->translationX, SIGNAL(valueChanged(int)), this, SLOT(translateX(int)));
	connect(m_Ui->translationY, SIGNAL(valueChanged(int)), this, SLOT(translateY(int)));
	connect(m_Ui->translationZ, SIGNAL(valueChanged(int)), this, SLOT(translateZ(int)));
	connect(m_Ui->rotationX,	SIGNAL(valueChanged(int)), this, SLOT(rotateX(int)));
	connect(m_Ui->rotationY,	SIGNAL(valueChanged(int)), this, SLOT(rotateY(int)));
	connect(m_Ui->rotationZ,	SIGNAL(valueChanged(int)), this, SLOT(rotateZ(int)));
	connect(m_Ui->zoom,			SIGNAL(valueChanged(int)), this, SLOT(zoom(int)));

	connect(m_Ui->translationX, SIGNAL(sliderReleased()), this, SLOT(resetSlider()));
	connect(m_Ui->translationY, SIGNAL(sliderReleased()), this, SLOT(resetSlider()));
	connect(m_Ui->translationZ, SIGNAL(sliderReleased()), this, SLOT(resetSlider()));
	connect(m_Ui->rotationX, SIGNAL(sliderReleased()), this, SLOT(resetSlider()));
	connect(m_Ui->rotationY, SIGNAL(sliderReleased()), this, SLOT(resetSlider()));
	connect(m_Ui->rotationZ, SIGNAL(sliderReleased()), this, SLOT(resetSlider()));
	connect(m_Ui->zoom, SIGNAL(sliderReleased()), this, SLOT(resetSlider()));

	connect(m_Ui->gamma, SIGNAL(valueChanged(int)), this, SLOT(setNewGammaForMIDA(int)));
	connect(m_Ui->schichtenEinblenden, SIGNAL(valueChanged(int)), this, SLOT(setAmountOfLayersAlphaCompositing(int)));
	hideWidgets();

	connect(m_Ui->ambient, SIGNAL(valueChanged(int)), this, SLOT(ambient(int)));
	connect(m_Ui->diffuse, SIGNAL(valueChanged(int)), this, SLOT(diffuse(int)));
	connect(m_Ui->specular, SIGNAL(valueChanged(int)), this, SLOT(specular(int)));

	connect(m_Ui->gradientModeCalc, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated), [=](const QString &text){ gradientModeCalc(text); });
	connect(m_Ui->gradientModeTarget, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated), [=](const QString &text){ gradientModeTarget(text); });

	// TODO: REMOVE
	openFileAction();
}

MainWindow::~MainWindow()
{
	delete m_Volume;
	delete m_VectorField;
	delete m_MultiSet;
}

void MainWindow::resetSlider() {
	m_Ui->translationX->setSliderPosition(49);
	m_Ui->translationY->setSliderPosition(49);
	m_Ui->translationZ->setSliderPosition(49);
	m_Ui->rotationX->setSliderPosition(49);
	m_Ui->rotationY->setSliderPosition(49);
	m_Ui->rotationZ->setSliderPosition(49);
	m_Ui->zoom->setSliderPosition(49);
	w->translate(0, 0, 0);
	w->rotate(0, 0, 0);
	w->scale(1);
}

//-------------------------------------------------------------------------------------------------
// Render Technique: further Values
//-------------------------------------------------------------------------------------------------

void MainWindow::setNewGammaForMIDA(int value)
{
	float normalizedValue = ((float)value - 50.0) / 50.0;
	//cout << "MIDA gamma " << value << " normaized: " << normalizedValue << endl;
	w->setMida_gamma(normalizedValue);
}


// Returns a value between 0 and 99
// can be devided through the number of layers 
void MainWindow::setAmountOfLayersAlphaCompositing(int value)
{
	//cout << "Layers of Alpha Compositing " << value << endl;
	w->setPercentageOfAlphaLayers(value);
}

//-------------------------------------------------------------------------------------------------
// Translation
//-------------------------------------------------------------------------------------------------

void MainWindow::translateX(int value)
{
	float normalizedValue = ((float)value - 50.0) / 50.0;
	//cout << "translateX " << value << " normaized: " << normalizedValue << endl;
	w->translate(normalizedValue, 0, 0);
}

void MainWindow::translateY(int value)
{
	float normalizedValue = ((float)value - 50.0) / 50.0;
	//cout << "translateY " << value << " normaized: " << normalizedValue << endl;
	w->translate(0, normalizedValue, 0);
}

void MainWindow::translateZ(int value)
{
	float normalizedValue = ((float)value - 50.0) / 50.0;
	//cout << "translateZ " << value << " normaized: " << normalizedValue << endl;
	w->translate(0, 0, normalizedValue);
}

void MainWindow::rotateX(int value)
{
	float normalizedValue = ((float)value - 50.0) / 50.0;
	//cout << "rotateX " << value << " normaized: " << normalizedValue << endl;
	w->rotate(normalizedValue, 0, 0);
}

void MainWindow::rotateY(int value)
{
	float normalizedValue = ((float)value - 50.0) / 50.0;
	//cout << "rotateY " << value << " normaized: " << normalizedValue << endl;
	w->rotate(0, normalizedValue, 0);
}

void MainWindow::rotateZ(int value)
{
	float normalizedValue = ((float)value - 50.0) / 50.0;
	//cout << "rotateZ " << value << " normaized: " << normalizedValue << endl;
	w->rotate(0, 0, normalizedValue);
}

void MainWindow::zoom(int value)
{
	float normalizedValue = ((float)value - 50.0) / 50.0;
	//cout << "zoom " << value << " normaized: " << normalizedValue << endl;
	w->scale(normalizedValue);
}

//-------------------------------------------------------------------------------------------------
// Slots
//-------------------------------------------------------------------------------------------------

void MainWindow::openFileAction()
{
	if (timer != nullptr) {
		timer->stop();
		timer = nullptr;
	}

	// TODO: CHANGE
	QString filename = QFileDialog::getOpenFileName(this, "Data File", 0, tr("Data Files (*.dat *.gri *.csv)"));
	//QString filename = "datasets/lobster_120x120x34.dat";

	if (!filename.isEmpty())
	{
		// store filename
		m_FileType.filename = filename;
		std::string fn = filename.toStdString();
		bool success = false;

		// progress bar and top label
		m_Ui->progressBar->setEnabled(true);
		m_Ui->labelTop->setText("Loading data ...");

		// load data according to file extension
		if (fn.substr(fn.find_last_of(".") + 1) == "dat")		// LOAD VOLUME
		{
			// send Name to glwidget
			string name = fn.substr(fn.find_last_of("/") + 1);
			w->setName(name);
			if (name.find("lobster") != std::string::npos) {
				m_Ui->schichtenEinblenden->setSliderPosition(4);
			}
			else if (name.find("head") != std::string::npos) {
				m_Ui->schichtenEinblenden->setSliderPosition(20);
			}
			else if (name.find("beetle") != std::string::npos) {
				m_Ui->schichtenEinblenden->setSliderPosition(5);
			}

			// create VOLUME
			m_FileType.type = VOLUME;
			m_Volume = new Volume();

			// load file
			success = m_Volume->loadFromFile(filename, m_Ui->progressBar);

			m_Ui->openGLWidget->setVolume(m_Volume);
		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "gri")		// LOAD VECTORFIELD
		{
			// create VECTORFIELD
			m_FileType.type = VECTORFIELD;
			m_VectorField = new VectorField();

			// load file
			success = m_VectorField->loadFromFile(filename, m_Ui->progressBar);
		}
		else if (fn.substr(fn.find_last_of(".") + 1) == "csv")		// LOAD MULTIVARIATE DATA
		{
			// create MULTIVARIATE
			m_FileType.type = MULTIVARIATE;
			m_MultiSet = new MultiSet();

			// load file
			success = m_MultiSet->loadFromFile(filename, m_Ui->progressBar);
		}

		m_Ui->progressBar->setEnabled(false);

		// status message
		if (success)
		{
			QString type;
			if (m_FileType.type == VOLUME) type = "VOLUME";
			else if (m_FileType.type == VECTORFIELD) type = "VECTORFIELD";
			else if (m_FileType.type == MULTIVARIATE) type = "MULTIVARIATE";
			m_Ui->labelTop->setText("File LOADED [" + filename + "] - Type [" + type + "]");
		}
		else
		{
			m_Ui->labelTop->setText("ERROR loading file " + filename + "!");
			m_Ui->progressBar->setValue(0);
		}
	}
	
	// create a timer
	timer = new QTimer(this);

	// setup signal and slot
	connect(timer, SIGNAL(timeout()),
		this, SLOT(update()));

	// msec
	timer->start(0);
	
}

void MainWindow::closeAction()
{
	close();
}

void MainWindow::render(QString value) {
	hideWidgets();
	if (value == "MIP") w->renderTechnique = w->RenderMIP;
	else if (value == "Alpha"){
		m_Ui->label_schichtenEinblenden->show();
		m_Ui->schichtenEinblenden->show();
		w->renderTechnique = w->RenderAlpha;
	}
	else if (value == "Average") w->renderTechnique = w->RenderAverage;
	else if (value == "MIDA") {
		m_Ui->gamma->show();
		m_Ui->label_gama->show();
		w->renderTechnique = w->RenderMIDA;
	}
	else if (value == "First Hit") w->renderTechnique = w->RenderFirstHit;
	else if (value == "Gradient" && w->GradientEnabled) {
		w->renderTechnique = w->RenderGradient;
		m_Ui->label_ambient->show();
		m_Ui->ambient->show();
		m_Ui->label_diffuse->show();
		m_Ui->diffuse->show();
		m_Ui->label_specular->show();
		m_Ui->specular->show();
		//m_Ui->gradientModeCalc->show();
		m_Ui->gradientModeTarget->show();
	}
	else if (value == "Pass through") w->renderTechnique = 9;
	else w->renderTechnique = w->RenderMIP;
}


void MainWindow::hideWidgets() {
	m_Ui->gamma->hide();
	m_Ui->label_gama->hide();
	m_Ui->label_schichtenEinblenden->hide();
	m_Ui->schichtenEinblenden->hide();
	m_Ui->label_ambient->hide();
	m_Ui->ambient->hide();
	m_Ui->label_diffuse->hide();
	m_Ui->diffuse->hide();
	m_Ui->label_specular->hide();
	m_Ui->specular->hide();
	m_Ui->gradientModeCalc->hide();
	m_Ui->gradientModeTarget->hide();
}

void MainWindow::ambient(int value) {
	float convertedValue = (float)value;
	w->ambientPower = convertedValue / 10.0;
}

void MainWindow::diffuse(int value) {
	float convertedValue = (float)value;
	w->diffusePower = convertedValue / 10.0;
}

void MainWindow::specular(int value) {
	float convertedValue = (float)value;
	w->specularPower = convertedValue / 10.0;
}

void MainWindow::gradientModeCalc(QString value) {
	if (value == "Sobel") w->GradientModeCalc = w->GradientSobel;
	if (value == "CentralDifference") w->GradientModeCalc = w->GradientCentralDifference;
}

void MainWindow::gradientModeTarget(QString value) {
	if (value == "CPU") w->GradientModeTarget = w->GradientCPU;
	if (value == "GPU") w->GradientModeTarget = w->GradientGPU;
}
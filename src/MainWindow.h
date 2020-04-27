
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>

#include "ui_MainWindow.h"
#include "Volume.h"
#include "VectorField.h"
#include "MultiSet.h"

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QStatusBar>
#include <QVariant>

#include <QGLWidget>


class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:

		MainWindow(QWidget *parent = 0);
		~MainWindow();

	protected slots :

		void								 openFileAction();
		void								 closeAction();


		void translateX(int value);
		void translateY(int value);
		void translateZ(int value);

		void rotateX(int value);
		void rotateY(int value);
		void rotateZ(int value);

		void zoom(int value);

		void render(QString value);

		void resetSlider();

		void setNewGammaForMIDA(int value);
		void setAmountOfLayersAlphaCompositing(int value);

		void ambient(int value);
		void diffuse(int value);
		void specular(int value);

		void gradientModeCalc(QString value);
		void gradientModeTarget(QString value);

	private:

		void hideWidgets();

		// USER INTERFACE ELEMENTS

		Ui_MainWindow						*m_Ui;


		// DATA 

		enum DataType
		{
			VOLUME					= 0,
			VECTORFIELD				= 1,
			MULTIVARIATE			= 2
		};

		struct FileType
		{
			QString			filename;
			DataType		type;
		}									 m_FileType;

		Volume								*m_Volume;						// for Volume-Rendering
		VectorField							*m_VectorField;					// for Flow-Visualisation
		MultiSet							*m_MultiSet;					// for Multivariate Data



		QGLFormat glFormat;

		QTimer *timer = nullptr;

		GLWidget *w;
		
};

#endif // MYTIMER_H

#endif

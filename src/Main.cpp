
#include "MainWindow.h"

#include <QApplication>

#include <QApplication>
#include <QGLFormat>

#include "TriangleWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	
	MainWindow mainWindow;
	mainWindow.show();

	/*
	QSurfaceFormat format;
	format.setSamples(16);

	TriangleWindow window;
	window.setFormat(format);
	window.resize(640, 480);
	window.show();

	window.setAnimating(true);
	//*/

	return app.exec();

}


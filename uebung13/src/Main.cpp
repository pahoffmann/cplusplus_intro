#include <QApplication>
#include "MainWindow.hpp"


int main(int argc, char** argv){


	QApplication app(argc,argv);
	MainWindow window;
	//window.setWindowTile("Bla");

	//window.setFixedSize(500);
	//window.setFixedSize(500);
	window.show();

	return app.exec();

}
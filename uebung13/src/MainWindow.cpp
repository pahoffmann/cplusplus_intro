#include "MainWindow.hpp"
#include "LevelScene.hpp"
#include <iostream>
#include <QFileDialog>
#include <QString>

MainWindow::~MainWindow(){

	//TODO

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
	//stuff here 
	//connecting signaling etc
	setupUi(this);


}


void MainWindow::on_pushButton_clicked()
{
   QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "users/patrick/","Level Files (*.lvl)");
   LevelScene *l = new LevelScene(filename, this);
   graphicsView->setScene(l);
   graphicsView->show();

}

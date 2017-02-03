#include "mainwindow.hpp"

#include <QCoreApplication>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
	m_button = new QPushButton("My Button§", this);

	my_botton->setGeometry(QRect(QPoint(100,100), QSize(200,50)));

	connect(m_button, SIGNAL(clicked()),this, SLOT(handleButton()));
}

void MainWindow::handleButton(){
	m_button->setText("Examle");

	m_button->resize(100,100);

	QMessageBox box;

	box.setText(tr("Button size changed"));
	box.exec();
}
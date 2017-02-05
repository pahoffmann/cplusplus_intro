#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include "../build/ui_untitled.h"
/* Basisfunktionalität & eigenes Window! */



class MainWindow : public QMainWindow, public Ui::MainWindow{
	Q_OBJECT; /* Signaling etc */
public:
	explicit MainWindow(QWidget *parent = 0);

	~MainWindow();


private slots:

    void on_pushButton_clicked();

signals:

private:
	
};
#endif

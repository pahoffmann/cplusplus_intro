#include <QMainWindow>
#include "../build/ui_untitled.h"
/* Basisfunktionalität & eigenes Window! */


/*namespace Ui{
	class MainWindow;
}*/

class MainWindow : public QMainWindow, public Ui::MainWindow{
	Q_OBJECT; /* Signaling etc */
public:
	explicit MainWindow(QWidget *parent = 0);

	~MainWindow();


private slots:
	//void handleButton();
private:
	//QPushButton *m_PushButton;
	
};
#include <QCoreApplication>

namespace Ui{
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
private slots:
	void handleButton();
private:
	QPushButton *m_PushButton;
}
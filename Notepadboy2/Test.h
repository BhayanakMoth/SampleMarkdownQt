#pragma once
#include <QtWidgets/QMainWindow>

QT_USE_NAMESPACE
namespace Ui{
class TestClass;
}
QT_END_NAMESPACE
class Test : public QMainWindow
{
	Q_OBJECT

public:
	Test(QWidget *parent = Q_NULLPTR);
private slots:
	
	//void on_actionBold_triggered();
private:
//    Ui::TestClass ui;

};

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QString>
#include "Document.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
private slots:
	void on_actionSave_triggered();
	void on_actionSave_As_triggered();
	void on_actionBold_triggered();
private:
    Ui::MainWindowClass ui;
	Document m_content;
	QString path;
};

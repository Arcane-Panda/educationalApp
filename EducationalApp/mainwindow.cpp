#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->show();
    ui->Phagocyte->show();
    ui->stackedWidget->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}



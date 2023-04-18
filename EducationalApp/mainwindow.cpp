/***
 * Alex Tokita, Andrew Hokanson, Austin Li, Jonah Thomas, and Lucas Zagal
 * CS3505 - A8 Educational App
 * 18 April 2023
 *
 * This class holds the methods for
 *
 * Code Style Review by:
 */

#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->show();
    ui->Phagocyte->show();
    ui->stackedWidget->setCurrentIndex(2);

    // Setup player movement connections
    connect(this, &MainWindow::keyDown, ui->Phagocyte, &PhagocyteWidget::keyDown);
    connect(this, &MainWindow::keyUp, ui->Phagocyte, &PhagocyteWidget::keyUp);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W:
            emit keyDown(Qt::Key_W);
            break;
        case Qt::Key_A:
            emit keyDown(Qt::Key_A);
            break;
        case Qt::Key_S:
            emit keyDown(Qt::Key_S);
            break;
        case Qt::Key_D:
            emit keyDown(Qt::Key_D);
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W:
            emit keyUp(Qt::Key_W);
            break;
        case Qt::Key_A:
            emit keyUp(Qt::Key_A);
            break;
        case Qt::Key_S:
            emit keyUp(Qt::Key_S);
            break;
        case Qt::Key_D:
            emit keyUp(Qt::Key_D);
            break;
    }
}

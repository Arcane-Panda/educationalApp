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

/**
 * @brief MainWindow::MainWindow Constructs the mainwindow and initializes game levels
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->MazePhagocyte->showMaximized();
    ui->stackedWidget->setCurrentIndex(1);

    // TODO Remove this and add to when change to level 2
    //ui->Level3Phagocyte->setupLevel3();
    ui->MazePhagocyte->setupLevel2();
   // ui->Level3Phagocyte->changeBackground(":/resource/internalBloodVessel.png");
    // Setup player movement connections
    connect(this, &MainWindow::keyDown, ui->MazePhagocyte, &PhagocyteWidget::keyDown);
    connect(this, &MainWindow::keyUp, ui->MazePhagocyte, &PhagocyteWidget::keyUp);


    //LEVEL 1 SETUP-------------
    connect(ui->button1, &QPushButton::clicked, ui->PatternGameDisplay, &PatternGameController::buttonPushed1);
    connect(ui->button2, &QPushButton::clicked, ui->PatternGameDisplay, &PatternGameController::buttonPushed2);
    connect(ui->button3, &QPushButton::clicked, ui->PatternGameDisplay, &PatternGameController::buttonPushed3);
    connect(ui->button4, &QPushButton::clicked, ui->PatternGameDisplay, &PatternGameController::buttonPushed4);
    connect(ui->button5, &QPushButton::clicked, ui->PatternGameDisplay, &PatternGameController::buttonPushed5);
    connect(ui->button6, &QPushButton::clicked, ui->PatternGameDisplay, &PatternGameController::buttonPushed6);
    connect(ui->button7, &QPushButton::clicked, ui->PatternGameDisplay, &PatternGameController::buttonPushed7);
    connect(ui->button8, &QPushButton::clicked, ui->PatternGameDisplay, &PatternGameController::buttonPushed8);
    connect(ui->button9, &QPushButton::clicked, ui->PatternGameDisplay, &PatternGameController::buttonPushed9);

    connect(ui->fireButton, &QPushButton::clicked, ui->PatternGameDisplay, &PatternGameController::checkPattern);
}

/**
 * @brief MainWindow::~MainWindow Destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::keyPressEvent Emits a signal when WASD are pressed
 * @param event Holds the information of which key was pressed
 */
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

/**
 * @brief MainWindow::keyReleaseEvent Emits a signal when WASD are released
 * @param event Holds the information of which key was released
 */
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

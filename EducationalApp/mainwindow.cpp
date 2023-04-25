/***
 * Alex Tokita, Andrew Hokanson, Austin Li, Jonah Thomas, and Lucas Zagal
 * CS3505 - A8 Educational App
 * 18 April 2023
 *
 * This class serves as the interface between the UI and the model code.
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
    ui->stackedWidget->setCurrentIndex(3);

    // TODO Remove this and add to when change to level 2
    ui->Level3Phagocyte->setupLevel3();
    //ui->MazePhagocyte->setupLevel2();
    ui->Level3Phagocyte->changeBackground(":/resource/internalBloodVessel.png");
    // Setup player movement connections
    connect(this, &MainWindow::keyDown, ui->Level3Phagocyte, &PhagocyteWidget::keyDown);
    connect(this, &MainWindow::keyUp, ui->Level3Phagocyte, &PhagocyteWidget::keyUp);


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
    connect(ui->PatternGameDisplay, &PatternGameController::clearButtons, this, &MainWindow::clearButtons);
    connect(ui->PatternGameDisplay, &PatternGameController::flashSelectedButtons, this, &MainWindow::flashSelectedButtons);

    // Level 1 UI
    ui->GreenPattern->setPixmap(QPixmap(":/resource/GreenPattern.png").scaled(163,163,Qt::KeepAspectRatio));
    ui->OrangePattern->setPixmap(QPixmap(":/resource/OrangePattern.png").scaled(163,163,Qt::KeepAspectRatio));
    ui->PinkPattern->setPixmap(QPixmap(":/resource/PinkPattern.png").scaled(163,163,Qt::KeepAspectRatio));
    ui->button1->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button2->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button3->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button4->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button5->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button6->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button7->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button8->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button9->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));

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

/**
 * @brief MainWindow::clearButtons Resets buttons for level 1
 */
void MainWindow::clearButtons()
{
    ui->button1->setChecked(false);
    ui->button2->setChecked(false);
    ui->button3->setChecked(false);
    ui->button4->setChecked(false);
    ui->button5->setChecked(false);
    ui->button6->setChecked(false);
    ui->button7->setChecked(false);
    ui->button8->setChecked(false);
    ui->button9->setChecked(false);
}

/**
 * @brief MainWindow::flashSelectedButtons Flashes buttons when they are clicked in level 1
 * @param color
 */
void MainWindow::flashSelectedButtons(QString color)
{
    if(ui->button1->isChecked())
       ui->button1->setStyleSheet( QString("QPushButton {background-color: " + color + "; border: none;}"));
    if(ui->button2->isChecked())
       ui->button2->setStyleSheet( QString("QPushButton {background-color: " + color + "; border: none;}"));
    if(ui->button3->isChecked())
       ui->button3->setStyleSheet( QString("QPushButton {background-color: " + color + "; border: none;}"));
    if(ui->button4->isChecked())
       ui->button4->setStyleSheet( QString("QPushButton {background-color: " + color + "; border: none;}"));
    if(ui->button5->isChecked())
       ui->button5->setStyleSheet( QString("QPushButton {background-color: " + color + "; border: none;}"));
    if(ui->button6->isChecked())
       ui->button6->setStyleSheet( QString("QPushButton {background-color: " + color + "; border: none;}"));
    if(ui->button7->isChecked())
       ui->button7->setStyleSheet( QString("QPushButton {background-color: " + color + "; border: none;}"));
    if(ui->button8->isChecked())
       ui->button8->setStyleSheet( QString("QPushButton {background-color: " + color + "; border: none;}"));
    if(ui->button9->isChecked())
       ui->button9->setStyleSheet( QString("QPushButton {background-color: " + color + "; border: none;}"));

     QTimer::singleShot(500, this, &MainWindow::unflashSelectedButtons);
}

/**
 * @brief MainWindow::unflashSelectedButtons Changes the color of buttons when they are clicked
 */
void MainWindow::unflashSelectedButtons()
{
    ui->button1->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button2->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button3->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button4->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button5->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button6->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button7->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button8->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button9->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
}


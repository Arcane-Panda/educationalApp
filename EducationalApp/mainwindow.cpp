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
    ui->stackedWidget->setCurrentIndex(1);






    //ui->dialogueBox->hide();

    // TODO Remove this and add to when change to level 2
    //ui->Level3Phagocyte->setupLevel3();
    //ui->MazePhagocyte->setupLevel2();
    ui->Level3Phagocyte->changeBackground(":/resource/internalBloodVessel.png");
    // Setup player movement connections

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
    connect(ui->PatternGameDisplay, &PatternGameController::updateImages, this, &MainWindow::updateImages);
    connect(this, &MainWindow::startLevel1, ui->PatternGameDisplay, &PatternGameController::startLevel1);
    connect(ui->PatternGameDisplay, &PatternGameController::level1Complete, this, &MainWindow::level1Complete);

    level1StartDialogue.push_back("Oh no! Looks like you’ve been invaded by a group of Campylobacter!");
    level1StartDialogue.push_back("Do not fear though! Millions of years of evolution has given us the ability to build complex systems that fend off billions of these bacteria and viruses every day.");
    level1StartDialogue.push_back("While most of us are familiar with white blood cells and antibodies, we often don’t even employ these weapons because of something known as the Complement System! ");
    level1StartDialogue.push_back("The complement system is a giant network of chemistry-guided proteins in your blood that can mitigate attackers and signal for more support from the immune system. You have QUINTILLIONS of these proteins in your blood right now!");
    level1StartDialogue.push_back("The job of the complement system is to cripple intruders, activate the other parts of the immune system, and then assist in ripping invaders apart.");
    level1StartDialogue.push_back("Let’s start off by activating one of the main proteins used in this system, the C3 protein. Match the patterns to start the chain reaction that activates the C3 proteins. The more, the better. ");

    level1EndDialogue.push_back("Good work! Activating the C3 protein causes a chain reaction. This cascading effect is also why this system is sometimes called the Complement Cascade.");
    level1EndDialogue.push_back("When C3 is activated, it splits into two parts. ");
    level1EndDialogue.push_back("The little red dots you see coming off of them is called C3a while the part that remains attached to the bacteria is C3b. C3a goes and floats freely in our vascular system.");
    level1EndDialogue.push_back(" Let's follow where the C3a proteins go! ");

    ui->darknessLevel1->setPixmap(QPixmap(":/resource/darkness.png"));
    ui->darknessLevel1->setGeometry(QRect(0,0,1400,1400));
    ui->dialogueBoxLevel1->setPixmap(QPixmap(":/resource/dialogueBox.png").scaled(1300,275,Qt::KeepAspectRatio));
    ui->drCatDogLevel1->setPixmap(QPixmap(":/resource/DrCatDog1.png"));

    dialogueIndex = 0;
    ui->dialogueLabelLevel1->setText(level1StartDialogue[dialogueIndex]);
    currentState = Level1Start;

    // Level 1 UI
    ui->LeftPattern->setPixmap(QPixmap(":/resource/GreenPattern.png").scaled(103,103,Qt::KeepAspectRatio));
    ui->MiddlePattern->setPixmap(QPixmap(":/resource/OrangePattern.png").scaled(103,103,Qt::KeepAspectRatio));
    ui->RightPattern->setPixmap(QPixmap(":/resource/PinkPattern.png").scaled(163,163,Qt::KeepAspectRatio));
    ui->button1->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button2->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button3->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button4->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button5->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button6->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button7->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button8->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));
    ui->button9->setStyleSheet( QString("QPushButton {background-color: rgb(255,255,255); QPushButton:pressed background-color: rgb(205,205,205); border: none;}"));


    //LEVEL 2 SETUP ---------------------------------------
    ui->darknessLevel2->setPixmap(QPixmap(":/resource/darkness.png"));
    ui->darknessLevel2->setGeometry(QRect(0,0,1400,1400));
    ui->dialogueBoxLevel2->setPixmap(QPixmap(":/resource/dialogueBox.png").scaled(1300,275,Qt::KeepAspectRatio));
    ui->drCatDogLevel2->setPixmap(QPixmap(":/resource/DrCatDog1.png"));

    level2StartDialogue.push_back("This is a phagocyte. It’s a huge cell that devours bacteria. But, in order to do that, it needs to find them first. That’s why we have the C3a proteins floating around. ");
    level2StartDialogue.push_back("C3a acts as a breadcrumb trail for phagocytes (a type of white blood cell) to find the location of the invasion. This allows the phagocytes to follow the breadcrumb trail back to the battlefield to help out. ");
    level2StartDialogue.push_back("Your job is now to help the phagocyte follow the C3a back to where it’s needed! Use W A S D to move around and find your way out.");

    level2EndDialogue.push_back("Great job! The C3a proteins have recruited a phagocyte.");

    connect(this, &MainWindow::keyDown, ui->MazePhagocyte, &PhagocyteWidget::keyDown);
    connect(this, &MainWindow::keyUp, ui->MazePhagocyte, &PhagocyteWidget::keyUp);
    connect(this, &MainWindow::startLevel2, ui->MazePhagocyte, &PhagocyteWidget::startLevel2);
    connect(ui->MazePhagocyte, &PhagocyteWidget::level2Complete, this, &MainWindow::level2Complete);

    //LEVEL 3 SETUP ---------------------------------------
    ui->darknessLevel3->setPixmap(QPixmap(":/resource/darkness.png"));
    ui->darknessLevel3->setGeometry(QRect(0,0,1400,1400));
    ui->dialogueBoxLevel3->setPixmap(QPixmap(":/resource/dialogueBox.png").scaled(1300,275,Qt::KeepAspectRatio));
    ui->drCatDogLevel3->setPixmap(QPixmap(":/resource/DrCatDog1.png"));

    level3StartDialogue.push_back("Now that the phagocyte has arrived, it can start dealing with the introducers via phagocytosis.");
    level3StartDialogue.push_back("Phagocytosis is the process of a cell swallowing up something else. However, this can be tricky sometimes because intruders don’t want to be swallowed!");
    level3StartDialogue.push_back("Luckily, this is where our friend C3b comes in. Earlier, when we started the cascade, the C3b proteins attached themselves to the intruders. Now they create a sort of protein “latch” that allows phagocytes to grab on and lock in pathogens. Now, let’s begin getting rid of this mess.");
    level3StartDialogue.push_back("Use W A S D to move and engulf all the intruders!");

    level3EndDialogue.push_back("Great job! Thanks to the work of the Complement System, the threat has been dealt with and our body stays healthy.");

    connect(this, &MainWindow::keyDown, ui->Level3Phagocyte, &PhagocyteWidget::keyDown);
    connect(this, &MainWindow::keyUp, ui->Level3Phagocyte, &PhagocyteWidget::keyUp);
    connect(this, &MainWindow::startLevel3, ui->Level3Phagocyte, &PhagocyteWidget::startLevel3);
    connect(ui->Level3Phagocyte, &PhagocyteWidget::level3Complete, this, &MainWindow::level3Complete);
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
        cout << "hitting w" << endl;
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
    case Qt::Key_Q:
        advanceDialogue();
        break;

    case Qt::Key_P:
        break;
    }
}


void MainWindow::advanceDialogue()
{
    switch(currentState)
    {
    case Level1Start:

        if(dialogueIndex < (int)level1StartDialogue.size() - 1)
        {
            //advance to next string
            dialogueIndex++;
            ui->dialogueLabelLevel1->setText(level1StartDialogue[dialogueIndex]);
        } else
        {
            //reached end so hide all UI elements and start level 1
            ui->darknessLevel1->hide();
            ui->dialogueLabelLevel1->hide();
            ui->dialogueBoxLevel1->hide();
            ui->drCatDogLevel1->hide();
            emit startLevel1();
            dialogueIndex = 0;
            currentState = Playing;
        }
        break;

    case Level1End:

        if(dialogueIndex < (int)level1EndDialogue.size() - 1)
        {
            //advance to next string
            dialogueIndex++;
            ui->dialogueLabelLevel1->setText(level1EndDialogue[dialogueIndex]);
        } else
        {
            //hide level 1 ui and display level 2 dialogue UI
            ui->darknessLevel1->hide();
            ui->dialogueLabelLevel1->hide();
            ui->dialogueBoxLevel1->hide();
            ui->drCatDogLevel1->hide();
            ui->stackedWidget->setCurrentIndex(2);
            dialogueIndex = 0;
            currentState = Level2Start;

            cout << "should be displaying level 2 UI" << endl;
            ui->darknessLevel2->show();
            ui->dialogueLabelLevel2->show();
            ui->dialogueBoxLevel2->show();
            ui->drCatDogLevel2->show();
            ui->dialogueLabelLevel2->setText(level2StartDialogue[dialogueIndex]);
        }
        break;

    case Level2Start:

        if(dialogueIndex < (int)level2StartDialogue.size() - 1)
        {
            cout << "we advancing the level 2 dialogue" << endl;
            //advance to next string
            dialogueIndex++;
            ui->dialogueLabelLevel2->setText(level2StartDialogue[dialogueIndex]);
        } else
        {
            //hide level 2 dialogue and start level
            ui->darknessLevel2->hide();
            ui->dialogueLabelLevel2->hide();
            ui->dialogueBoxLevel2->hide();
            ui->drCatDogLevel2->hide();
            dialogueIndex = 0;
            currentState = Playing;
            emit startLevel2();
        }
        break;

    case Level2End:

        if(dialogueIndex < (int)level2EndDialogue.size() - 1)
        {
            //advance to next string
            dialogueIndex++;
            ui->dialogueLabelLevel2->setText(level2EndDialogue[dialogueIndex]);
        } else
        {
            //hide level 2 ui and switch to level 3 dialogue
            ui->darknessLevel2->hide();
            ui->dialogueLabelLevel2->hide();
            ui->dialogueBoxLevel2->hide();
            ui->drCatDogLevel2->hide();
            ui->stackedWidget->setCurrentIndex(3);
            dialogueIndex = 0;
            currentState = Level3Start;

            cout << "should be displaying level 2 UI" << endl;
            ui->darknessLevel3->show();
            ui->dialogueLabelLevel3->show();
            ui->dialogueBoxLevel3->show();
            ui->drCatDogLevel3->show();
            ui->dialogueLabelLevel3->setText(level3StartDialogue[dialogueIndex]);
        }
        break;

    case Level3Start:

        if(dialogueIndex < (int)level3StartDialogue.size() - 1)
        {
            cout << "we advancing the level 3 dialogue" << endl;
            //advance to next string
            dialogueIndex++;
            ui->dialogueLabelLevel3->setText(level3StartDialogue[dialogueIndex]);
        } else
        {
            //hide level 3 dialogue and start the level
            ui->darknessLevel3->hide();
            ui->dialogueLabelLevel3->hide();
            ui->dialogueBoxLevel3->hide();
            ui->drCatDogLevel3->hide();
            dialogueIndex = 0;
            currentState = Playing;
            emit startLevel3();
        }
        break;

    case Level3End:

        if(dialogueIndex < (int)level3EndDialogue.size() - 1)
        {
            //advance to next string
            dialogueIndex++;
            ui->dialogueLabelLevel3->setText(level3EndDialogue[dialogueIndex]);
        } else
        {
            //reached end of the game!
            ui->dialogueLabelLevel3->setText("Thanks for playing!");
        }
        break;

    case Playing:
        break;
    }


}

void MainWindow::level1Complete()
{
    currentState = Level1End;
    ui->darknessLevel1->show();
    ui->dialogueLabelLevel1->show();
    ui->dialogueBoxLevel1->show();
    ui->drCatDogLevel1->show();
    ui->dialogueLabelLevel1->setText(level1EndDialogue[dialogueIndex]);
}

void MainWindow::level2Complete()
{
    currentState = Level2End;
    ui->darknessLevel2->show();
    ui->dialogueLabelLevel2->show();
    ui->dialogueBoxLevel2->show();
    ui->drCatDogLevel2->show();
    ui->dialogueLabelLevel2->setText(level2EndDialogue[dialogueIndex]);
}

void MainWindow::level3Complete()
{
    currentState = Level3End;
    ui->darknessLevel3->show();
    ui->dialogueLabelLevel3->show();
    ui->dialogueBoxLevel3->show();
    ui->drCatDogLevel3->show();
    ui->dialogueLabelLevel3->setText(level3EndDialogue[dialogueIndex]);
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

/**
 * @brief MainWindow::updateImages Update the 3 pattern images to reflect the queued and current moves
 * @param image1
 * @param image2
 * @param image3
 */
void MainWindow::updateImages(QPixmap image1, QPixmap image2, QPixmap image3)
{
    ui->LeftPattern->setPixmap(image1.scaled(103,103,Qt::KeepAspectRatio));
    ui->MiddlePattern->setPixmap(image2.scaled(103,103,Qt::KeepAspectRatio));
    ui->RightPattern->setPixmap(image3.scaled(163,163,Qt::KeepAspectRatio));
}



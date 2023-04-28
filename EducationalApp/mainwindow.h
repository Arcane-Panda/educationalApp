/***
 * Alex Tokita, Andrew Hokanson, Austin Li, Jonah Thomas, and Lucas Zagal
 * CS3505 - A8 Educational App
 * 18 April 2023
 *
 * Code Style Review by:
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include "phagocytelevel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void keyDown(Qt::Key);
    void keyUp(Qt::Key);
    void startLevel1();
    void startLevel2();
    void startLevel3();

public slots:
    void clearButtons();
    void flashSelectedButtons(QString);
    void unflashSelectedButtons();
    void updateImages(QPixmap, QPixmap, QPixmap);
    void level1Complete();
    void level2Complete();
    void level3Complete();

private:
    enum levelState {Level1Start, Level1End, Level2Start, Level2End, Level3Start, Level3End, Playing};
    Ui::MainWindow *ui;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    QString getImage(int);
    void advanceDialogue();

    vector<QString> level1StartDialogue;
    vector<QString> level1EndDialogue;
    vector<QString> level2StartDialogue;
    vector<QString> level2EndDialogue;
    vector<QString> level3StartDialogue;
    vector<QString> level3EndDialogue;

    levelState currentState;
    int dialogueIndex;
};

#endif // MAINWINDOW_H

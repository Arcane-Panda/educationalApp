/***
 * Alex Tokita, Andrew Hokanson, Austin Li, Jonah Thomas, and Lucas Zagal
 * CS3505 - A8 Educational App
 * 18 April 2023
 *
 * Code Style Review by:
 */

#ifndef PHAGOCYTEWIDGET_H
#define PHAGOCYTEWIDGET_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <tuple>
#include <vector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

using std::tuple;
using std::vector;

class PhagocyteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhagocyteWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void setupLevel2();
    void setupLevel3();
    void changeBackground(QString fileName);
signals:
    void level2Complete();
    void level3Complete();

public slots:
    void updateWorld();
    void keyDown(Qt::Key);
    void keyUp(Qt::Key);
    void startLevel2();
    void startLevel3();

private:
    b2World world;
    b2Body* body;
    vector<QRect> walls;
    vector<b2Body*> bacteria;
    QTimer timer;
    QImage phagocyteImg[3];
    QImage bacteriaImg[3];
    QImage visionImg;
    QImage backgroundBlood;
    bool wKeyDown;
    bool aKeyDown;
    bool sKeyDown;
    bool dKeyDown;
    int speed;
    int animationCounter;
    double angle;

};

#endif // PHAGOCYTEWIDGET_H

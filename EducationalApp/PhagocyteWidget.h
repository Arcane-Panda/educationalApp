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

class PhagocyteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhagocyteWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void setupMaze();
signals:

public slots:
    void updateWorld();
    void keyDown(Qt::Key);
    void keyUp(Qt::Key);

private:
    b2World world;
    b2Body* body;
    QTimer timer;
    QImage image;
    bool wKeyDown;
    bool aKeyDown;
    bool sKeyDown;
    bool dKeyDown;
    int speed;
    int rotateSpeed;
    double angle;

};

#endif // PHAGOCYTEWIDGET_H

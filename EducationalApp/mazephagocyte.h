#ifndef MAZEPHAGOCYTE_H
#define MAZEPHAGOCYTE_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>

class MazePhagocyte
{
    Q_OBJECT
public:
    explicit MazePhagocyte(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
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

#endif // MAZEPHAGOCYTE_H

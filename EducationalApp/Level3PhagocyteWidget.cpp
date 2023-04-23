/***
 * Alex Tokita, Andrew Hokanson, Austin Li, Jonah Thomas, and Lucas Zagal
 * CS3505 - A8 Educational App
 * 18 April 2023
 *
 * This class holds the methods for a functioning Phagocyte
 *
 * Code Style Review by: Austin
 */

#include "Level2Widget.h"
#include <QPainter>
#include <QDebug>
#include <QRect>
#include <iostream>
using std::cout;
using std::endl;

/**
 * @brief PhagocyteWidget::PhagocyteWidget Constructor
 * @param parent
 */
PhagocyteWidget::PhagocyteWidget(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 0.0f)),
    timer(this),
    visionImg(":/resource/vision.png"),
    backgroundBlood(":/resource/bloodvessels.png")
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(50.0f, 450.0f);

    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2CircleShape hitbox;
    hitbox.m_radius = 25.0f;

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &hitbox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 0.001f;

    // Override the default friction.
    fixtureDef.friction = 50.0f;
    fixtureDef.restitution = 0.2;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    // Player Movement Initialization
    speed = 500;
    angle = 0.0f;
    wKeyDown = false;
    aKeyDown = false;
    sKeyDown = false;
    dKeyDown = false;

    phagocyteImg[0] = QImage(":/resource/Phagocyte1.png");
    phagocyteImg[1] = QImage(":/resource/Phagocyte2.png");
    phagocyteImg[2] = QImage(":/resource/Phagocyte3.png");

    printf("Init world\n");

    connect(&timer, &QTimer::timeout, this, &PhagocyteWidget::updateWorld);
    timer.start(17);
}

void PhagocyteWidget::setupMaze()
{
    QPainter painter(this);
    QFile mazeFile(QString(":/resource/maze.json"));
    if(mazeFile.open(QIODevice::ReadOnly))
    {
        QByteArray wallData = mazeFile.readAll();
        QJsonDocument mazeDoc = QJsonDocument::fromJson(wallData);
        QJsonArray walls = mazeDoc["maze"].toArray();

        for(const QJsonValue &wall : walls)
        {
            int x = wall.toArray()[0].toInt();
            int y = wall.toArray()[1].toInt();
            int w = wall.toArray()[2].toInt();
            int h = wall.toArray()[3].toInt();

            b2BodyDef groundBodyDef;
            groundBodyDef.position.Set(x, y);
            b2Body* groundBody = world.CreateBody(&groundBodyDef);
            b2PolygonShape groundBox;
            groundBox.SetAsBox(w/2, h/2);
            groundBody->CreateFixture(&groundBox, 0.0f);

            this->walls.push_back(QRect(x - w/2, y - h/2, w, h));
        }
    }
}

/**
 * @brief PhagocyteWidget::paintEvent Re-validates properties
 */
void PhagocyteWidget::paintEvent(QPaintEvent *)
{
    animationCounter++;
    int frameIndex = fmod(animationCounter, 40) / 10;
    if (frameIndex == 2)
    {
        frameIndex = 0;
    }
    if (frameIndex == 3)
    {
        frameIndex = 2;
    }
    // Create a painter

    QPainter painter(this);
    b2Vec2 position = body->GetPosition();

    painter.drawImage(QRect(0, 0, 1400, 1400), backgroundBlood);
    QImage rotatedImg = phagocyteImg[frameIndex].transformed(QTransform().rotate(angle));
    float width = 50 * (cos((fmod(abs(angle), 90.0f) / 180 * M_PI)) + sin((fmod(abs(angle), 90.0f) / 180 * M_PI)));
    painter.drawImage(QRect((int)(position.x) - width / 2, (int)(position.y) - width / 2, width, width), rotatedImg);
    for(QRect wall: walls)
    {
        painter.fillRect(wall, QBrush(Qt::yellow));
    }
    painter.drawImage(QRect((int)(position.x) - 1500, (int)(position.y) - 1500, 3000, 3000), visionImg);
    painter.end();
}

/**
 * @brief PhagocyteWidget::updateWorld
 */
void PhagocyteWidget::updateWorld()
{
    // User Input Deciphering

    if(aKeyDown)
    {
        angle -= 2;
    }
    else if(dKeyDown)
    {
        angle += 2;
    }
    angle = fmod(angle, 360.0f);

    if(wKeyDown)
    {
        b2Vec2 forceVec = b2Vec2(speed * cos(angle * M_PI/180), speed * sin(angle * M_PI/180));
        body->ApplyForceToCenter(forceVec, true);
    }
    else if(sKeyDown)
    {
        b2Vec2 forceVec = b2Vec2(-speed * cos(angle * M_PI/180), -speed * sin(angle * M_PI/180));
        body->ApplyForceToCenter(forceVec, true);
    }

    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
}

void PhagocyteWidget::keyDown(Qt::Key key)
{
    switch (key)
    {
        case Qt::Key_W:
            wKeyDown = true;
            break;
        case Qt::Key_A:
            aKeyDown = true;
            break;
        case Qt::Key_S:
            sKeyDown = true;
            break;
        case Qt::Key_D:
            dKeyDown = true;
            break;
        default:
            break;
    }
}

void PhagocyteWidget::keyUp(Qt::Key key)
{
    switch (key)
    {
        case Qt::Key_W:
            wKeyDown = false;
            break;
        case Qt::Key_A:
            aKeyDown = false;
            break;
        case Qt::Key_S:
            sKeyDown = false;
            break;
        case Qt::Key_D:
            dKeyDown = false;
            break;
        default:
            break;
    }
}

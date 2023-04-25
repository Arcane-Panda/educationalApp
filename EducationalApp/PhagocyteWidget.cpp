/***
 * Alex Tokita, Andrew Hokanson, Austin Li, Jonah Thomas, and Lucas Zagal
 * CS3505 - A8 Educational App
 * 18 April 2023
 *
 * This class holds the methods for a functioning Phagocyte
 *
 * Code Style Review by: Austin
 */

#include "PhagocyteWidget.h"
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

    bacteriaImg[0] = QImage(":/resource/Bacteria1.png");
    bacteriaImg[1] = QImage(":/resource/Bacteria2.png");
    bacteriaImg[2] = QImage(":/resource/Bacteria3.png");

    printf("Init world\n");

    connect(&timer, &QTimer::timeout, this, &PhagocyteWidget::updateWorld);
    timer.start(17);
}

/**
 * @brief PhagocyteWidget::changeBackground Changes the background image of the window
 * @param fileName The background image file
 */
void PhagocyteWidget::changeBackground(QString fileName)
{
    backgroundBlood = QImage(fileName);
}

/**
 * @brief PhagocyteWidget::setupLevel2 Adds level 2 game objects to the widget
 */
void PhagocyteWidget::setupLevel2()
{
    // Draw maze borders
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

            b2BodyDef wallBodyDef;
            wallBodyDef.position.Set(x, y);
            b2Body* wallBody = world.CreateBody(&wallBodyDef);
            b2PolygonShape wallBox;
            wallBox.SetAsBox(w/2, h/2);
            wallBody->CreateFixture(&wallBox, 0.0f);

            this->walls.push_back(QRect(x - w/2, y - h/2, w, h));
        }
    }
}

/**
 * @brief PhagocyteWidget::setupLevel3 Adds level 3 game objects into the widget
 */
void PhagocyteWidget::setupLevel3()
{
    // Draw game borders
    int borderWallInfo[4][4] {{700, 0, 1400, 10}, {0, 400,10, 800}, {700, 772, 1400, 10}, {1372, 400, 10, 800}};
    for(int i = 0; i < 4; i++)
    {
        int x = borderWallInfo[i][0];

            int y = borderWallInfo[i][1];
            int w = borderWallInfo[i][2];
            int h = borderWallInfo[i][3];

            b2BodyDef wallBodyDef;
        wallBodyDef.position.Set(x, y);
        b2Body* wallBody = world.CreateBody(&wallBodyDef);
        b2PolygonShape wallBox;
        wallBox.SetAsBox(w/2, h/2);
        wallBody->CreateFixture(&wallBox, 0.0f);
        this->walls.push_back(QRect(x - w/2, y - h/2, w, h));
    }

    // Draw bacteria from JSON file
    QFile bacteriaFile(QString(":/resource/bacteria.json"));
    if(bacteriaFile.open(QIODevice::ReadOnly))
    {
        QByteArray bacteriaData = bacteriaFile.readAll();
        QJsonDocument bacteriaDoc = QJsonDocument::fromJson(bacteriaData);
        QJsonArray bacteriaArray = bacteriaDoc["bacteria"].toArray();

        std::cout << bacteriaArray.size() << std::endl;
        for(const QJsonValue &bacterium : bacteriaArray)
        {
            int x = bacterium.toArray()[0].toInt();
            int y = bacterium.toArray()[1].toInt();

            b2BodyDef bacteriaBodyDef;
            bacteriaBodyDef.position.Set(x+32, y+32);
            b2Body* bacteriaBody = world.CreateBody(&bacteriaBodyDef);
            b2PolygonShape hitBox;
            hitBox.SetAsBox(8, 8);
            bacteriaBody->CreateFixture(&hitBox, 0.0f);

            this->bacteria.push_back(bacteriaBody);
            bacteriaBody->SetTransform(bacteriaBody->GetPosition(), rand()%360);
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

    painter.drawImage(QRect(0, 0, 1400, 800), backgroundBlood);


    //Draw Phagocyte
    QImage rotatedImg = phagocyteImg[frameIndex].transformed(QTransform().rotate(angle));
    float width = 50 * (cos((fmod(abs(angle), 90.0f) / 180 * M_PI)) + sin((fmod(abs(angle), 90.0f) / 180 * M_PI)));
    painter.drawImage(QRect((int)(position.x) - width / 2, (int)(position.y) - width / 2, width, width), rotatedImg);

    //Draw Bacteria
    for(b2Body* bacterium : bacteria)
    {
        b2Vec2 bacteriaPos = bacterium->GetPosition();
        rotatedImg = bacteriaImg[frameIndex].transformed(QTransform().rotate(bacterium->GetAngle()));
        painter.drawImage(QRect((int)(bacteriaPos.x)-32,  (int)(bacteriaPos.y)-32  , 64, 64), rotatedImg);
    }

   // width = 50 * (cos((fmod(abs(angle), 90.0f) / 180 * M_PI)) + sin((fmod(abs(angle), 90.0f) / 180 * M_PI)));


    for(QRect wall: walls)
    {
        painter.fillRect(wall, QBrush(Qt::yellow));
    }

    //fog of war
    //put an if around this?
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

    //check collisions
    for(b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next)
    {
        b2Body* bacteriaBody = edge->contact->GetFixtureA()->GetBody();
        for(int i = 0; i < (int)bacteria.size(); i++)
        {
            if(bacteria[i] == bacteriaBody)
            {
                bacteria.erase(bacteria.begin()+i);
                world.DestroyBody(bacteriaBody);
            }
        }
    }


    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
}

/**
 * @brief PhagocyteWidget::keyDown Updates the widgets WASD key pressed states (pressed)
 * @param key
 */
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

/**
 * @brief PhagocyteWidget::keyUp Updates the widgets WASD key pressed states (released)
 * @param key
 */
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

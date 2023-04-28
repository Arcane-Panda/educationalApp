/***
 * Alex Tokita, Andrew Hokanson, Austin Li, Jonah Thomas, and Lucas Zagal
 * CS3505 - A8 Educational App
 * 27 April 2023
 *
 * This class serves as the model for a level featuring a moveable phagocyte— either
 * with walls to avoid or with
 */

#include "PhagocyteLevel.h"
#include <QPainter>
#include <QDebug>
#include <QRect>
#include <iostream>
using std::cout;
using std::endl;

/**
 * @brief PhagocyteLevel::PhagocyteLevel Constructor
 * @param parent
 */
PhagocyteLevel::PhagocyteLevel(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 0.0f)),
    timer(this),
    visionImg(":/resource/vision.png"),
    backgroundImg(":/resource/bloodvessels.png")
{
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(50.0f, 450.0f);

    phagocyteBody = world.CreateBody(&bodyDef);

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
    phagocyteBody->CreateFixture(&fixtureDef);

    // Player Movement Initialization
    speed = 500;
    angle = 0.0f;
    wKeyDown = false;
    aKeyDown = false;
    sKeyDown = false;
    dKeyDown = false;

    // Load in the animation sequence for Phagocyte
    phagocyteImg[0] = QImage(":/resource/Phagocyte1.png");
    phagocyteImg[1] = QImage(":/resource/Phagocyte2.png");
    phagocyteImg[2] = QImage(":/resource/Phagocyte3.png");
    // Load in the animation sequence for Bacteria
    bacteriaImg[0] = QImage(":/resource/Bacteria1.png");
    bacteriaImg[1] = QImage(":/resource/Bacteria2.png");
    bacteriaImg[2] = QImage(":/resource/Bacteria3.png");
}

/**
 * @brief PhagocyteLevel::addWallsFromFile adds walls to the level's world based on a json file
 * that contains an array of 4-int-tuples, each of which represents a walls center x coordinate,
 * center y coordinate, width, and height respectively.
 * @param filename the name of the file from which to add walls
 */
void PhagocyteLevel::addWallsFromFile(QString filename)
{
    QFile wallsFile(filename);
    if(wallsFile.open(QIODevice::ReadOnly))
    {
        // Read from wall
        QByteArray wallData = wallsFile.readAll();
        QJsonDocument wallsDoc = QJsonDocument::fromJson(wallData);
        QJsonArray walls = wallsDoc["walls"].toArray();

        // Add in colliders for each wall and add dimensions for drawing
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
 * @brief PhagocyteLevel::startLevel2 Does the necessary setup for level 2 and starts the world update timer
 */
void PhagocyteLevel::startLevel2()
{
    // add the maze walls to the world
    addWallsFromFile(QString(":/resource/maze.json"));

    // Timer
    connect(&timer, &QTimer::timeout, this, &PhagocyteLevel::updateWorld);
    timer.start(17);
}

/**
 * @brief PhagocyteLevel::startLevel3 Does the necessary setup for level 3 and starts the world update timer
 */
void PhagocyteLevel::startLevel3()
{
    // Define game boundaries
    addWallsFromFile(QString(":/resource/borderwalls.json"));

    // Draw bacteria from JSON file
    QFile bacteriaFile(QString(":/resource/bacteria.json"));
    if(bacteriaFile.open(QIODevice::ReadOnly))
    {
        QByteArray bacteriaData = bacteriaFile.readAll();
        QJsonDocument bacteriaDoc = QJsonDocument::fromJson(bacteriaData);
        QJsonArray bacteriaArray = bacteriaDoc["bacteria"].toArray();

        // Define bacteria colliders and set them up for drawing
        for(const QJsonValue &bacterium : bacteriaArray)
        {
            int x = bacterium.toArray()[0].toInt();
            int y = bacterium.toArray()[1].toInt();

            b2BodyDef bacteriumBodyDef;
            bacteriumBodyDef.position.Set(x+32, y+32);
            b2Body* bacteriumBody = world.CreateBody(&bacteriumBodyDef);
            b2PolygonShape hitBox;
            hitBox.SetAsBox(8, 8);
            bacteriumBody->CreateFixture(&hitBox, 0.0f);

            // add the current bacterium to the master list and give it a random rotation
            this->bacteria.push_back(bacteriumBody);
            bacteriumBody->SetTransform(bacteriumBody->GetPosition(), rand() * 360.0);
        }
    }

    // Timer
    connect(&timer, &QTimer::timeout, this, &PhagocyteLevel::updateWorld);
    timer.start(17);
}

/**
 * @brief PhagocyteLevel::changeBackground Changes the background image of the window
 * @param fileName The background image file
 */
void PhagocyteLevel::changeBackground(QString fileName)
{
    backgroundImg = QImage(fileName);
}

/**
 * @brief PhagocyteLevel::paintEvent Repaints the world, including all walls, all bacteria, and the phagocyte
 */
void PhagocyteLevel::paintEvent(QPaintEvent *)
{
    // Define which animation frame to display -- sequence is 1,2,3,2,1,2,3,etc
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
    b2Vec2 position = phagocyteBody->GetPosition();

    painter.drawImage(QRect(0, 0, 1400, 800), backgroundImg);

    // Draw the phagocyte at its current rotation
    QImage rotatedImg = phagocyteImg[frameIndex].transformed(QTransform().rotate(angle));
    float width = 50 * (cos((fmod(abs(angle), 90.0f) / 180 * M_PI)) + sin((fmod(abs(angle), 90.0f) / 180 * M_PI)));
    painter.drawImage(QRect((int)(position.x) - width / 2, (int)(position.y) - width / 2, width, width), rotatedImg);

    // Draw each bacterium
    for(b2Body* bacterium : bacteria)
    {
        b2Vec2 bacteriaPos = bacterium->GetPosition();
        rotatedImg = bacteriaImg[frameIndex].transformed(QTransform().rotate(bacterium->GetAngle()));
        painter.drawImage(QRect((int)(bacteriaPos.x)-32,  (int)(bacteriaPos.y)-32  , 64, 64), rotatedImg);
    }

    // Draw the walls
    for(QRect wall: walls)
    {
        painter.fillRect(wall, QBrush(Qt::red));
    }

    // Draw the "Fog of War"
    painter.drawImage(QRect((int)(position.x) - 1500, (int)(position.y) - 1500, 3000, 3000), visionImg);
    painter.end();
}

/**
 * @brief PhagocyteLevel::updateWorld updates the world, including applying forces to bodies, registering
 * user input, and
 */
void PhagocyteLevel::updateWorld()
{
    // Update phagocyte angle based on player input
    if(aKeyDown)
    {
        angle -= 2;
    }
    else if(dKeyDown)
    {
        angle += 2;
    }
    angle = fmod(angle, 360.0f);

    // Apply forces to phagocyte based on player input
    if(wKeyDown)
    {
        b2Vec2 forceVec = b2Vec2(speed * cos(angle * M_PI/180), speed * sin(angle * M_PI/180));
        phagocyteBody->ApplyForceToCenter(forceVec, true);
    }
    else if(sKeyDown)
    {
        b2Vec2 forceVec = b2Vec2(-speed * cos(angle * M_PI/180), -speed * sin(angle * M_PI/180));
        phagocyteBody->ApplyForceToCenter(forceVec, true);
    }

    // Check for any collisions between the phagocyte and the bacteria,
    // consuming any bacteria that do collide
    for(b2ContactEdge* edge = phagocyteBody->GetContactList(); edge; edge = edge->next)
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

    // Advance the world at a fixed time step and iterations
    world.Step(1.0/60.0, 6, 2);
    update(); // trigger repainting

    // Check level completion conditions
    if(phagocyteBody->GetPosition().x > 1400)
    {
        emit level2Complete();
        timer.stop();
    } else if(walls.size() == 4 && bacteria.empty())
    {
        emit level3Complete();
        timer.stop();
    }
}

/**
 * @brief PhagocyteLevel::keyDown Updates the widgets WASD key pressed states (pressed)
 * @param key
 */
void PhagocyteLevel::keyDown(Qt::Key key)
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
 * @brief PhagocyteLevel::keyUp Updates the widgets WASD key pressed states (released)
 * @param key
 */
void PhagocyteLevel::keyUp(Qt::Key key)
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

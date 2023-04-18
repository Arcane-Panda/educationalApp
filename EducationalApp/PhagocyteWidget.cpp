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
    image(":/resource/phagocyte.png")
{
    // Define the ground body.
    //b2BodyDef groundBodyDef;
    //groundBodyDef.position.Set(0.0f, 20.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    //b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    //b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    //groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    //groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);

    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 50.0f;
    fixtureDef.restitution = 0.9;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    // Player Movement Initialization
    speed = 50;
    rotateSpeed = 25.0f;
    wKeyDown = false;
    aKeyDown = false;
    sKeyDown = false;
    dKeyDown = false;

    printf("Init world\n");

    connect(&timer, &QTimer::timeout, this, &PhagocyteWidget::updateWorld);
    timer.start(10);
}

/**
 * @brief PhagocyteWidget::paintEvent Re-validates properties
 */
void PhagocyteWidget::paintEvent(QPaintEvent *)
{
    // Create a painter
    QPainter painter(this);
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();

    //printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

    // TODO how to draw image at rotation?
    QPoint globalCursorPos = QCursor::pos();
    painter.drawImage(QRect(globalCursorPos.x() - 25, globalCursorPos.y() - 45, 50, 50), image);
    painter.drawImage(QRect((int)(position.x), (int)(position.y), 50, 50), image);
    //painter.drawImage(QRect(10, 10, 30, 30), image);
//    qDebug() << image;
    painter.end();
}

/**
 * @brief PhagocyteWidget::updateWorld
 */
void PhagocyteWidget::updateWorld()
{
    // User Input Deciphering
    /*
    //b2Vec2 force = b2Vec2(0,0);
    b2Vec2 force = b2Vec2(speed * cos((body->GetAngle() * M_PI) / 180), -speed * sin((body->GetAngle() * M_PI) / 180));
    int dir = 0;

    // Forward Backward Movement first
    if (wKeyDown)
    {
        force = b2Vec2(body->GetMass() * speed * cos((body->GetAngle() * M_PI) / 180), body->GetMass() * speed * sin((body->GetAngle() * M_PI) / 180));
        cout << body->GetAngle() << endl;
        cout << force.x << " " << force.y << endl;
    }
    else if (sKeyDown)
    {
        force = b2Vec2(body->GetMass() * -speed * cos((body->GetAngle() * M_PI) / 180), body->GetMass() * -speed * sin((body->GetAngle() * M_PI) / 180));
        cout << aKeyDown << endl;
    }
    body->ApplyForceToCenter(force, true);

    // Secondly Left Right Rotation
    if (aKeyDown)
    {
        dir = 1;
    }
    else if (dKeyDown)
    {
        dir = -1;
    }
    body->SetAngularVelocity(rotateSpeed * dir);
    */

    QPoint globalCursorPos = QCursor::pos();
    b2Vec2 toMouse(globalCursorPos.x(), globalCursorPos.y());
    toMouse -= (b2Vec2(body->GetPosition().x + 25, body->GetPosition().y + 45));
    body->ApplyForceToCenter(toMouse, true);

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

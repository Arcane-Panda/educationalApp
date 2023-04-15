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

/**
 * @brief PhagocyteWidget::PhagocyteWidget Constructor
 * @param parent
 */
PhagocyteWidget::PhagocyteWidget(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 10.0f)),
    timer(this),
    image(":/resource/phagocyte.png")
{
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 20.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);

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
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9;
    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
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

//    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

    painter.drawImage((int)(position.x), (int)(position.y), image);
    painter.drawImage(QRect(10, 10, 30, 30), image);
//    qDebug() << image;
    painter.end();
}

/**
 * @brief PhagocyteWidget::updateWorld
 */
void PhagocyteWidget::updateWorld()
{
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
}

// Movement methods
/**
 * @brief PhagocyteWidget::moveForward Applies a standardized force vector in the direction this Phagocyte is facing
 */
void PhagocyteWidget::moveForward()
{

}

/**
 * @brief PhagocyteWidget::moveBackward Applies a standardized force vector in the opposite direction this Phagocyte is facing
 */
void PhagocyteWidget::moveBackward()
{
    // TODO: Really no clue if this works lol
    //body->ApplyForceToCenter(b2Vec2());
}

/**
 * @brief PhagocyteWidget::rotate Rotates this Phagocyte in the specified direction
 * @param dir A negative or positive integer that indicates left or right respectively
 */
void PhagocyteWidget::rotate(int dir)
{
    // TODO: Really no clue if this works lol
    body->ApplyTorque(dir*10, true);
}



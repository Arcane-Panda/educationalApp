
#ifndef BACTERIA_H
#define BACTERIA_H


#include <QObject>
#include <Box2D/Box2D.h>


class Bacteria
{
public:
    Bacteria();
    b2BodyDef* GetBodyDef();
    bool GetCollision();
private:
    b2BodyDef bodyDef;
    b2Body* body;
    b2PolygonShape bodyShape;
};

#endif // BACTERIA_H

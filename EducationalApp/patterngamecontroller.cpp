#include "patterngamecontroller.h"
#include "qpainter.h"

PatternGameController::PatternGameController(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 0.0f))
{
    greenPattern = {1, 2, 5, 6, 7, 8};
    pinkPattern = {3, 4, 5, 6, 7, 9};
    orangePattern = {4, 5, 8, 9};
    greenImage = QImage(":/resource/GreenPattern.png");
    orangeImage = QImage(":/resource/OrangePattern.png");
    pinkImage = QImage(":/resource/PinkPattern.png");

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(200.0f, 200.0f);

    bacteria = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2CircleShape hitbox;
    hitbox.m_radius = 10.0f;

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &hitbox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 0.001f;

    // Override the default friction.
    fixtureDef.friction = 50.0f;
    fixtureDef.restitution = 0.2;
    // Add the shape to the body.
    bacteria->CreateFixture(&fixtureDef);

    connect(&timer, &QTimer::timeout, this, &PatternGameController::updateWorld);
    timer.start(17);
}

void PatternGameController::checkPattern(bool pushed)
{

    for(auto it = entered.begin(); it != entered.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    //Check to see if the entered pattern matches any of the correct patterns
    if(compareSets(&entered, &greenPattern))
    {
        emit flashSelectedButtons(QString("rgb(23,186,62)"));
        createProteins(0);
        cout << "Matches green!" << endl;
    }
    else if(compareSets(&entered, &pinkPattern))
    {
        emit flashSelectedButtons(QString("rgb(254,170,202)"));
        createProteins(1);
        cout << "Matches pink!" << endl;
    }
    else if (compareSets(&entered, &orangePattern))
    {
        emit flashSelectedButtons(QString("rgb(218,164,2)"));
        createProteins(2);
        cout << "Matches orange!" << endl;
    }
    else
    {
        cout << "Matches none :(" << endl;
    }


    //Clear the selected pattern
    entered.clear();
    emit clearButtons();
}

bool PatternGameController::compareSets(set<int>* set1, set<int>* set2)
{
    //If the sets are different sizes, return false
    if(set1->size() != set2->size())
        return false;

    //Go though each element
    for (int num : *set1)
    {
        //If the element isn't in the other set, return false
        if (set2->find(num) == set2->end())
            return false;
    }

    //Else return true
    return true;
}

void PatternGameController::updateEntered(int button, bool selected)
{
    if(selected)
        entered.insert(button);
    else
    {
        entered.erase(button);
    }
}

void PatternGameController::buttonPushed1(bool pushed)
{
    updateEntered(1, pushed);
}

void PatternGameController::buttonPushed2(bool pushed)
{
    updateEntered(2, pushed);
}

void PatternGameController::buttonPushed3(bool pushed)
{
    updateEntered(3, pushed);
}

void PatternGameController::buttonPushed4(bool pushed)
{
    updateEntered(4, pushed);
}

void PatternGameController::buttonPushed5(bool pushed)
{
    updateEntered(5, pushed);
}

void PatternGameController::buttonPushed6(bool pushed)
{
    updateEntered(6, pushed);
}

void PatternGameController::buttonPushed7(bool pushed)
{
    updateEntered(7, pushed);
}

void PatternGameController::buttonPushed8(bool pushed)
{
    updateEntered(8, pushed);
}

void PatternGameController::buttonPushed9(bool pushed)
{
    updateEntered(9, pushed);
}

void PatternGameController::createProteins(int color)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(340.0f, 340.0f); // TODO randomize in circle?

    protein = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2CircleShape hitbox;
    hitbox.m_radius = 5.0f;

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &hitbox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 0.001f;

    // Override the default friction.
    fixtureDef.friction = 50.0f;
    fixtureDef.restitution = 0.2;
    // Add the shape to the body.
    protein->CreateFixture(&fixtureDef);

    // Add Protein and body to map so that it knows its color?
    switch (color)
    {
    case 0: // Green
        break;
    case 1: // Pink

        break;
    case 2: // Orange

        break;
    }
}

/**
 * @brief PatternGameController::updateWorld
 */
void PatternGameController::updateWorld()
{
    // Move All Bacteria Towards the cell (don't if it has been marked with proteins)

    b2Vec2 center = b2Vec2(340, 340);
    b2Vec2 forceVec = b2Vec2(center.x - bacteria->GetPosition().x, center.y - bacteria->GetPosition().y);
    bacteria->ApplyForceToCenter(forceVec, true);

    // Spawn in bacteria some kind of wave

    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
}

/**
 * @brief PatternGameController::paintEvent Re-validates properties
 */
void PatternGameController::paintEvent(QPaintEvent *)
{
    // Create a painter
    QPainter painter(this);

    painter.drawImage(QRect(bacteria->GetPosition().x - 10, bacteria->GetPosition().y - 10, 20, 20), greenImage);
    if (protein)
    {
        painter.drawImage(QRect(protein->GetPosition().x - 5, protein->GetPosition().y - 5, 10, 10), orangeImage);
    }
    painter.end();
}

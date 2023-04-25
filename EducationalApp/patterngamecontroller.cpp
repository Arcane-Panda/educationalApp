#include "patterngamecontroller.h"
#include "qpainter.h"

PatternGameController::PatternGameController(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 0.0f))
{
    //set matching patterns
    greenPattern = {1, 2, 5, 6, 7, 8};
    orangePattern = {4, 5, 8, 9};
    pinkPattern = {3, 4, 5, 6, 7, 9};
    bluePattern = {1, 2, 3, 5, 8};
    lightBluePattern = {1, 4, 6, 7, 8, 9};
    purplePattern = {2, 4, 5, 6, 8};
    yellowPattern = {1, 3, 5, 7, 9};

    //create mappings from ints to pattern sets
    patternMapping[0] = greenPattern;
    patternMapping[1] = orangePattern;
    patternMapping[2] = pinkPattern;
    patternMapping[3] = bluePattern;
    patternMapping[4] = lightBluePattern;
    patternMapping[5] = purplePattern;
    patternMapping[6] = yellowPattern;

    //create mappings from ints to colors
    colorMapping[0] = QString("rgb(23,186,62)");
    colorMapping[1] = QString("rgb(218,164,2)");
    colorMapping[2] = QString("rgb(254,170,202)");
    colorMapping[3] = QString("rgb(32,32,255)");
    colorMapping[4] = QString("rgb(160,244,255)");
    colorMapping[5] = QString("rgb(185, 64, 255)");
    colorMapping[6] = QString("rgb(255,244,160)");

    //create mappings from ints to QPixmap images
    imageMapping[0] = QPixmap(QString(":/resource/GreenPattern.png"));
    imageMapping[1] = QPixmap(QString(":/resource/OrangePattern.png"));
    imageMapping[2] = QPixmap(QString(":/resource/PinkPattern.png"));
    imageMapping[3] = QPixmap(QString(":/resource/BluePattern.png"));
    imageMapping[4] = QPixmap(QString(":/resource/LightBluePattern.png"));
    imageMapping[5] = QPixmap(QString(":/resource/PurplePattern.png"));
    imageMapping[6] = QPixmap(QString(":/resource/YellowPattern.png"));

    bacteriaImage = QImage(":/resource/Bacteria1.png");
    defendCellImage = QImage(":/resource/Cell.png");
    c3ProteinImage = QImage(":/resource/ProteinSprite.png");

    //fill the queued patterns
    queuedPatterns.push_back(0);
    queuedPatterns.push_back(1);
    queuedPatterns.push_back(2);

    b2BodyDef cellBodyDef;
    cellBodyDef.position.Set(340, 340);
    b2Body* cellBody = world.CreateBody(&cellBodyDef);
    b2CircleShape hitbox;
    hitbox.m_radius = 30.0f;

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &hitbox;
    fixtureDef.filter.groupIndex = 3;
    cellBody->CreateFixture(&fixtureDef);

    framesTillNextSpawn = 300;
    bacteriaWave = 0;
    score = 100;
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
    if(compareSets(&entered, &patternMapping[queuedPatterns[2]]))
    {
       emit flashSelectedButtons(colorMapping[queuedPatterns[2]]);
       createProteins(2);
       updateDisplayedPatterns();
       cout << "Matches!" << endl;
    }
    else
    {
       emit flashSelectedButtons(QString("rgb(255,30,30)"));
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

void PatternGameController::createBacteria(int count)
{
    for (int i = 0; i < count; i++)
    {
        b2BodyDef bacteriaBodyDef;
        int angle = (rand() * 360);
        bacteriaBodyDef.position.Set(340 + 330 * cos(angle), 340 + 330 * sin(angle));
        bacteriaBodyDef.type = b2_dynamicBody;
        b2Body* bacteriaBody = world.CreateBody(&bacteriaBodyDef);
        b2CircleShape hitbox;
        hitbox.m_radius = 10.0f;

        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &hitbox;
        fixtureDef.filter.groupIndex = 1;
        bacteriaBody->CreateFixture(&fixtureDef);

        this->bacterium.push_back(bacteriaBody);
    }
}

void PatternGameController::createProteins(int count)
{
    for (int i = 0; i < count; i++)
    {
        b2BodyDef proteinBodyDef;
        int angle = (rand() % 360);
        proteinBodyDef.position.Set(340 + 35 * cos(angle), 340 + 35 * sin(angle));
        proteinBodyDef.type = b2_dynamicBody;
        b2Body* proteinBody = world.CreateBody(&proteinBodyDef);
        b2CircleShape hitbox;
        hitbox.m_radius = 5.0f;

        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.filter.groupIndex = 2;
        fixtureDef.shape = &hitbox;
        proteinBody->CreateFixture(&fixtureDef);

        this->proteins.push_back(proteinBody);
    }
}

/**
 * @brief PatternGameController::updateWorld
 */
void PatternGameController::updateWorld()
{
    // Move All Bacteria Towards the cell (don't if it has been marked with proteins)

    getOutOfCurrentBacteria:
    for(b2Body* bacteriaBody : bacterium)
    {
        b2Vec2 center = b2Vec2(340, 340);
        b2Vec2 forceVec = b2Vec2(center.x - bacteriaBody->GetPosition().x, center.y - bacteriaBody->GetPosition().y);
        bacteriaBody->ApplyForceToCenter(forceVec, true);

        int bacteriaKey;

        for(int i = 0; i < (int)bacterium.size(); i++)
        {
            if(bacterium[i] == bacteriaBody)
            {
                bacteriaKey = i;
            }
        }

        for(b2ContactEdge* edge = bacteriaBody->GetContactList(); edge; edge = edge->next)
        {
            b2Body* collideBody = edge->contact->GetFixtureA()->GetBody();
            for(int i = 0; i < (int)proteins.size(); i++)
            {
                if(proteins[i] == collideBody)
                {
                    proteins.erase(proteins.begin()+i);
                    world.DestroyBody(collideBody);
                    bacterium.erase(bacterium.begin()+bacteriaKey);
                    world.DestroyBody(bacteriaBody);
                    goto getOutOfCurrentBacteria;
                }
            }
        }
    }

    // Check for collisions between every bacteria and protein TODO



    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);

    // Every 3 seconds another wave of bacteria comes
    framesTillNextSpawn--;
    if (framesTillNextSpawn < 0)
    {
        framesTillNextSpawn = 300;
        bacteriaWave += rand() % 2;
        createBacteria(bacteriaWave);
    }
    update();
}

/**
 * @brief PatternGameController::paintEvent Re-validates properties
 */
void PatternGameController::paintEvent(QPaintEvent *)
{
    // Create a painter
    QPainter painter(this);

    for(b2Body* bacteriaBody : bacterium)
    {
        cout << "drawn bacteria" << endl;
        painter.drawImage(QRect(bacteriaBody->GetPosition().x - 10, bacteriaBody->GetPosition().y - 10, 20, 20), bacteriaImage);
    }
    for(b2Body* proteinBody : proteins)
    {
        painter.drawImage(QRect(proteinBody->GetPosition().x - 5, proteinBody->GetPosition().y - 5, 10, 10), c3ProteinImage);
    }

    painter.drawImage(QRect(310, 310, 60, 60), defendCellImage);

    painter.end();
}

/**
 * @brief PatternGameController::updateDisplayedPatterns Updates the current and queued patterns
 */
void PatternGameController::updateDisplayedPatterns()
{
    //shift the moves and add a new random move
    queuedPatterns[2] = queuedPatterns[1];
    queuedPatterns[1] = queuedPatterns[0];
    queuedPatterns[0] = rand() % 7;

    //updates the view by sending in the images to the MainWindow
    emit updateImages(imageMapping[queuedPatterns[0]], imageMapping[queuedPatterns[1]], imageMapping[queuedPatterns[2]]);
}

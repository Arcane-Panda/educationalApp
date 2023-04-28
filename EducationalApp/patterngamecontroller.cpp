/***
 * Alex Tokita, Andrew Hokanson, Austin Li, Jonah Thomas, and Lucas Zagal
 * CS3505 - A8 Educational App
 * 27 April 2023
 *
 * This class serves as te model for the pattern matching game.
 */

#include "patterngamecontroller.h"
#include "qpainter.h"

/**
 * @brief PatterGameController::PatternGameController Constructor
 * @param parent
 */
PatternGameController::PatternGameController(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 0.0f))
{
    // set matching patterns
    greenPattern = {1, 2, 5, 6, 7, 8};
    orangePattern = {4, 5, 8, 9};
    pinkPattern = {3, 4, 5, 6, 7, 9};
    bluePattern = {1, 2, 3, 5, 8};
    lightBluePattern = {1, 4, 6, 7, 8, 9};
    purplePattern = {2, 4, 5, 6, 8};
    yellowPattern = {1, 3, 5, 7, 9};

    // create mappings from ints to pattern sets
    patternMapping[0] = greenPattern;
    patternMapping[1] = orangePattern;
    patternMapping[2] = pinkPattern;
    patternMapping[3] = bluePattern;
    patternMapping[4] = lightBluePattern;
    patternMapping[5] = purplePattern;
    patternMapping[6] = yellowPattern;

    // create mappings from ints to colors
    colorMapping[0] = QString("rgb(23,186,62)");
    colorMapping[1] = QString("rgb(218,164,2)");
    colorMapping[2] = QString("rgb(254,170,202)");
    colorMapping[3] = QString("rgb(32,32,255)");
    colorMapping[4] = QString("rgb(160,244,255)");
    colorMapping[5] = QString("rgb(185, 64, 255)");
    colorMapping[6] = QString("rgb(255,244,160)");

    // create mappings from ints to QPixmap images
    imageMapping[0] = QPixmap(QString(":/resource/GreenPattern.png"));
    imageMapping[1] = QPixmap(QString(":/resource/OrangePattern.png"));
    imageMapping[2] = QPixmap(QString(":/resource/PinkPattern.png"));
    imageMapping[3] = QPixmap(QString(":/resource/BluePattern.png"));
    imageMapping[4] = QPixmap(QString(":/resource/LightBluePattern.png"));
    imageMapping[5] = QPixmap(QString(":/resource/PurplePattern.png"));
    imageMapping[6] = QPixmap(QString(":/resource/YellowPattern.png"));

    // define the locations of other images used in this level
    bacteriumImage = QImage(":/resource/Bacteria.png");
    defendCellImage = QImage(":/resource/Cell.png");
    c3ProteinImage = QImage(":/resource/ProteinSprite.png");

    // fill the queued patterns
    queuedPatterns.push_back(0);
    queuedPatterns.push_back(1);
    queuedPatterns.push_back(2);

    // add the central cell to the b2World
    b2BodyDef cellBodyDef;
    cellBodyDef.position.Set(340, 340);
    b2Body* cellBody = world.CreateBody(&cellBodyDef);
    b2CircleShape hitbox;
    hitbox.m_radius = 30.0f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &hitbox;
    fixtureDef.filter.groupIndex = 3;
    cellBody->CreateFixture(&fixtureDef);

    framesTillNextSpawn = 300;
    bacteriaWave = 0;

    // start listening for collisions in this same object
    world.SetContactListener(this);
}

/**
 * @brief PatterGameController::startLevel1 Starts up level 1
 */
void PatternGameController::startLevel1()
{
    connect(&timer, &QTimer::timeout, this, &PatternGameController::updateWorld);
    timer.start(17);
}

/**
 * @brief PatterGameController::checkPattern Checks the player's pattern against the correct one,
 * creating proteins if correct or flashing the buttons red if not.
 */
void PatternGameController::checkPattern()
{
    // Check to see if the entered pattern matches any of the correct patterns
    if(compareSets(&entered, &patternMapping[queuedPatterns[2]]))
    {
       emit flashSelectedButtons(colorMapping[queuedPatterns[2]]);
       createProteins(2);
       updateDisplayedPatterns();
    }
    else
    {
       emit flashSelectedButtons(QString("rgb(255,30,30)"));
    }

    // Clear the selected pattern
    entered.clear();
    emit clearButtons();
}

/**
 * @brief PatterGameController::compareSets Returns true if two sets are
 * completely identical, false otherwise.
 * @param set1 the first set to compare
 * @param set2 the second set to compare against the first
 */
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

/**
 * @brief PatterGameController::createBacteria Spawns the specified number of
 * bacteria into the level
 * @param count the number of bacteria to spawn
 */
void PatternGameController::createBacteria(int count)
{
    for (int i = 0; i < count; i++)
    {
        // create a b2Body for each bacterium being spawned, at a random
        // angle around the cell being defended.
        b2BodyDef bacteriaBodyDef;
        int angle = (arc4random_uniform(361u));
        bacteriaBodyDef.position.Set(340 + 330 * cos(angle), 340 + 330 * sin(angle));
        bacteriaBodyDef.type = b2_dynamicBody;
        b2Body* bacteriaBody = world.CreateBody(&bacteriaBodyDef);
        b2CircleShape hitbox;
        hitbox.m_radius = 20.0f;

        // define the bacterium's hitbox
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &hitbox;
        fixtureDef.filter.groupIndex = 1;
        bacteriaBody->CreateFixture(&fixtureDef);

        this->bacteria.push_back(bacteriaBody);
    }
}

/**
 * @brief PatterGameController::createProteins Spawns the specified number of
 * proteins into the level
 * @param count the number of proteins to spawn
 */
void PatternGameController::createProteins(int count)
{
    for (int i = 0; i < count; i++)
    {
        // create a b2Body for each protein being spawned, at a random
        // angle around the cell being defended.
        b2BodyDef proteinBodyDef;
        int angle = (arc4random_uniform(361u));
        proteinBodyDef.position.Set(340 + 35 * cos(angle), 340 + 35 * sin(angle));
        proteinBodyDef.type = b2_dynamicBody;
        b2Body* proteinBody = world.CreateBody(&proteinBodyDef);
        b2CircleShape hitbox;
        hitbox.m_radius = 5.0f;

        // Define the protein's hitbox
        b2FixtureDef fixtureDef;
        fixtureDef.filter.groupIndex = 2;
        fixtureDef.shape = &hitbox;
        proteinBody->CreateFixture(&fixtureDef);

        // add the protein to the list of all active proteins
        this->proteins.push_back(proteinBody);
    }
}

/**
 * @brief PatternGameController::updateWorld Updates the level world,
 * including moving bacteria and proteins, and removing any that collided.
 */
void PatternGameController::updateWorld()
{
    // Move all bacteria towards the cell (don't if it has been marked with proteins)
    for(b2Body* bacteriumBody : bacteria)
    {
        b2Vec2 center = b2Vec2(340, 340);
        b2Vec2 forceVec = b2Vec2(center.x - bacteriumBody->GetPosition().x, center.y - bacteriumBody->GetPosition().y);
        bacteriumBody->ApplyForceToCenter(forceVec, true);
    }

    // Remove every protein that should be removed, both from the world and from the array of them
    for(b2Body* proteinToRemove: proteinsToRemove)
    {
        vector<b2Body*>::iterator it = std::find(proteins.begin(), proteins.end(), proteinToRemove);
        if(it != proteins.end())
        {
            proteins.erase(it);
            world.DestroyBody(proteinToRemove);
        }
    }
    proteinsToRemove.clear();

    // Remove every bacterium that should be removed, both from the world and from the array of them
    for(b2Body* bacteriumToRemove: bacteriaToRemove)
    {
        vector<b2Body*>::iterator it = std::find(bacteria.begin(), bacteria.end(), bacteriumToRemove);
        if(it != bacteria.end())
        {
            bacteria.erase(it);
            world.DestroyBody(bacteriumToRemove);
        }
    }
    bacteriaToRemove.clear();

    // Every 3 seconds another wave of bacteria comes
    framesTillNextSpawn--;
    if (framesTillNextSpawn < 0)
    {
        framesTillNextSpawn = 300;
        bacteriaWave += arc4random_uniform(2u);
        createBacteria(bacteriaWave);
    }

    // Advance the world at a fixed time step and iterations
    world.Step(1.0/60.0, 6, 2);
    update(); // trigger repainting

    // consider the level complete once wave 3 has been passed
    if(bacteriaWave > 3)
    {
        emit level1Complete();
        timer.stop();
    }
}

/**
 * @brief PatternGameController::paintEvent Repaints the world.
 */
void PatternGameController::paintEvent(QPaintEvent *)
{
    // Create a painter
    QPainter painter(this);

    // Paint all currently active bacteria
    for(b2Body* bacteriumBody : bacteria)
    {
        // rotate bacterium image based on its trajectory towards the center:
        float bacX = bacteriumBody->GetPosition().x;
        float bacY = bacteriumBody->GetPosition().y;
        float angle = atan((bacY - 340.0f) / (bacX - 340.0f));
        if(bacX < 340.0f)
            angle = angle + M_PI;
        angle = angle - 3*M_PI_4; // adjustment due to image already being at a 45° angle
        float rotImgWidth = 40 * (cos(abs(fmod(angle,M_PI_2))) + sin(abs(fmod(angle,M_PI_2))));

        QImage rotatedImg = bacteriumImage.transformed(QTransform().rotateRadians(angle));
        painter.drawImage(QRect(bacteriumBody->GetPosition().x - 20, bacteriumBody->GetPosition().y - 20, rotImgWidth, rotImgWidth), rotatedImg);
    }

    // Paint all currently active proteins
    for(b2Body* proteinBody : proteins)
    {
        painter.drawImage(QRect(proteinBody->GetPosition().x - 5, proteinBody->GetPosition().y - 5, 10, 10), c3ProteinImage);
    }

    // Paint the cell being defended
    painter.drawImage(QRect(310, 310, 60, 60), defendCellImage);

    painter.end();
}

/**
 * @brief PatternGameController::BeginContact Callback triggered by the world whenever contact
 * between two bodies is detected. Checks if the two bodies are a protein and a bacteria,
 * "removing" both if so or doing nothing otherwise.
 */
void PatternGameController::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    if(bodyA->GetFixtureList()->GetShape()->m_radius == 5.0f && bodyB->GetFixtureList()->GetShape()->m_radius == 20.0f)
    {
        // in this case, bodyA is a protein and bodyB is a bacterium:
        proteinsToRemove.push_back(bodyA);
        bacteriaToRemove.push_back(bodyB);
    }
    else if(bodyA->GetFixtureList()->GetShape()->m_radius == 20.0f && bodyB->GetFixtureList()->GetShape()->m_radius == 5.0f)
    {
        // in this case, bodyA is a baterium and bodyB is a protein:
        bacteriaToRemove.push_back(bodyA);
        proteinsToRemove.push_back(bodyB);
    }
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

/**
 * @brief PatterGameController::updateEntered Updates the entered vector with a button
 * that has been pushed or unpushed.
 * @param button the index of the toggled button
 * @param selected whether this button was just selected or unselected
 */
void PatternGameController::updateEntered(int button, bool selected)
{
    if(selected)
        entered.insert(button);
    else
    {
        entered.erase(button);
    }
}

/**
 * @brief PatterGameController::buttonPushed1 updates button 1's "pushed" state
 * @param pushed true if button 1 is now pushed, false otherwise
 */
void PatternGameController::buttonPushed1(bool pushed)
{
    updateEntered(1, pushed);
}

/**
 * @brief PatterGameController::buttonPushed2 updates button 2's "pushed" state
 * @param pushed true if button 2 is now pushed, false otherwise
 */
void PatternGameController::buttonPushed2(bool pushed)
{
    updateEntered(2, pushed);
}

/**
 * @brief PatterGameController::buttonPushed3 updates button 3's "pushed" state
 * @param pushed true if button 3 is now pushed, false otherwise
 */
void PatternGameController::buttonPushed3(bool pushed)
{
    updateEntered(3, pushed);
}

/**
 * @brief PatterGameController::buttonPushed4 updates button 4's "pushed" state
 * @param pushed true if button 4 is now pushed, false otherwise
 */
void PatternGameController::buttonPushed4(bool pushed)
{
    updateEntered(4, pushed);
}

/**
 * @brief PatterGameController::buttonPushed5 updates button 5's "pushed" state
 * @param pushed true if button 5 is now pushed, false otherwise
 */
void PatternGameController::buttonPushed5(bool pushed)
{
    updateEntered(5, pushed);
}

/**
 * @brief PatterGameController::buttonPushed6 updates button 6's "pushed" state
 * @param pushed true if button 6 is now pushed, false otherwise
 */
void PatternGameController::buttonPushed6(bool pushed)
{
    updateEntered(6, pushed);
}

/**
 * @brief PatterGameController::buttonPushed7 updates button 7's "pushed" state
 * @param pushed true if button 7 is now pushed, false otherwise
 */
void PatternGameController::buttonPushed7(bool pushed)
{
    updateEntered(7, pushed);
}

/**
 * @brief PatterGameController::buttonPushed8 updates button 8's "pushed" state
 * @param pushed true if button 8 is now pushed, false otherwise
 */
void PatternGameController::buttonPushed8(bool pushed)
{
    updateEntered(8, pushed);
}

/**
 * @brief PatterGameController::buttonPushed9 updates button 9's "pushed" state
 * @param pushed true if button 9 is now pushed, false otherwise
 */
void PatternGameController::buttonPushed9(bool pushed)
{
    updateEntered(9, pushed);
}

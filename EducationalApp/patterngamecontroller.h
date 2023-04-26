#ifndef PATTERNGAMECONTROLLER_H
#define PATTERNGAMECONTROLLER_H

#include <set>
#include <QWidget>
#include <iostream>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <queue>
#include <map>

using std::set;
using std::cout;
using std::endl;
using std::vector;
using std::rand;
using std::queue;
using std::map;

class PatternGameController : public QWidget
{
    Q_OBJECT
public:
    explicit PatternGameController(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

signals:
    void clearButtons();
    void flashSelectedButtons(QString);
    void updateImages(QPixmap, QPixmap, QPixmap);
    void level1Complete();

public slots:
    void updateWorld();
    void buttonPushed1(bool);
    void buttonPushed2(bool);
    void buttonPushed3(bool);
    void buttonPushed4(bool);
    void buttonPushed5(bool);
    void buttonPushed6(bool);
    void buttonPushed7(bool);
    void buttonPushed8(bool);
    void buttonPushed9(bool);

    void checkPattern(bool);
    void updateEntered(int, bool);

    void startLevel1();


private:
    vector<b2Body*> bacterium;
    vector<b2Body*> proteins;
    b2World world;
    set<int> entered;
    set<int> greenPattern;
    set<int> pinkPattern;
    set<int> orangePattern;
    set<int> bluePattern;
    set<int> lightBluePattern;
    set<int> purplePattern;
    set<int> yellowPattern;

    vector<int> queuedPatterns;

    QImage bacteriaImage;
    QImage defendCellImage;
    QImage c3ProteinImage;

    map<int, set<int>> patternMapping;
    map<int, QString> colorMapping;
    map<int, QPixmap> imageMapping;

    QTimer timer;
    int framesTillNextSpawn;
    int bacteriaWave;
    int score;
    void createProteins(int count);
    void createBacteria(int count);
    bool compareSets(set<int>* , set<int>*);
    void updateDisplayedPatterns();
};

#endif // PATTERNGAMECONTROLLER_H

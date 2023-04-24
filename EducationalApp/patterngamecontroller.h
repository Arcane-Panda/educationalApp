#ifndef PATTERNGAMECONTROLLER_H
#define PATTERNGAMECONTROLLER_H

#include <set>
#include <QWidget>
#include <iostream>

using std::set;
using std::cout;
using std::endl;

class PatternGameController : public QWidget
{
    Q_OBJECT
public:
    explicit PatternGameController(QWidget *parent = nullptr);

signals:
    void clearButtons();
    void flashSelectedButtons(QString);


public slots:
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


private:
    set<int> entered;
    set<int> greenPattern;
    set<int> pinkPattern;
    set<int> orangePattern;
    bool compareSets(set<int>* , set<int>*);
};

#endif // PATTERNGAMECONTROLLER_H

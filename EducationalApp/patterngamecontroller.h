#ifndef PATTERNGAMECONTROLLER_H
#define PATTERNGAMECONTROLLER_H

#include <set>
#include <QWidget>

using std::set;

class PatternGameController : public QWidget
{
    Q_OBJECT
public:
    explicit PatternGameController(QWidget *parent = nullptr);


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


private:
    set<int> entered;
    set<int> greenPattern = {1, 2, 5, 6, 7, 8};
    set<int> pinkPattern = {3, 4, 5, 6, 7, 9};
    set<int> orangePattern = {4, 5, 8, 9};
    bool compareSets(set<int>* , set<int>*);
};

#endif // PATTERNGAMECONTROLLER_H

#include "patterngamecontroller.h"

PatternGameController::PatternGameController(QWidget *parent) : QWidget(parent)
{

}




void PatternGameController::checkPattern(bool pushed)
{
    if(compareSets(&entered, &greenPattern))
    {

    }
    else if(compareSets(&entered, &pinkPattern))
    {

    }
    else if (compareSets(&entered, &orangePattern))
    {

    }
    else
    {

    }
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








void PatternGameController::buttonPushed1(bool pushed)
{
    entered.insert(1);
}

void PatternGameController::buttonPushed2(bool pushed)
{
    entered.insert(2);
}

void PatternGameController::buttonPushed3(bool pushed)
{
    entered.insert(3);
}

void PatternGameController::buttonPushed4(bool pushed)
{
    entered.insert(4);
}

void PatternGameController::buttonPushed5(bool pushed)
{
    entered.insert(5);
}

void PatternGameController::buttonPushed6(bool pushed)
{
    entered.insert(6);
}

void PatternGameController::buttonPushed7(bool pushed)
{
    entered.insert(7);
}

void PatternGameController::buttonPushed8(bool pushed)
{
    entered.insert(8);
}

void PatternGameController::buttonPushed9(bool pushed)
{
    entered.insert(9);
}


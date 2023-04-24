#include "patterngamecontroller.h"

PatternGameController::PatternGameController(QWidget *parent) : QWidget(parent)
{
    greenPattern = {1, 2, 5, 6, 7, 8};
    pinkPattern = {3, 4, 5, 6, 7, 9};
    orangePattern = {4, 5, 8, 9};
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
        cout << "Matches green!" << endl;
    }
    else if(compareSets(&entered, &pinkPattern))
    {
        cout << "Matches pink!" << endl;
    }
    else if (compareSets(&entered, &orangePattern))
    {
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




#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QWidget>

class GameController : public QWidget
{
    Q_OBJECT

public:
    GameController();

signals:
    void setCurrentLevel(int index);
    void updateDialog(QString newText);
    void showCatDog(bool show);
public slots:

};

#endif // GAMECONTROLLER_H

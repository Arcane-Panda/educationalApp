#ifndef PHAGOCYTEWIDGET_H
#define PHAGOCYTEWIDGET_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>

class PhagocyteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhagocyteWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:

public slots:
    void updateWorld();

private:
    b2World world;
    b2Body* body;
    QTimer timer;
    QImage image;
};

#endif // PHAGOCYTEWIDGET_H

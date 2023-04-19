/***
 * Alex Tokita, Andrew Hokanson, Austin Li, Jonah Thomas, and Lucas Zagal
 * CS3505 - A8 Educational App
 * 18 April 2023
 *
 * This class holds the methods
 *
 * Code Style Review by:
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    return a.exec();
}

#ifndef SCREENS_H
#define SCREENS_H

#include <QWidget>

class Screens
{

public:
    static bool allowScreenShows;
    static void show(QWidget* screen);
};

#endif // SCREENS_H

#include <iostream>

#include <QtGui/QApplication>
#include <qfile.h>
#include <QTextStream>
#include <QtDebug>

#include "startupwindow.h"
#include "videotest.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    QFile styleFile("style.css");
    QTextStream styleStream(&styleFile);
    QString styleString = styleStream.readAll();

    qDebug() << styleString;
    */

/*    a.setStyleSheet("\
                    QWidget{font-family: Tamworth Gothic};"
            );*/

    StartupWindow w;
    w.show();

    return a.exec();
}

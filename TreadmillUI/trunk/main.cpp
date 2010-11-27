#include <iostream>

#include <QtGui/QApplication>
#include <qfile.h>
#include <QTextStream>
#include <QtDebug>
#include <QDir>
#include <Phonon>

#include "startupwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    StartupWindow w;
    w.show();

    return a.exec();
}

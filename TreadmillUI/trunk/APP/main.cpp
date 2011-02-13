#include <iostream>

#include <QtGui/QApplication>
#include <qfile.h>
#include <QTextStream>
#include <QtDebug>
#include <QDir>

//#include "qextserialport.h"
#include "startupwindow.h"
#include "preferences.h"

using namespace std;

void loadPreferences(){
    QFile file(Preferences::FILENAME);
    if(file.exists()){
        file.open(QFile::ReadOnly);

        QDataStream stream(&file);

        stream >> Preferences::measurementSystem;

        file.close();
    }
}

void savePreferences(){
    QFile file(Preferences::FILENAME);
    file.open(QFile::WriteOnly);
    QDataStream stream(&file);

    stream << Preferences::measurementSystem;

    file.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir::setCurrent(QCoreApplication::applicationDirPath());
//    a.setStyleSheet(" QWidget:hover { background-color: orange } ");

    /*QDeclarativeView view;
        view.setSource(QUrl("/redmouse.qml"));
        view.setResizeMode(QDeclarativeView::SizeRootObjectToView);

    #if defined(Q_WS_S60) || defined(Q_WS_MAEMO)
        view.showMaximized();
    #else
        view.setGeometry(100,100, 800, 480);
        view.show();
    #endif*/

    loadPreferences();

//    Preferences::initializeSerialPort();

    StartupWindow* w = new StartupWindow();
    w->showFullScreen();

    a.exec();

    savePreferences();

    return 0;
}

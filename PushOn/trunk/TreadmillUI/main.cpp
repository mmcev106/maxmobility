#include <iostream>

#include <QtGui/QApplication>
#include <qfile.h>
#include <QTextStream>
#include <QtDebug>
#include <QDir>
#include <QCoreApplication>

#include "startupwindow.h"
#include "preferences.h"
#include "screens.h"
#include "state.h"
#include "utils.h"
#include "settingsscreen.h"
#include "calibrationscreen.h"
#include "serialreconnectthread.h"

using namespace std;

void loadPreferences(){
    bool tempMeasurementSystem;
    QFile file(Preferences::FILENAME);
    if(file.exists()){
        file.open(QFile::ReadOnly);

        QDataStream stream(&file);
        //read the file
        stream >> tempMeasurementSystem;

        file.close();
        Preferences::setMeasurementSystem(tempMeasurementSystem);
    }

    Preferences::setMeasurementSystem(STANDARD);
    if (Preferences::measurementSystem == STANDARD)
    {
        Preferences::WALKING_SPEED=2.0;
        Preferences::FAST_SPEED=3.0;
        Preferences::JOGGING_SPEED=6.0;
        Preferences::RUNNING_SPEED=8.0;
    }
    else
    {
        Preferences::WALKING_SPEED=3.0;
        Preferences::FAST_SPEED=6.0;
        Preferences::JOGGING_SPEED=10.0;
        Preferences::RUNNING_SPEED=14.0;
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
    a.setApplicationName("PushOn");
    Preferences::application=&a;

    QString workingDir = QCoreApplication::applicationDirPath();
    QDir::setCurrent(workingDir);
    qDebug() << "Working Directory: " << workingDir;

    loadPreferences();

    Preferences::startupWindow = new StartupWindow();
    MainScreen::createMainScreen(Preferences::startupWindow);
    SettingsScreen::createSettingsScreen(Preferences::startupWindow);
    CalibrationScreen::createCalibrationScreen(Preferences::startupWindow);

    if(!Preferences::isTestingMode()){
        SerialReconnectThread* serialReconnectThread = new SerialReconnectThread();
        serialReconnectThread->start();
    }

    if(Preferences::isTestingMode()){
        //Mark M uses this for simulating serial events

       /* QTimer* testTimer = new QTimer(startupWindow);
        testTimer->setInterval(1000);
        testTimer->connect(testTimer,SIGNAL(timeout()),startupWindow,SLOT(mockSerialEvent()));
        testTimer->start();*/
    }

    Screens::show(Preferences::startupWindow);
    a.exec();

    savePreferences();

    return 0;
}

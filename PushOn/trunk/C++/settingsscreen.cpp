#include "settingsscreen.h"
#include "ui_settingsscreen.h"
#include "QProcess"
#include "preferences.h"

SettingsScreen* SettingsScreen::settingsScreen = NULL;

static const int UPDATE_DISPLAY_DELAY = 100;

int SettingsScreen::on_time=0;
int SettingsScreen::belt_time=0;

SettingsScreen::SettingsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsScreen)
    ,secondTimer(new QTimer(this))
{

    connect(secondTimer, SIGNAL(timeout()), this, SLOT( updateDisplay()));
    secondTimer->setSingleShot(false);
    secondTimer->setInterval(UPDATE_DISPLAY_DELAY);
    secondTimer->start();

    ui->setupUi(this);
}

SettingsScreen::~SettingsScreen()
{
    delete ui;
}

void SettingsScreen::createSettingsScreen(QWidget *parent){
    settingsScreen = new SettingsScreen(parent);
    settingsScreen->hide();
}

SettingsScreen* SettingsScreen::getSettingsScreen(){
    return settingsScreen;
}

void SettingsScreen::on_connect_invisibleButton_pressed()
{
    // this is how you're going to start the network stuff
    QProcess *process = new QProcess(this);
    QString program = "explorer.exe";
    QString args = QString("shell:::{1fa9085f-25a2-489b-85d4-86326eedcd87}");
    process->start(program, QStringList() << args);
}

void SettingsScreen::updateDisplay(){

    on_time = (Preferences::on_time)/24;
    ui->onTimeLabel->setText(QString("%1").arg(on_time,1,'g',-1,QLatin1Char('0')));

    belt_time = (Preferences::belt_time)/24;
    ui->beltTimeLabel->setText(QString("%1").arg(belt_time,1,'g',-1,QLatin1Char('0')));

    if (Preferences::getMeasurementSystem())
        ui->unitsLabel->setText(QString("Standard"));
    else
        ui->unitsLabel->setText(QString("Metric"));
}


void SettingsScreen::on_pushButton_pressed()
{
    Preferences::application->exit();
}

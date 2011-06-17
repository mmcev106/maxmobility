#include "settingsscreen.h"
#include "ui_settingsscreen.h"

SettingsScreen* SettingsScreen::settingsScreen = NULL;

SettingsScreen::SettingsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsScreen)
{
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

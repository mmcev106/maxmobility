#include "myworkoutsscreen.h"
#include "ui_myworkoutsscreen.h"
#include "newworkoutscreen.h"
#include "preferences.h"
#include "invisiblebutton.h"

#include <QDir>
#include <QDebug>
#include <QVBoxLayout>
#include <QBitmap>

MyWorkoutsScreen::MyWorkoutsScreen(QWidget *parent) :
    AbstractScreen(parent),
    ui(new Ui::MyWorkoutsScreen)
    ,workoutListItemBackground(":/My Workouts/images/My Workouts Title Bar.png")
{
    ui->setupUi(this);

    QDir workoutsDir(WORKOUTS);


    QStringList children = workoutsDir.entryList(QDir::Files, QDir::Name);

    QVBoxLayout *layout = new QVBoxLayout;

    for(int i=0;i<children.length();i++){
        QString workout = children.at(i);
        qDebug() << workout << endl;
        InvisibleButton* button = new InvisibleButton;
        button->highlightOnPress = false;
        button->setText(workout);
        button->setBackgroundPixmap(&workoutListItemBackground);

        layout->addWidget(button, Qt::AlignVCenter);
    }

    ui->scrollAreaWidgetContents->setLayout(layout);
    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
}

MyWorkoutsScreen::~MyWorkoutsScreen()
{
    delete ui;
}

void MyWorkoutsScreen::on_invisibleButton_6_pressed()
{
    (new NewWorkoutScreen())->show();
    close();
}

void MyWorkoutsScreen::on_invisibleButton_upArrowButton_pressed()
{
    ui->scrollAreaWidgetContents->scroll(0, workoutListItemBackground.height());
}

void MyWorkoutsScreen::on_invisibleButton_downArrowButton_pressed()
{
    ui->scrollAreaWidgetContents->scroll(0, -workoutListItemBackground.height());
}

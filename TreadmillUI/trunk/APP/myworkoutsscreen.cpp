#include "myworkoutsscreen.h"
#include "ui_myworkoutsscreen.h"
#include "newworkoutscreen.h"
#include "preferences.h"
#include "invisiblebutton.h"
#include "mainscreen.h"
#include "screens.h"

#include <QDir>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBitmap>
#include <QScrollBar>
#include <QMessageBox>

MyWorkoutsScreen::MyWorkoutsScreen(QWidget *parent) :
    AbstractScreen(parent),
    ui(new Ui::MyWorkoutsScreen)
    ,workoutListItemBackground(":/My Workouts/images/My Workouts Title Bar.png")
    ,xPixmap(":/My Workouts/images/My Workouts - 'x'.png")
{
    ui->setupUi(this);

    QDir workoutsDir(Preferences::getCurrentWorkoutsPath());

    QStringList children = workoutsDir.entryList(QDir::Files, QDir::Name);


    rowHeight = workoutListItemBackground.height() + 10;

    QWidget * scrollAreaContents = new QWidget(ui->scrollArea);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    scrollAreaContents->setLayout(layout);
    ui->scrollArea->setWidget(scrollAreaContents);
    ui->scrollArea->setWidgetResizable(true);

    for(int i=0;i<children.length();i++){
        QString workout = children.at(i);

        QWidget* listItem = new QWidget(scrollAreaContents);
        QHBoxLayout* listItemLayout = new QHBoxLayout;
        listItemLayout->setMargin(0);
        listItem->setLayout(listItemLayout);
        layout->addWidget(listItem);

        InvisibleButton* deleteLabel = new InvisibleButton(listItem);
        deleteLabel->setAccessibleName(workout);
        deleteLabel->setBackgroundPixmap(&xPixmap);
        deleteLabel->setFixedHeight(deleteLabel->height()+10);
        listItemLayout->addWidget(deleteLabel, Qt::AlignVCenter);
        connect( deleteLabel, SIGNAL(pressed()), this, SLOT(deleteWorkout()) );

        QWidget* spacer = new QWidget(listItem);
        spacer->setFixedSize(25, 1);
        listItemLayout->addWidget(spacer);

        QWidget* workoutButton = new QWidget(listItem);
        workoutButton->setFixedSize(workoutListItemBackground.size());
        listItemLayout->addWidget(workoutButton, Qt::AlignVCenter);

        QLabel* background = new QLabel(workoutButton);
        background->setPixmap(workoutListItemBackground);
        background->setFixedSize(workoutListItemBackground.size());

        InvisibleButton* button = new InvisibleButton(workoutButton);
        button->setAccessibleName(workout);
        button->highlightOnPress = false;
        button->setText(workout);
        button->setStyleSheet("font-size: 20px");
        button->setFixedSize(workoutListItemBackground.size());
        connect( button, SIGNAL(pressed()), this, SLOT(workoutSelected()) );
    }

    scrollAreaContents->setFixedHeight((rowHeight-2) * children.length());

    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    setUpArrowVisibility(false);

    if(scrollAreaContents->height() <= ui->scrollArea->height()){
        setDownArrowVisibility(false);
    }
}

MyWorkoutsScreen::~MyWorkoutsScreen()
{
    delete ui;
}

void MyWorkoutsScreen::workoutSelected(){
    InvisibleButton* button = (InvisibleButton*)sender();
    QString workoutName = button->accessibleName();

    Workout* workout = Workout::load(workoutName);

    MainScreen::getMainScreen()->startWorkout(workout);
    close();
}

void MyWorkoutsScreen::deleteWorkout(){
    InvisibleButton* button = (InvisibleButton*)sender();
    QString workoutName = button->accessibleName();

    QFile file(Preferences::getCurrentWorkoutsPath() + "/" + workoutName);
    file.remove();

    QWidget* listItem = button->parentWidget();
    listItem->setParent(NULL);

    QWidget* scrollAreaContents = ui->scrollArea->widget();

    scrollAreaContents->layout()->removeWidget(listItem);
    scrollAreaContents->setFixedHeight(scrollAreaContents->height() - rowHeight);
    updateArrowVisibility();
}

void MyWorkoutsScreen::on_invisibleButton_6_pressed()
{
    Screens::show(new NewWorkoutScreen());
    close();
}

void MyWorkoutsScreen::on_invisibleButton_upArrowButton_pressed()
{
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->value() - rowHeight);
    updateArrowVisibility();
}

void MyWorkoutsScreen::on_invisibleButton_downArrowButton_pressed()
{
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->value() + rowHeight);
    updateArrowVisibility();
}

void MyWorkoutsScreen::updateArrowVisibility(){
    QScrollBar *scrollBar = ui->scrollArea->verticalScrollBar();

    setUpArrowVisibility(scrollBar->value() != scrollBar->minimum());
    setDownArrowVisibility( scrollBar->value() != scrollBar->maximum() );
}

void MyWorkoutsScreen::setUpArrowVisibility(bool visible){
    ui->upArrowLabel->setVisible(visible);
    ui->invisibleButton_upArrowButton->setVisible(visible);
}

void MyWorkoutsScreen::setDownArrowVisibility(bool visible){
    ui->downArrowLabel->setVisible(visible);
    ui->invisibleButton_downArrowButton->setVisible(visible);
}

void MyWorkoutsScreen::on_invisibleButton_7_pressed()
{
    close();
}

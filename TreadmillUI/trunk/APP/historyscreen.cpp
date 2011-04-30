#include "historyscreen.h"
#include "ui_historyscreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>`
#include <QFile>
#include <QDebug>
#include "screens.h"
#include "preferences.h"
#include <QTextStream>
#include <QScrollBar>

 QString HistoryScreen::DATE_FORMAT = "M-d-yyyy";

HistoryScreen::HistoryScreen(QWidget *parent) :
    AbstractScreen(parent),
    ui(new Ui::HistoryScreen)
    ,history(loadHistory())
    ,rowHeight(55)
{
    ui->setupUi(this);

    QWidget * scollAreaContents = new QWidget(ui->scrollArea);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    scollAreaContents->setLayout(layout);
    ui->scrollArea->setWidget(scollAreaContents);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // qSort(history.begin(), history.end(), foo);

    int totalSeconds = 0;
    int totalCalories = 0;
    float totalDistance = 0;

    for(int i=0; i<history->length(); i++){

        HistoryItem* item = history->at(i);

        QWidget* listItem = new QWidget(scollAreaContents);
        listItem->setFixedHeight(rowHeight-10);
        QHBoxLayout* listItemLayout = new QHBoxLayout;
        listItemLayout->setMargin(0);
        listItem->setLayout(listItemLayout);
        layout->addWidget(listItem, Qt::AlignTop);

        QLabel* dateLabel = new QLabel(listItem);
        dateLabel->setText(item->date.toString("M-d-yyyy"));
        listItemLayout->addWidget(dateLabel);

        listItemLayout->addSpacerItem(new QSpacerItem(40, 1));;

        QLabel* nameLabel = new QLabel(listItem);
        nameLabel->setText(item->name);
        nameLabel->setFixedWidth(265);
        nameLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        listItemLayout->addWidget(nameLabel);

        listItemLayout->addSpacerItem(new QSpacerItem(35, 1));;

        short seconds = item->seconds%60;
        short minutes = item->seconds/60;
        QString timeString = QString("%1:%2").arg(minutes).arg(seconds);

        QLabel* timeLabel = new QLabel(listItem);
        timeLabel->setText(timeString);
        timeLabel->setMargin(5);
        timeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        timeLabel->setFixedWidth(120);
        listItemLayout->addWidget(timeLabel);

        QString caloriesString = QString("%1").arg(item->calories);

        QLabel* caloriesLabel = new QLabel(listItem);
        caloriesLabel->setText(caloriesString);
        caloriesLabel->setMargin(5);
        caloriesLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        caloriesLabel->setFixedWidth(125);
        listItemLayout->addWidget(caloriesLabel);

        int distanceInteger = (int) item->distance;
        int distanceDecimal = item->distance - distanceInteger;
        QString distanceString = QString("%1.%2").arg(distanceInteger).arg(distanceDecimal);

        QLabel* distanceLabel = new QLabel(listItem);
        distanceLabel->setText(distanceString);
        distanceLabel->setMargin(5);
        distanceLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        listItemLayout->addWidget(distanceLabel);

        totalSeconds += item->seconds;
        totalCalories += item->calories;
        totalDistance += item->distance;
    }

    int averageSeconds = 0;
    int averageCalories = 0;
    float averageDistance = 0;

    if(history->length() > 0){
        averageSeconds = totalSeconds/history->length();
        averageCalories = totalCalories/history->length();
        averageDistance = totalDistance/history->length();
        averageDistance = ((float)(int)(averageDistance*10))/10;
    }


    qDebug() << "averageSeconds%60: " << averageSeconds%60;

    ui->workoutsLabel->setText(QString("%1").arg(history->length()));
    ui->averageTimeLabel->setText(QString("%1:%2").arg(averageSeconds/60).arg(averageSeconds%60));
    ui->averageCaloriesLabel->setText(QString("%1").arg(averageCalories));

    ui->averageDistanceLabel->setText(QString("%1").arg(averageDistance));

    scollAreaContents->setFixedHeight(rowHeight * history->length());

    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    setUpArrowVisibility(false);

    if(scollAreaContents->height() <= ui->scrollArea->height()){
        setDownArrowVisibility(false);
    }
}

void HistoryScreen::on_invisibleButton_upArrowButton_pressed()
{
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->value() - rowHeight);
    updateArrowVisibility();
}

void HistoryScreen::on_invisibleButton_downArrowButton_pressed()
{
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->value() + rowHeight);
    updateArrowVisibility();
}

void HistoryScreen::updateArrowVisibility(){
    QScrollBar *scrollBar = ui->scrollArea->verticalScrollBar();

    setUpArrowVisibility(scrollBar->value() != scrollBar->minimum());
    setDownArrowVisibility( scrollBar->value() != scrollBar->maximum() );
}

QList<HistoryItem*>* HistoryScreen::loadHistory(){

    QList<HistoryItem*>* history = new QList<HistoryItem*>;

    QFile historyFile(HISTORY);
    historyFile.open(QFile::ReadOnly);

    QTextStream stream( &historyFile );
    QString line;

    while(( line = stream.readLine() ) != NULL){

        QStringList args = line.split('\t');

        if(args.length() < 5){
            qCritical() << "An error occurred parsing the history line: " << line;
            continue;
        }

        HistoryItem* item = new HistoryItem();

        item->date = QDate::fromString(args.at(0), DATE_FORMAT);
        item->name = args.at(1);
        item->seconds = QLocale(QLocale::C).toInt(args.at(2));
        item->calories = QLocale(QLocale::C).toInt(args.at(3));
        item->distance = QLocale(QLocale::C).toFloat(args.at(4));

        history->append(item);
    }

    historyFile.close();

    return history;
}

void HistoryScreen::on_invisibleButton_6_pressed()
{
    close();
}


void HistoryScreen::setUpArrowVisibility(bool visible){
    ui->upArrowLabel->setVisible(visible);
    ui->invisibleButton_upArrowButton->setVisible(visible);
}

void HistoryScreen::setDownArrowVisibility(bool visible){
    ui->downArrowLabel->setVisible(visible);
    ui->invisibleButton_downArrowButton->setVisible(visible);
}


HistoryScreen::~HistoryScreen()
{
    delete ui;

    for(int i=0;i<history->length();i++){
        delete history->at(i);
    }

    delete history;
}

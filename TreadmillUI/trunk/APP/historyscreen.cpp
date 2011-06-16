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

 bool sortByDateDescending(HistoryItem* item1, HistoryItem* item2){
      return item1->date >= item2->date;
 }

 bool sortByDateAcending(HistoryItem* item1, HistoryItem* item2){
      return item1->date < item2->date;
 }

 bool sortByNameDescending(HistoryItem* item1, HistoryItem* item2){
      return item1->name.toLower() >= item2->name.toLower();
 }

 bool sortByNameAcending(HistoryItem* item1, HistoryItem* item2){
      return item1->name.toLower() < item2->name.toLower();
 }

 bool sortByTimeDescending(HistoryItem* item1, HistoryItem* item2){
      return item1->calories >= item2->calories;
 }

 bool sortByTimeAcending(HistoryItem* item1, HistoryItem* item2){
      return item1->seconds < item2->seconds;
 }

 bool sortByCaloriesDescending(HistoryItem* item1, HistoryItem* item2){
      return item1->calories >= item2->calories;
 }

 bool sortByCaloriesAcending(HistoryItem* item1, HistoryItem* item2){
      return item1->calories < item2->calories;
 }

 bool sortByDistanceDescending(HistoryItem* item1, HistoryItem* item2){
      return item1->distance >= item2->distance;
 }

 bool sortByDistanceAcending(HistoryItem* item1, HistoryItem* item2){
      return item1->distance < item2->distance;
 }

HistoryScreen::HistoryScreen(QWidget *parent) :
    AbstractScreen(parent),
    ui(new Ui::HistoryScreen)
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


    history = loadHistory();

    displayHistory(sortByDateDescending);

    scollAreaContents->setFixedHeight(rowHeight * history->length());

    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    setUpArrowVisibility(false);

    if(scollAreaContents->height() <= ui->scrollArea->height()){
        setDownArrowVisibility(false);
    }
}

void HistoryScreen::displayHistory(bool (*sortFunction)(HistoryItem*, HistoryItem*)){
    lastSortFunction = sortFunction;

    QVBoxLayout* layout = (QVBoxLayout*) ui->scrollArea->widget()->layout();

    QLayoutItem * widget;
    while( (widget = layout->takeAt(0)) != NULL){
        widget->widget()->setParent(NULL);
        delete widget;
    }

    qSort(history->begin(), history->end(), sortFunction);

    for(int i=0; i<history->length(); i++){

        HistoryItem* item = history->at(i);

        QWidget* listItem = new QWidget(ui->scrollArea->widget());
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
        QString secondsString;
        if (seconds<10)
            secondsString="0";
        secondsString.append(QString("%1").arg(seconds));
        QString timeString = QString("%1:%2").arg(minutes).arg(secondsString);

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
        int distanceDecimal = (item->distance*100) - (distanceInteger*100);
        qDebug() << "distance should be: " << distanceInteger << "." << distanceDecimal << " from: "<< item->distance;
        QString distanceDecimalString;
        if (distanceDecimal < 10)
            distanceDecimalString = "0";
        distanceDecimalString.append(QString("%1").arg(distanceDecimal));
        QString distanceString = QString("%1.%2").arg(distanceInteger).arg(distanceDecimalString);

        QLabel* distanceLabel = new QLabel(listItem);
        distanceLabel->setText(distanceString);
        distanceLabel->setMargin(5);
        distanceLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        listItemLayout->addWidget(distanceLabel);
    }
}

void HistoryScreen::on_invisibleButton_date_pressed(){

    resetHeaderImages();

    if(lastSortFunction == sortByDateDescending){
        displayHistory(sortByDateAcending);
        ui->dateHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Date Title (ascending).png")));
    }
    else{
        displayHistory(sortByDateDescending);
        ui->dateHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Date Title (descending).png")));
    }
}

void HistoryScreen::on_invisibleButton_workout_pressed(){

    resetHeaderImages();

    if(lastSortFunction == sortByNameAcending){
        displayHistory(sortByNameDescending);
        ui->workoutHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Workout Title (descending).png")));
    }
    else{
        displayHistory(sortByNameAcending);
        ui->workoutHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Workout Title (ascending).png")));
    }
}

void HistoryScreen::on_invisibleButton_time_pressed(){

    resetHeaderImages();

    if(lastSortFunction == sortByTimeDescending){
        displayHistory(sortByTimeAcending);
        ui->timeHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Time Title (ascending).png")));
    }
    else{
        displayHistory(sortByTimeDescending);
        ui->timeHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Time Title (descending).png")));
    }
}

void HistoryScreen::on_invisibleButton_calories_pressed(){

    resetHeaderImages();

    if(lastSortFunction == sortByCaloriesDescending){
        displayHistory(sortByCaloriesAcending);
        ui->caloriesHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Calories Title (ascending).png")));
    }
    else{
        displayHistory(sortByCaloriesDescending);
        ui->caloriesHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Calories Title (descending).png")));
    }
}

void HistoryScreen::on_invisibleButton_distance_pressed(){

    resetHeaderImages();

    if(lastSortFunction == sortByDistanceDescending){
        displayHistory(sortByDistanceAcending);
        ui->distanceHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Distance Title (ascending).png")));
    }
    else{
        displayHistory(sortByDistanceDescending);
        ui->distanceHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Distance Title (descending).png")));
    }
}

void HistoryScreen::resetHeaderImages(){
    ui->dateHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Date Title (default).png")));
    ui->workoutHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Workout Title (default).png")));
    ui->timeHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Time Title (default).png")));
    ui->caloriesHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Calories Title (default).png")));
    ui->distanceHeader->setPixmap(QPixmap(QString::fromUtf8(":/images/images/Distance Title (default).png")));
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


    int totalSeconds = 0;
    int totalCalories = 0;
    double totalDistance = 0;

    QFile historyFile(Preferences::getCurrentHistoryPath());
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
        item->distance = QLocale(QLocale::C).toDouble(args.at(4));

        history->append(item);

        totalSeconds += item->seconds;
        totalCalories += item->calories;
        totalDistance += item->distance;
    }

    historyFile.close();

    int averageSeconds = 0;
    int averageCalories = 0;
    double averageDistance = 0;
    QString averageSecondsString;
    QString averageDistanceDecimalString;

    if(history->length() > 0){
        averageSeconds = totalSeconds/history->length();
        averageCalories = totalCalories/history->length();
        averageDistance = totalDistance/history->length();
        int averageDistanceDecimal = (averageDistance-(int)averageDistance)*100;
        qDebug()<< "Average Distance: " << averageDistance << " length: " << history->length()<<" decimal: "<<averageDistanceDecimal;
        if ((averageSeconds%60) <10)
            averageSecondsString="0";
        averageSecondsString.append(QString("%1").arg(averageSeconds%60));
        if (averageDistanceDecimal < 10)
            averageDistanceDecimalString = "0";
        averageDistanceDecimalString.append(QString("%1").arg(averageDistanceDecimal));
    }

    ui->workoutsLabel->setText(QString("%1").arg(history->length()));
    ui->averageTimeLabel->setText(QString("%1:%2").arg(averageSeconds/60).arg(averageSecondsString));
    ui->averageCaloriesLabel->setText(QString("%1").arg(averageCalories));
    ui->averageDistanceLabel->setText(QString("%1.%2").arg((int)averageDistance).arg(averageDistanceDecimalString));

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

#include "historyscreen.h"
#include "ui_historyscreen.h"
#include <QVBoxLayout>
#include <QHBoxLayout>`
#include <QFile>
#include <QDebug>
#include "screens.h"
#include "preferences.h"
#include <QTextStream>

HistoryScreen::HistoryScreen(QWidget *parent) :
    AbstractScreen(parent),
    ui(new Ui::HistoryScreen)
    ,history(loadHistory())
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

    for(int i=0; i<history->length(); i++){

        HistoryItem* item = history->at(i);

        QWidget* listItem = new QWidget(scollAreaContents);
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

        /*QString timeString = args.at(2);

        QLabel* timeLabel = new QLabel(listItem);
        timeLabel->setText(timeString);
        timeLabel->setMargin(5);
        timeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        timeLabel->setFixedWidth(120);
        listItemLayout->addWidget(timeLabel);

        QString caloriesString = args.at(3);

        QLabel* caloriesLabel = new QLabel(listItem);
        caloriesLabel->setText(caloriesString);
        caloriesLabel->setMargin(5);
        caloriesLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        caloriesLabel->setFixedWidth(125);
        listItemLayout->addWidget(caloriesLabel);

        QString distanceString = args.at(4);

        QLabel* distanceLabel = new QLabel(listItem);
        distanceLabel->setText(distanceString);
        distanceLabel->setMargin(5);
        distanceLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        listItemLayout->addWidget(distanceLabel);*/
    }

    scollAreaContents->adjustSize();

    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    setUpArrowVisibility(false);

    if(scollAreaContents->height() <= ui->scrollArea->height()){
        setDownArrowVisibility(false);
    }
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

        //date args.at(0)

        HistoryItem* item = new HistoryItem();
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

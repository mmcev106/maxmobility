#include "outdoorpathsscreen.h"
#include "ui_outdoorpathsscreen.h"
#include "pointerevent.h"
#include "screens.h"
#include "mainscreen.h"
#include "workout.h"
#include "utils.h"

static const int HISTORY_WIDTH = 12;
static const int HISTORY_HEIGHT = 10;

static const QString TRAILS_PATH = "/videos/trails";

OutdoorPathsScreen::OutdoorPathsScreen(QWidget *parent) :
    AbstractScreen(parent)
    ,ui(new Ui::OutdoorPathsScreen)
    ,timeSliderWidget(this)
    ,intensitySliderWidget(this)
    ,weightSliderWidget(this)
    ,history(new int[HISTORY_WIDTH])
    ,historyWidget(this, history, HISTORY_WIDTH, HISTORY_HEIGHT, BIG_BRICK_URL, HIGHLIGHTED_BIG_BRICK_URL)
{
    ui->setupUi(this);

    int x = 10;
    int y = 422;
    int dy = 119;
    timeSliderWidget.move(x, y);
    y += dy;
    intensitySliderWidget.move(x, y);
    y += dy;
    weightSliderWidget.move(x, y);

    updateHistoryFromIntensity();
    historyWidget.move(747, 448);

    ui->backgroundLabel->lower();

    on_woodedButton_pressed();
}

OutdoorPathsScreen::~OutdoorPathsScreen()
{
    delete ui;
    delete history;
}

void OutdoorPathsScreen::on_woodedButton_pressed(){
    hideAllBorders();
    ui->woodedBorder->show();
}

void OutdoorPathsScreen::on_deerButton_pressed(){
    hideAllBorders();
    ui->deerBorder->show();
}

void OutdoorPathsScreen::on_lakeButton_pressed(){
    hideAllBorders();
    ui->lakeBorder->show();
}

void OutdoorPathsScreen::on_cityButton_pressed(){
    hideAllBorders();
    ui->cityBorder->show();
}

void OutdoorPathsScreen::hideAllBorders(){
    ui->woodedBorder->hide();
    ui->deerBorder->hide();
    ui->lakeBorder->hide();
    ui->cityBorder->hide();
}


const char* OutdoorPathsScreen::selected_Item(void)
{
    if (ui->woodedBorder->isVisible())
        return ("radnor");
    if (ui->deerBorder->isVisible())
        return ("deer");
    if (ui->lakeBorder->isVisible())
        return ("lake");
    if (ui->cityBorder->isVisible())
        return ("downtown");
}

void OutdoorPathsScreen::on_closeButton_pressed(){
    close();
}

QString getWorkoutName(QString videoName){
    if( videoName.compare("radnor") == 0){
        return "Wooded Path";
    }
    else if( videoName.compare("Deer") == 0){
        return "Deer Trail";
    }
    else if( videoName.compare("lake") == 0){
        return "Lake Trail";
    }
    else{ // videoName.compare("downtown") == 0
        return "City Walk";
    }
}

Workout* OutdoorPathsScreen::createTrailWorkout(QString videoName){
    Workout* workout = Workout::load(TRAILS_PATH, videoName);

    if( workout == NULL){
        workout = Workout::createWorkout(NULL, MIN_SPEED, 1, timeSliderWidget.value);
    }

    workout->name = getWorkoutName(videoName);
    workout->_weight = weightSliderWidget.value;

    Workout::increaseWorkoutIntensity(workout, intensitySliderWidget.getPercentage());

    return workout;
}

void OutdoorPathsScreen::on_startButton_pressed(){

    QString videoName  = selected_Item();
    QString videoPath = TRAILS_PATH + "/" + videoName + ".avi";

    Workout* workout = createTrailWorkout(videoName);
    workout->visualization = VIDEO_VISUALIZATION;
    workout->videoPath = videoPath;

    MainScreen::getMainScreen()->startWorkout(workout);

    close();
}

bool OutdoorPathsScreen::event(QEvent *event)
{
    if(event->type() == POINTER_EVENT_TYPE){
        PointerEvent* pointerEvent = (PointerEvent*)event;

        if(pointerEvent->pointer == &intensitySliderWidget){
            updateHistoryFromIntensity();
        }
    }

    return QWidget::event(event);
}

void OutdoorPathsScreen::updateHistoryFromIntensity(){
    for(int i=0;i<HISTORY_WIDTH;i++){
        /**
         * Subtract one so that intensity 1 is only one row high.
         */
        history[i] = intensitySliderWidget.value * 2 - 1;
    }

    historyWidget.repaint();
}

#include "outdoorpathsscreen.h"
#include "ui_outdoorpathsscreen.h"
#include "pointerevent.h"
#include "screens.h"
#include "mainscreen.h"
#include "workout.h"
#include "utils.h"

static const int HISTORY_WIDTH = 12;
static const int HISTORY_HEIGHT = 10;

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

void OutdoorPathsScreen::on_closeButton_pressed(){
    close();
}

const char* OutdoorPathsScreen::selected_Item(void)
{
    if (ui->woodedBorder->isVisible())
        return ("/videos/trails/radnor.avi");
    if (ui->deerBorder->isVisible())
        return ("/videos/trails/deer.avi");
    if (ui->lakeBorder->isVisible())
        return ("/videos/trails/lake.avi");
    if (ui->cityBorder->isVisible())
        return ("/videos/trails/downtown.avi");
}

void OutdoorPathsScreen::on_startButton_pressed(){

    float percentage = intensitySliderWidget.value/intensitySliderWidget.max;

    float speed = percentage * Utils::getMAX_SPEED();
    float grade = percentage * MAX_GRADE;

    Workout* workout = Workout::createWorkout("Outdoor Path", speed, grade, timeSliderWidget.value);
    MainScreen::getMainScreen()->startWorkout(workout);

    const char* selection = selected_Item();
    MainScreen::getMainScreen()->ShowWidget(VIDEO_VISUALIZATION,selection,NULL);

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

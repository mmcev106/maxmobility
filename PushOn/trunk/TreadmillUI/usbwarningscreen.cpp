#include "usbwarningscreen.h"
#include "ui_usbwarningscreen.h"

UsbWarningScreen::UsbWarningScreen(QString backgroundResource) :
    QWidget(NULL),
    ui(new Ui::UsbWarningScreen)
{
    ui->setupUi(this);
    ui->backgroundLabel->setPixmap(QPixmap(backgroundResource));
}

UsbWarningScreen::~UsbWarningScreen()
{
    delete ui;
}

void UsbWarningScreen::on_closeButton_pressed()
{
    close();
}

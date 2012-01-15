#ifndef USBWARNINGSCREEN_H
#define USBWARNINGSCREEN_H

#include <QWidget>

namespace Ui {
    class UsbWarningScreen;
}

class UsbWarningScreen : public QWidget
{
    Q_OBJECT

public:
    explicit UsbWarningScreen(QString backgroundResource);
    ~UsbWarningScreen();

private slots:
    void on_closeButton_pressed();

private:
    Ui::UsbWarningScreen *ui;
};

#endif // USBWARNINGSCREEN_H

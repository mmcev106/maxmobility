#ifndef MESSAGESCREEN_H
#define MESSAGESCREEN_H

#include "abstractscreen.h"
#include <QTimer>

namespace Ui {
    class MessageScreen;
}

static const int FIRST_TIMEOUT = 2;
static const int CLOSE_TIMEOUT = 7;

class MessageScreen : public AbstractScreen
{
    Q_OBJECT

public:
    explicit MessageScreen(QWidget *parent, QString message);
    ~MessageScreen();
    void setText(QString message);

private:
    Ui::MessageScreen *ui;

protected:
    void keyPressEvent(QKeyEvent* event);
};

#endif // MESSAGESCREEN_H

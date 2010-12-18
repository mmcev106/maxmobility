#include "abstractscreen.h"

AbstractScreen::AbstractScreen(QWidget *parent) :
    QWidget(parent)
{
    setAttribute( Qt::WA_DeleteOnClose );
}

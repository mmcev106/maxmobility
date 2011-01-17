#ifndef INVISIBLEBUTTON_H
#define INVISIBLEBUTTON_H

#include <QPushButton>

class InvisibleButton : public QPushButton
{
    Q_OBJECT
public:
    explicit InvisibleButton(QWidget *parent = 0);
    bool isHighlighted();
    void setHighlighted(bool highlight);

    void setBackgroundPixmap(QPixmap*);

    bool highlightOnPress;


signals:

public slots:

private:
    bool currentlyPressed;
    bool highlighted;
    void paintEvent(QPaintEvent *);
    QPixmap* backgroundPixmap;

private slots:
    void pressed();
    void released();
};

#endif // INVISIBLEBUTTON_H

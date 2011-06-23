#ifndef ABSTRACTSCREEN_H
#define ABSTRACTSCREEN_H

#include <QWidget>
#include <QTimer>
#include <QLabel>

class AbstractScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractScreen(QWidget *parent = 0);

private:
    QTimer* mouseTimer;
    QLabel mouseLabel;
    QTimer accActionTimer;
    QObject* lastAccButtonPressed;

protected:
//    void mouseReleaseEvent(QMouseEvent *event);
      void virtual keyPressEvent(QKeyEvent* event);

      bool handleAccAction(QString audioFile);

signals:

public slots:
    void surroundCursor();

};

#endif // ABSTRACTSCREEN_H

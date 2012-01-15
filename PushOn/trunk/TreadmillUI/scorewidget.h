#ifndef SCOREWIDGET_H
#define SCOREWIDGET_H
#include <QWidget>
#include <QString>

namespace Ui {
    class ScoreWidget;
}

class ScoreWidget : public QWidget
{
    Q_OBJECT

    public:
        //explicit ScoreWidget(QWidget *parent = 0);
        explicit ScoreWidget(QWidget *parent = 0, QString title = "", QString results = "");
        ~ScoreWidget();
        void setText(QString title, QString results);

    private:
         Ui::ScoreWidget *ui;

    private slots:

};

#endif // SCOREWIDGET_H

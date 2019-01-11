#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtUiPlugin/QDesignerExportWidget>

namespace Ui {
class Widget;
}

class  Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *ev);

    void Calculation(double, double);
    struct StructCircle
    {
        QPointF CircleOrigin;
        double diameter;
    };
    StructCircle  MaxCircle;
    StructCircle  CenterCircle;
    StructCircle  ClickCircle;

    double ratio;
    double Click_x;
    double Click_y;

    QMouseEvent *click;
    Ui::Widget *ui;

private slots:
    void reshow(QString);


};

#endif // WIDGET_H

#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QtMath>
#include <QBrush>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(this->ui->doubleSpinBox_X,SIGNAL(valueChanged(QString)),this,SLOT(reshow(QString)));
    connect(this->ui->doubleSpinBox_Y,SIGNAL(valueChanged(QString)),this,SLOT(reshow(QString)));
    MaxCircle.CircleOrigin.setX(100);
    MaxCircle.CircleOrigin.setY(180);
    MaxCircle.diameter=20;

    CenterCircle.diameter=2;
    ClickCircle.diameter=CenterCircle.diameter;
    ratio=5;

    Click_x=MaxCircle.CircleOrigin.x();
    Click_y=MaxCircle.CircleOrigin.y();



}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.drawEllipse(MaxCircle.CircleOrigin.x()-((MaxCircle.diameter*ratio)/2),MaxCircle.CircleOrigin.y()-((MaxCircle.diameter*ratio)/2),
                        MaxCircle.diameter*ratio,MaxCircle.diameter*ratio);                                       //画MAX圆

    painter.setPen(Qt::gray);
    painter.setPen(Qt::DotLine);
    painter.drawLine(MaxCircle.CircleOrigin.x()-((MaxCircle.diameter*ratio)/2),MaxCircle.CircleOrigin.y(),
                     MaxCircle.CircleOrigin.x()+((MaxCircle.diameter*ratio)/2),MaxCircle.CircleOrigin.y());       //画X线过圆心
    painter.drawLine(MaxCircle.CircleOrigin.x(),MaxCircle.CircleOrigin.y()-((MaxCircle.diameter*ratio)/2),
                     MaxCircle.CircleOrigin.x(),MaxCircle.CircleOrigin.y()+((MaxCircle.diameter*ratio)/2));       //画Y线过圆心

    painter.setPen(Qt::black);
    //    painter.setBrush(Qt::green);

    //    painter.drawEllipse(MaxCircle.CircleOrigin.x()-(CenterCircle.diameter*ratio/2),MaxCircle.CircleOrigin.y()-(CenterCircle.diameter*ratio/2),
    //                        CenterCircle.diameter*ratio,CenterCircle.diameter*ratio);       //画中心圆
    painter.setBrush(Qt::gray);
    painter.drawEllipse(Click_x-(ClickCircle.diameter*ratio/2),Click_y-(ClickCircle.diameter*ratio/2),
                        ClickCircle.diameter*ratio,ClickCircle.diameter*ratio);                           //画鼠标点击圆
}
void Widget::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton)
    {
        double tempclickX;
        double tempclickY;
        tempclickX =event->x();
        tempclickY =event->y();
        qDebug()<<"鼠标点击位置："<<event->pos();
        Calculation(tempclickX,tempclickY);

    }

    this->repaint();

}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    double tempclickX;
    double tempclickY;
    tempclickX =event->x();
    tempclickY =event->y();
    qDebug()<<"鼠标移动到："<<event->pos();
    Calculation(tempclickX,tempclickY);
    this->repaint();
}
void Widget::reshow(QString)
{
    double tempclickX;
    double tempclickY;
    tempclickX=ui->doubleSpinBox_X->text().toDouble()*ratio+MaxCircle.CircleOrigin.x();
    tempclickY=ui->doubleSpinBox_Y->text().toDouble()*ratio*(-1)+MaxCircle.CircleOrigin.y();
    Calculation(tempclickX,tempclickY);
    this->repaint();

}
void Widget::keyPressEvent(QKeyEvent *event)   //键盘按下事件
{
    if(event->key() == Qt::Key_Left)
    {
        double tempclickX;
        double tempclickY;
        if(Click_x==MaxCircle.CircleOrigin.x())
        {
            tempclickX=Click_x-ratio;

        }
        else
        {
        tempclickX =Click_x-1;
        }
        tempclickY =Click_y;
        Calculation(tempclickX,tempclickY);
        this->repaint();


    }
    if(event->key() == Qt::Key_Right)
    {
        double tempclickX;
        double tempclickY;
        if(Click_x==MaxCircle.CircleOrigin.x())
        {
            tempclickX=Click_x+ratio;
        }
        else
        {
        tempclickX =Click_x+1;
        }
        tempclickY =Click_y;
        Calculation(tempclickX,tempclickY);
        this->repaint();

    }
    if(event->key() == Qt::Key_Up)
    {
        double tempclickX;
        double tempclickY;
        tempclickX =Click_x;
        if(Click_y==MaxCircle.CircleOrigin.y())
        {
            tempclickY=Click_y-ratio;
        }
        else
        {
        tempclickY =Click_y-1;
        }

        Calculation(tempclickX,tempclickY);
        this->repaint();

    }
    if(event->key() == Qt::Key_Down)
    {
        double tempclickX;
        double tempclickY;
        tempclickX =Click_x;
        if(Click_y==MaxCircle.CircleOrigin.y())
        {
            tempclickY=Click_y+ratio;
        }
        else
        {
        tempclickY =Click_y+1;
        }
        Calculation(tempclickX,tempclickY);
        this->repaint();

    }
}
void Widget::Calculation(double tempclickX,double tempclickY)
{


    double disA= (MaxCircle.CircleOrigin.x()-tempclickX)*(MaxCircle.CircleOrigin.x()-tempclickX);                //两点之间距离
    double disB= (MaxCircle.CircleOrigin.y()-tempclickY)*(MaxCircle.CircleOrigin.y()-tempclickY);
    double DisClickCircle=sqrt(disA+disB)/ratio;



    if(DisClickCircle>(MaxCircle.diameter/2))
    {
        qDebug()<<"警告：坐标错误，显示可能有误";
        return;
    }
    Click_x=tempclickX;
    Click_y=tempclickY;

    ui->doubleSpinBox_X->blockSignals(true);
    ui->doubleSpinBox_Y->blockSignals(true);

    this->ui->doubleSpinBox_X->setValue((Click_x-MaxCircle.CircleOrigin.x())/ratio);
    this->ui->doubleSpinBox_Y->setValue((Click_y-MaxCircle.CircleOrigin.y())/ratio*(-1));

    ui->doubleSpinBox_X->blockSignals(false);
    ui->doubleSpinBox_Y->blockSignals(false);
    this->ui->label_distance->setText(QString::number(DisClickCircle, 'f', 2));
    double SlopeA=-(Click_y-MaxCircle.CircleOrigin.y());                              //求斜率
    double SlopeB=Click_x-MaxCircle.CircleOrigin.x();
    double SlopeK=SlopeA/SlopeB;

    double angle=(qAtan(SlopeK)/(2*M_PI))*360;          //反三角函数求角度
    double Clockwise;
    double AntiClockwise;
    if (Click_x<MaxCircle.CircleOrigin.x())             //判断角度
    {
        angle=180+(qAtan(SlopeK)/(2*M_PI))*360;
    }
    else if(Click_x>=MaxCircle.CircleOrigin.x()&&Click_y>=MaxCircle.CircleOrigin.y())
    {
        angle=360+(qAtan(SlopeK)/(2*M_PI))*360;
    }
    this->ui->label_angle->setText(QString::number(angle, 'f', 2));

    if(angle<=180)  //判断逆时针角度
    {
        AntiClockwise=180-angle;
        this->ui->label_AntiClockwise->setText(QString::number(AntiClockwise, 'f', 2));
    }
    else
    {
        AntiClockwise=360-angle+180;
        this->ui->label_AntiClockwise->setText(QString::number(AntiClockwise, 'f', 2));
    }
    Clockwise =360-AntiClockwise;                        //顺时针判断
    this->ui->label_Clockwise->setText(QString::number(Clockwise, 'f', 2));
    if(AntiClockwise==0)
    {
        this->ui->label_Clockwise->setText("0.00");
    }


    if(MaxCircle.CircleOrigin.x()-1*ratio < Click_x && Click_x < MaxCircle.CircleOrigin.x()+1*ratio) //X轴吸附
    {

        this->ui->doubleSpinBox_X->setValue(0);

        Click_x= MaxCircle.CircleOrigin.x();
    }
    if(MaxCircle.CircleOrigin.y()-1*ratio < Click_y&& Click_y<MaxCircle.CircleOrigin.y()+1*ratio)   //y轴吸附
    {

        this->ui->doubleSpinBox_Y->setValue(0);
        Click_y = MaxCircle.CircleOrigin.y();
    }

    if(DisClickCircle<=CenterCircle.diameter/2)      //点在中心圆
    {
        Click_x=MaxCircle.CircleOrigin.x();
        Click_y=MaxCircle.CircleOrigin.y();
        this->ui->label_distance->setText("0");
        this->ui->label_angle->setText("0");
        this->ui->label_Clockwise->setText("0");
        this->ui->label_AntiClockwise->setText("0");
        ui->doubleSpinBox_X->blockSignals(true);
        ui->doubleSpinBox_Y->blockSignals(true);

        this->ui->doubleSpinBox_X->setValue(0);
        this->ui->doubleSpinBox_Y->setValue(0);
        ui->doubleSpinBox_X->blockSignals(false);
        ui->doubleSpinBox_Y->blockSignals(false);
    }
    if(DisClickCircle>(MaxCircle.diameter/2)-ClickCircle.diameter/2)
    {
        double DisCircularcut=(MaxCircle.diameter/2)-(ClickCircle.diameter/2);
        double c=(qAtan(SlopeK)/(2*M_PI))*360;
        this->ui->label_distance->setText(QString::number(DisCircularcut, 'f', 2));
        if(Click_x>MaxCircle.CircleOrigin.x())      //如果点击生成的圆于Max圆重叠则生成圆在Max圆内相切
        {
            Click_x=(int)(MaxCircle.CircleOrigin.x()+(DisCircularcut*ratio*(cos((int) c*M_PI/180))));
            Click_y=(int)(MaxCircle.CircleOrigin.y()-(DisCircularcut*ratio*(sin((int) c*M_PI/180))));
        }
        else if(Click_x<MaxCircle.CircleOrigin.x())
        {
            Click_x=(int)(MaxCircle.CircleOrigin.x()-(DisCircularcut*ratio*(cos((int) c*M_PI/180))));
            Click_y=(int)(MaxCircle.CircleOrigin.y()+(DisCircularcut*ratio*(sin((int) c*M_PI/180))));
        }
        else if(Click_x==MaxCircle.CircleOrigin.x()&&Click_y>MaxCircle.CircleOrigin.y())
        {
            Click_x=MaxCircle.CircleOrigin.x();
            Click_y=MaxCircle.CircleOrigin.y()+DisCircularcut*ratio;
        }
        else
        {
            Click_x=MaxCircle.CircleOrigin.x();
            Click_y=MaxCircle.CircleOrigin.y()-DisCircularcut*ratio;
        }
        ui->doubleSpinBox_X->blockSignals(true);
        ui->doubleSpinBox_Y->blockSignals(true);

        this->ui->doubleSpinBox_X->setValue((Click_x-MaxCircle.CircleOrigin.x())/ratio);
        this->ui->doubleSpinBox_Y->setValue((Click_y-MaxCircle.CircleOrigin.y())/ratio*(-1));
        ui->doubleSpinBox_X->blockSignals(false);
        ui->doubleSpinBox_Y->blockSignals(false);
    }
}



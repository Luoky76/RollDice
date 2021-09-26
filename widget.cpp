#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(1000,618);
    setWindowTitle("欢乐博饼");
    setWindowIcon(QIcon(":/resource/mooncakeIcon.png"));

    backgroundInit();   //初始化背景元素（包括按钮）

    connect(btn_start,&MyButton::mouseEntered,this,&Widget::enterAnimation);
    connect(btn_start,&MyButton::mouseLeft,this,&Widget::leaveAnimation);
}

void Widget::leaveAnimation()
{
    QPropertyAnimation *animation = new QPropertyAnimation(moon,"geometry"); //设置恢复动画
    animation->setDuration(1000);
    animation->setStartValue(QRect(moon->x(),moon->y(),moon->width(),moon->height()));
    animation->setEndValue(QRect(width()-moon->width(),-moon->height()*0.3,moon->width(),moon->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

    animation = new QPropertyAnimation(change,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(change->x(),change->y(),change->width(),change->height()));
    animation->setEndValue(QRect(0,height()-change->height(),change->width(),change->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void Widget::enterAnimation()
{
    QPropertyAnimation *animation = new QPropertyAnimation(moon,"geometry"); //设置凸显按钮的动画
    animation->setDuration(1000);
    animation->setStartValue(QRect(width()-moon->width(),-moon->height()*0.3,moon->width(),moon->height()));
    animation->setEndValue(QRect(width()-moon->width()+100,-moon->height()*0.3-100,moon->width(),moon->height()));
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();

    animation = new QPropertyAnimation(change,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(0,height()-change->height(),change->width(),change->height()));
    animation->setEndValue(QRect(-100,height()-change->height()+100,change->width(),change->height()));
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
}

void Widget::backgroundInit()
{
    QPixmap pixmap;

    background = new QLabel(this);//背景图片
    pixmap.load(":/resource/background/background.png");
    pixmap = pixmap.scaled(width(),height());
    background->setGeometry(0,0,width(),height());
    background->setPixmap(pixmap);
    background->move(0,0);

    btn_start = new MyButton(":/resource/button/start.png","",this);
    btn_start->move((width()-btn_start->width())*0.5,(height()-btn_start->height())*0.5);

    change = new QLabel(this);    //嫦娥图片
    pixmap.load(":/resource/background/change.png");
    pixmap = pixmap.scaled(500,500,Qt::KeepAspectRatio);
    change->setGeometry(0,0,pixmap.width(),pixmap.height());
    change->setPixmap(pixmap);
    change->move(0,height()-change->height());

    moon = new QLabel(this);       //月亮图片
    pixmap.load(":/resource/background/moon.png");
    pixmap = pixmap.scaled(700,700,Qt::KeepAspectRatio);
    moon->setGeometry(0,0,pixmap.width(),pixmap.height());
    moon->setPixmap(pixmap);
    moon->move(width()-moon->width(),-moon->height()*0.3);
}

Widget::~Widget()
{
    delete ui;
}

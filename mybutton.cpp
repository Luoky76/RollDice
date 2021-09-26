#include "mybutton.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>

MyButton::MyButton(QString normalImg,QString pressImg,QWidget *parent):QPushButton(parent)
{
    normalImgPath = normalImg;
    if (pressImg=="") pressImgPath = normalImgPath;
    else pressImgPath = pressImg;

    QPixmap pixmap;
    bool ret = pixmap.load(normalImgPath);  //判断是否能正常加载图片
    if (!ret)
    {
        qDebug()<<normalImg<<"加载图片失败 in myButton";
    }
    this->setFixedSize(pixmap.width(),pixmap.height()); //根据图片尺寸设置固定窗口尺寸
    this->setStyleSheet("QPushButton{border:0px;}");    //设置不规则的图片样式表 边框0像素
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    connect(this,&MyButton::clicked,this,&MyButton::zoom);   //点击按钮来执行跳动特效

    this->setCursor(Qt::PointingHandCursor);    //设置鼠标样式
}

void MyButton::zoomDown(int dy)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);   //创建动画对象
    animation->setDuration(200);    //设置时间间隔
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->width()));   //设置起始位置
    animation->setEndValue(QRect(this->x(),this->y()+dy,this->width(),this->width()));  //设置结束位置，按钮将变到该位置，但按钮的x和y并不改变
    animation->setEasingCurve(QEasingCurve::OutBounce); //设置缓和曲线，QEasingCurve::OutBounce为弹跳效果
    animation->start(); //开始执行动画
}

void MyButton::zoomUp(int dy)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);   //创建动画对象
    animation->setDuration(200);    //设置时间间隔
    animation->setStartValue(QRect(this->x(),this->y()+dy,this->width(),this->width()));   //设置起始位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->width()));  //设置结束位置，按钮将变到该位置
    animation->setEasingCurve(QEasingCurve::OutBounce); //设置缓和曲线，QEasingCurve::OutBounce为弹跳效果
    animation->start(); //开始执行动画

    connect(animation,&QPropertyAnimation::finished,[=](){  //动画结束后重新连接按钮和特效
        connect(this,&MyButton::clicked,this,&MyButton::zoom);
    });
}

void MyButton::zoom()   //此函数已解决了连续按按钮会导致的按钮偏移bug
{
    disconnect(this,&MyButton::clicked,this,&MyButton::zoom);   //断开连接，防止多次触发
    int dy = this->height()*0.15;   //垂直跳跃距离
    zoomDown(dy);     //向下跳跃
    zoomUp(dy);    //向上跳跃
}

void MyButton::mousePressEvent(QMouseEvent *ev)  //接收鼠标按下事件来切换按钮图标
{
    QPixmap pixmap;
    bool ret = pixmap.load(pressImgPath);
    if (!ret)
    {
        qDebug()<<pressImgPath<<"加载图片失败 mousePressEvent";
        return QPushButton::mousePressEvent(ev);
    }
    this->setFixedSize(pixmap.width(),pixmap.height()); //根据图片尺寸设置固定窗口尺寸
    this->setStyleSheet("QPushButton{border:0px;}");    //设置不规则的图片样式表 边框0像素
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    QPushButton::mousePressEvent(ev);
}

void MyButton::mouseReleaseEvent(QMouseEvent *ev)    //接收鼠标松开事件来切换按钮图标
{
    QPixmap pixmap;
    bool ret = pixmap.load(normalImgPath);
    if (!ret)
    {
        qDebug()<<normalImgPath<<"加载图片失败 mousePressEvent";
        return QPushButton::mouseReleaseEvent(ev);
    }
    this->setFixedSize(pixmap.width(),pixmap.height()); //根据图片尺寸设置固定窗口尺寸
    this->setStyleSheet("QPushButton{border:0px;}");    //设置不规则的图片样式表 边框0像素
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    QPushButton::mouseReleaseEvent(ev);
}

void MyButton::enterEvent(QEnterEvent *)
{
    emit mouseEntered();
}

void MyButton::leaveEvent(QEvent *)
{
    emit mouseLeft();
}

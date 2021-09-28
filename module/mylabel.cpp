#include "mylabel.h"
#include <QLabel>
#include <QMouseEvent>

MyLabel::MyLabel(QString iconPath,QWidget *parent):QLabel(parent)
{
    QPixmap pixmap(iconPath);
    setFixedSize(pixmap.width(),pixmap.height());   //根据图片大小创建
    setPixmap(pixmap);
    setCursor(Qt::PointingHandCursor);  //设置鼠标样式
}

MyLabel::MyLabel(QWidget *parent):QLabel(parent)
{
    setCursor(Qt::PointingHandCursor);  //设置鼠标样式
}

void MyLabel::setIcon(QString iconPath)
{
    QPixmap pixmap(iconPath);
    setFixedSize(pixmap.width(),pixmap.height());   //根据图片大小创建
    setPixmap(pixmap);
}

void MyLabel::enterEvent(QEnterEvent *)
{
    emit mouseEntered();
}

void MyLabel::leaveEvent(QEvent *)
{
    emit mouseLeft();
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) //如果点击的是鼠标左键
    {
        emit click();
    }
}

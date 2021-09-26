#ifndef WIDGET_H
#define WIDGET_H

#include <mybutton.h>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QLabel *change;  //嫦娥图片
    QLabel *moon;    //月亮图片
    QLabel *background; //背景图片
    MyButton *btn_start;
    void backgroundInit();
    void enterAnimation();  //鼠标进入按钮的动画
    void leaveAnimation();  //鼠标离开按钮的动画
};
#endif // WIDGET_H

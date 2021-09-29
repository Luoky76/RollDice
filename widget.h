#ifndef WIDGET_H
#define WIDGET_H

#include "mysetwindow.h"
#include "playwidget.h"
#include "module/mybutton.h"
#include "module/mylabel.h"
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QScreen>
#include <QApplication>

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
    QLabel *rule;
    MyLabel *ruleHint;  //游戏规则引导
    MyButton *btn_singleMode;   //单机模式按钮
    MyButton *btn_onlineMode;   //联机模式按钮
    void backgroundInit();
    void enterAnimation();  //鼠标进入按钮的动画
    void leaveAnimation();  //鼠标离开按钮的动画
    void showRule();    //显示规则
    void hideRule();    //隐藏规则
};
#endif // WIDGET_H

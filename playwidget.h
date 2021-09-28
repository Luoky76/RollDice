#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include <module/mylabel.h>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QScreen>
#include <QApplication>
#include <QIcon>
#include <QPixmap>
#include <QRandomGenerator>
#include <QDebug>
#include <QMessageBox>
#include <QListWidget>
#include <QFile>

class PlayWidget : public QWidget
{
    Q_OBJECT
public:
    static PlayWidget *playWidgetInstance();    //单例模式

private:
    explicit PlayWidget(QWidget *parent = nullptr);
    static PlayWidget *playWidget;
    void closeEvent(QCloseEvent *ev) override;  //窗口关闭事件

    MyLabel *btn_roll;  //摇骰子按钮
    QTimer *rollTimer1;  //用于摇骰子的按钮的动画
    QTimer *rollTimer2; //用于六个骰子的动画

    QLabel *dices[6];   //六个骰子的图片
    int diceNumber[6];  //六个骰子的点数
    QLabel *background;  //背景图片
    QLabel *bowl;        //碗图片
    QString prizeGrade[12]; //12级的奖项的名称
    QListWidget *prizeRecord;   //获奖记录表

    void backgroundInit();  //初始化背景元素
    void prizeInit();   //初始化获奖等级
    void handleRollTimer2();//响应计时器2的槽函数
    void rollDice();    //摇六个骰子
    int calcPrizeGrade(); //计算获奖等级
    QString ReadQssFile(const QString &filePath);   //读取qss样式文件

signals:
    void windowClose();//窗口关闭信号
};
#endif // PLAYWIDGET_H

#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include "module/mylabel.h"
#include "playerwidget.h"
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
#include <QList>
#include <QSize>
#include <QFont>

class PlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayWidget(int playerCnt,QWidget *parent = nullptr);
    void addPlayer(int playerCnt);  //添加玩家
    void setPlayerName(int idx,QString name);   //设置某个特定玩家的名字
    void gameStart();   //开始游戏
    void gameOver();    //结束游戏

private:

    static PlayWidget *playWidget;
    void closeEvent(QCloseEvent *ev) override;  //窗口关闭事件

    MyLabel *btn_roll;  //摇骰子按钮
    bool btn_roll_locked;   //是否锁定摇骰子按钮
    void startRoll();   //摇骰子

    QTimer *rollTimer1;  //用于摇骰子的按钮的动画
    QTimer *rollTimer2; //用于六个骰子的动画

    QLabel *dices[6];   //六个骰子的图片
    int diceNumber[6];  //六个骰子的点数
    QLabel *background;  //背景图片
    QLabel *bowl;        //碗图片
    QString prizeGrade[12]; //12级的奖项的名称
    QListWidget *prizeRecord;   //获奖记录表

    QList <PlayerWidget *> players;  //玩家实例
    int currentPlayer = 0;  //轮到哪名玩家
    void nextPlayer();  //下一名玩家

    void backgroundInit();  //初始化背景元素
    void handleRollTimer2();//响应计时器2的槽函数，得到获奖结果
    void rollDice();    //摇六个骰子
    void prizeInit();   //初始化获奖等级
    int calcPrizeGrade(); //计算获奖等级
    void addRankItem(QListWidgetItem *item);    //向排名表中添加新记录

    void showPlayer();  //显示所有玩家
    void setPlayerPos();    //设置玩家位置
    QString ReadQssFile(const QString &filePath);   //读取qss样式文件

    void artificialStart();   //人机掷骰子
    QTimer *aiTimer;    //人机响应计时器

signals:
    void windowClose();//窗口关闭信号
};
#endif // PLAYWIDGET_H

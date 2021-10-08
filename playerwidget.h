#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include "namebox.h"
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QLineEdit>
#include <QComboBox>
#include <QPropertyAnimation>
#include <QPainter>
#include <QTimer>

class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    const static int artificial = 0;
    const static int person = 1;
    explicit PlayerWidget(QString pixmapPath = "",QWidget *parent = nullptr);
    QString getPlayerName();    //获取玩家名称
    void setPlayerName(QString name);   //设置玩家名
    int getPlayerMode();    //获取玩家模式
    void setPlayerMode(int mode);   //修改玩家模式
    void setPixmap(QString pixmapPath);   //设置玩家图片
    void animationStart();  //开始边框特效
    void animationStop();   //结束边框特效

private:
    QLabel *playerPixmap;   //玩家图片
    QString pixmapPath;     //玩家图片路径
    void setPlayerPixmap(); //设置玩家图片

    QLineEdit *playerName;   //玩家名编辑栏
    QComboBox *playerMode;   //选择人机或玩家模式的下拉框
    void setRandomPlayerName();  //随机生成玩家名


    //以下设置边框特效
    QColor borderColor;               //边框颜色
    float alpha;                      //α通道值
    QPropertyAnimation *animation;    //动画
    QTimer *timer;  //更新动画的计时器
    bool animationOn = false;   //表示当前是否有动画
    void animationInit();   //初始化动画所需属性
    void paintEvent(QPaintEvent *event) override;

signals:

};

#endif // PLAYERWIDGET_H

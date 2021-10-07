#ifndef MYSETWINDOW_H
#define MYSETWINDOW_H

#include "module/mybutton.h"
#include "playwidget.h"
#include <QMainWindow>
#include <QLabel>
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>
class MySetWindow : public QMainWindow
{
    Q_OBJECT
public:
    static MySetWindow *mySetWindowInstance();    //单例模式

private:
    static MySetWindow* mySetWindow;    //记录单例指针
    explicit MySetWindow(QWidget *parent = nullptr);

    QString qnum;   //玩家人数
    QString qname;  //玩家名字

    QLabel *background;     //背景图片
    QLabel *theSetPixmap;   //设置的图片

    MyButton *yesBtn;       //确定按钮
    MyButton *gobackBtn;    //返回按钮

    QLineEdit *personNum;   //人数编辑条
    QLineEdit *personName;  //名字编辑条

    PlayWidget *playWidget = nullptr;   //游戏界面指针

    void backgroundInit();  //初始化背景元素
    void closeEvent(QCloseEvent *ev) override;

signals:
    //自定义信号 使得主场景得知返回
    void windowClose();
};

#endif // MYSETWINDOW_H

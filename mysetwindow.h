#ifndef MYSETWINDOW_H
#define MYSETWINDOW_H

#include <QMainWindow>
#include <module/mybutton.h>
#include "playwidget.h"
#include <QLabel>
class MySetWindow : public QMainWindow
{
    Q_OBJECT
public:
    static MySetWindow *mySetWindowInstance();    //单例模式
    QString qnum;   //玩家人数
    QString qname;  //玩家名字

private:
    static MySetWindow* mySetWindow;    //记录单例指针
    explicit MySetWindow(QWidget *parent = nullptr);

    QLabel *background;     //背景图片
    QLabel *theSetPixmap;   //设置的图片

    MyButton *yesBtn;       //确定按钮
    MyButton *gobackBtn;    //返回按钮

    QLineEdit *PersonNum;   //人数编辑条
    QLineEdit *PersonName;  //名字编辑条

    void backgroundInit();  //初始化背景元素
    void closeEvent(QCloseEvent *ev) override;

signals:
    //自定义信号 使得主场景得知返回
    void windowClose();
};

#endif // MYSETWINDOW_H

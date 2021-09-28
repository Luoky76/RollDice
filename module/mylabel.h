#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QString>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QString iconPath,QWidget *parent = nullptr);
    explicit MyLabel(QWidget *parent = nullptr);
    void setIcon(QString iconPath); //设置图标，根据图标大小改变尺寸

private:
    void enterEvent(QEnterEvent *ev) override;
    void leaveEvent(QEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;

signals:
    void mouseEntered();    //鼠标进入事件
    void mouseLeft();   //鼠标离开事件
    void click();   //鼠标点击事件
};

#endif // MYLABEL_H

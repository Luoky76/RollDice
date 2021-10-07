#ifndef QWHBREATHWIDGET_H
#define QWHBREATHWIDGET_H

/*
 * 边框呼吸效果
 * 该控件支持为任意继承自QWidget的窗体设置效果
 * 该控件支持设置边框宽度
 * 该控件支持设置边框颜色
 */

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QHBoxLayout>

class QWHBreathWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float m_alpha READ getAlpha WRITE setAlpha)
public:
    explicit QWHBreathWidget(QWidget *parent = nullptr);
    ~QWHBreathWidget();

public:
    //设置特效的窗体
    void setWidget(QWidget *widget);
    //设置边距（边距=线条宽度）
    void setMarginis(int margins);
    //设置边框颜色
    void setBorderColor(QColor color);

    //获取边距
    int getMargins();
    //获取边框颜色
    QColor getBorderColor();

protected:
    void paintEvent(QPaintEvent *);
    void drawBorder(QPainter *painter);

private:
    void setAlpha(float alpha);
    float getAlpha()    const;

    int m_contentMargin;                //保存控件边距
    QColor m_borderColor;               //边框颜色
    float m_alpha;                      //α通道值
    QWidget *m_widget;                  //特效窗体
    QHBoxLayout *m_hLayout;             //水平布局

    QPropertyAnimation *m_animation;    //动画
};

#endif // QWHBREATHWIDGET_H

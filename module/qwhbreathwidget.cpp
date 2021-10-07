#include "qwhbreathwidget.h"

QWHBreathWidget::QWHBreathWidget(QWidget *parent) : QWidget(parent)
{
    m_contentMargin = 8;                //保存控件边距
    m_borderColor = Qt::blue;           //边框颜色
    m_alpha = 255;                      //α通道值
    m_widget = nullptr;                 //特效窗体
    m_hLayout = new QHBoxLayout(this);  //水平布局
    //m_hLayout->setMargin(0);
    m_hLayout->setContentsMargins(m_contentMargin, m_contentMargin, m_contentMargin, m_contentMargin);
    this->setLayout(m_hLayout);

    m_animation = new QPropertyAnimation(this, "m_alpha", this);
    m_animation->setStartValue(50);
    m_animation->setKeyValueAt(0.5, 255);
    m_animation->setEndValue(50);
    m_animation->setDuration(4000);
    m_animation->setLoopCount(-1);
    m_animation->start();
    connect(m_animation, SIGNAL(finished()), this, SLOT(onFinished()));
}

QWHBreathWidget::~QWHBreathWidget()
{

}

void QWHBreathWidget::setWidget(QWidget *widget)
{
    //清除布局，但不包括布局内控件
    if (this->layout() != nullptr)
    {
        QLayoutItem *item;
        while ((item = this->layout()->takeAt(0)) != nullptr)
        {
            delete item;
            item = nullptr;
        }
    }
    //重新添加控件
    m_widget = widget;
    m_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_hLayout->addWidget(m_widget);
}

void QWHBreathWidget::setMarginis(int margins)
{
    m_contentMargin = margins;
}

void QWHBreathWidget::setBorderColor(QColor color)
{
    m_borderColor = color;
}

int QWHBreathWidget::getMargins()
{
    return m_contentMargin;
}

QColor QWHBreathWidget::getBorderColor()
{
    return m_borderColor;
}

void QWHBreathWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  //打开反走样功能
    drawBorder(&painter);
}

void QWHBreathWidget::drawBorder(QPainter *painter)
{
    painter->save();

    m_borderColor.setAlpha(m_animation->currentValue().toInt());
    painter->setPen(QPen(m_borderColor, m_contentMargin * 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(rect());

    painter->restore();
}

void QWHBreathWidget::setAlpha(float alpha)
{
    m_alpha = alpha;
    update();
}

float QWHBreathWidget::getAlpha() const
{
    return m_alpha;
}

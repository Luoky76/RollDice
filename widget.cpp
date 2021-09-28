#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(1500,927);
    setWindowTitle("欢乐博饼");
    setWindowIcon(QIcon(":/resource/mooncakeIcon.png"));

    backgroundInit();   //初始化背景元素（包括按钮）

    connect(btn_start,&MyButton::mouseEntered,this,&Widget::enterAnimation);    //当鼠标进入开始按钮时，移开周围物件
    connect(btn_start,&MyButton::mouseLeft,this,&Widget::leaveAnimation);   //当鼠标离开开始按钮时，恢复周围物件

    connect(ruleHint,&MyLabel::mouseEntered,this,&Widget::showRule);    //当鼠标移动到标签上时，展示游戏规则
    connect(ruleHint,&MyLabel::mouseLeft,this,&Widget::hideRule);   //当鼠标离开标签时，隐藏游戏规则

    connect(btn_start,&MyButton::clicked,[=](){ //按下按钮后打开游戏界面，隐藏此界面
        PlayWidget::playWidgetInstance()->show();
        this->hide();
    });
    connect(PlayWidget::playWidgetInstance(),&PlayWidget::windowClose,[=](){    //游戏界面关闭后，重新展示此界面
        this->show();
    });
}

void Widget::showRule()
{
    QPixmap pixmap(":/resource/rule.png");
    pixmap = pixmap.scaled(600,900,Qt::KeepAspectRatio);
    rule->setFixedSize(pixmap.width(),pixmap.height());
    rule->setPixmap(pixmap);
    rule->move((width()-rule->width())*0.5,height()-rule->height());
}

void Widget::hideRule()
{
    rule->move(width(),height());
}

void Widget::leaveAnimation()
{
    QPropertyAnimation *animation = new QPropertyAnimation(moon,"geometry"); //设置恢复动画
    animation->setDuration(1000);
    animation->setStartValue(QRect(moon->x(),moon->y(),moon->width(),moon->height()));
    animation->setEndValue(QRect(width()-moon->width(),-moon->height()*0.3,moon->width(),moon->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

    animation = new QPropertyAnimation(change,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(change->x(),change->y(),change->width(),change->height()));
    animation->setEndValue(QRect(0,height()-change->height(),change->width(),change->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void Widget::enterAnimation()
{
    QPropertyAnimation *animation = new QPropertyAnimation(moon,"geometry"); //设置凸显按钮的动画
    animation->setDuration(1000);
    animation->setStartValue(QRect(moon->x(),moon->y(),moon->width(),moon->height()));
    animation->setEndValue(QRect(width()-moon->width()+150,-moon->height()*0.3-150,moon->width(),moon->height()));
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();

    animation = new QPropertyAnimation(change,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(change->x(),change->y(),change->width(),change->height()));
    animation->setEndValue(QRect(-150,height()-change->height()+150,change->width(),change->height()));
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();
}

void Widget::backgroundInit()
{
    QPixmap pixmap;

    background = new QLabel(this);//背景图片
    pixmap.load(":/resource/background/background.png");
    pixmap = pixmap.scaled(width(),height());
    background->setGeometry(0,0,width(),height());
    background->setPixmap(pixmap);
    background->move(0,0);

    btn_start = new MyButton(":/resource/button/start.png","",this);
    btn_start->move((width()-btn_start->width())*0.5,(height()-btn_start->height())*0.5);

    change = new QLabel(this);    //嫦娥图片
    pixmap.load(":/resource/background/change.png");
    pixmap = pixmap.scaled(750,750,Qt::KeepAspectRatio);
    change->setGeometry(0,0,pixmap.width(),pixmap.height());
    change->setPixmap(pixmap);
    change->move(0,height()-change->height());
    change->setAttribute(Qt::WA_TransparentForMouseEvents); //设置鼠标事件穿透

    moon = new QLabel(this);       //月亮图片
    pixmap.load(":/resource/background/moon.png");
    pixmap = pixmap.scaled(1050,1050,Qt::KeepAspectRatio);
    moon->setGeometry(0,0,pixmap.width(),pixmap.height());
    moon->setPixmap(pixmap);
    moon->move(width()-moon->width(),-moon->height()*0.3);
    moon->setAttribute(Qt::WA_TransparentForMouseEvents); //设置鼠标事件穿透

    ruleHint = new MyLabel(":/resource/button/rulebutton.png",this);
    ruleHint->move(width()-ruleHint->width(),height()-ruleHint->height()*3);

    rule = new QLabel(this);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenRect = screen->availableVirtualGeometry();  //获取屏幕长宽
    move((screenRect.width()-width())*0.5,(screenRect.height()-height())*0.5);    //居中创建页面
}

Widget::~Widget()
{
    delete ui;
}

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(1282,800);
    setWindowTitle("欢乐博饼");
    setWindowIcon(QIcon(":/resource/mooncakeIcon.png"));

    backgroundInit();   //初始化背景元素（包括按钮）

    connect(btn_singleMode,&MyButton::mouseEntered,this,&Widget::enterAnimation);    //当鼠标进入按钮时，移开周围物件
    connect(btn_onlineMode,&MyButton::mouseEntered,this,&Widget::enterAnimation);
    connect(btn_singleMode,&MyButton::mouseLeft,this,&Widget::leaveAnimation);   //当鼠标离开按钮时，恢复周围物件
    connect(btn_onlineMode,&MyButton::mouseLeft,this,&Widget::leaveAnimation);

    connect(ruleHint,&MyLabel::mouseEntered,this,&Widget::showRule);    //当鼠标移动到标签上时，展示游戏规则
    connect(ruleHint,&MyLabel::mouseLeft,this,&Widget::hideRule);   //当鼠标离开标签时，隐藏游戏规则

    connect(btn_singleMode,&MyButton::clicked,[=](){ //按下单机模式按钮
        QTimer::singleShot(300,[=](){   //延迟一会儿后打开设置界面，隐藏此界面
            MySetWindow::mySetWindowInstance()->show();
            this->hide();
        });
    });

    connect(MySetWindow::mySetWindowInstance(),&MySetWindow::windowClose,[=](){    //设置界面关闭后，重新展示此界面
        this->show();
    });
}

void Widget::showRule()
{
    QPixmap pixmap(":/resource/rule.png");
    rule->setFixedSize(pixmap.width(),pixmap.height());
    rule->setPixmap(pixmap);
    rule->move((width()-rule->width())*0.5,(height()-rule->height())*0.5);
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
    animation->setEasingCurve(QEasingCurve::InCubic);
    animation->start();

    animation = new QPropertyAnimation(change,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(change->x(),change->y(),change->width(),change->height()));
    animation->setEndValue(QRect(0,height()-change->height(),change->width(),change->height()));
    animation->setEasingCurve(QEasingCurve::InCubic);
    animation->start();
}

void Widget::enterAnimation()
{
    QPropertyAnimation *animation = new QPropertyAnimation(moon,"geometry"); //设置凸显按钮的动画
    animation->setDuration(1000);
    animation->setStartValue(QRect(moon->x(),moon->y(),moon->width(),moon->height()));
    animation->setEndValue(QRect(width()-moon->width()+100,-moon->height()*0.3-100,moon->width(),moon->height()));
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start();

    animation = new QPropertyAnimation(change,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(change->x(),change->y(),change->width(),change->height()));
    animation->setEndValue(QRect(-100,height()-change->height()+100,change->width(),change->height()));
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

    //单机模式按钮
    btn_singleMode = new MyButton(":/resource/button/singleMode.png",":/resource/button/singleMode2.png",this);
    btn_singleMode->move((width()-btn_singleMode->width())*0.5,(height()-btn_singleMode->height())*0.4);    //设置按钮位置

    //联机模式按钮
    btn_onlineMode = new MyButton(":/resource/button/onlineMode.png",":/resource/button/onlineMode2.png",this);
    btn_onlineMode->move((width()-btn_onlineMode->width())*0.5,(height()-btn_onlineMode->height())*0.6);    //设置按钮位置

    change = new QLabel(this);    //嫦娥图片
    pixmap.load(":/resource/background/change.png");
    pixmap = pixmap.scaled(500,500,Qt::KeepAspectRatio);
    change->setGeometry(0,0,pixmap.width(),pixmap.height());
    change->setPixmap(pixmap);
    change->move(0,height()-change->height());
    change->setAttribute(Qt::WA_TransparentForMouseEvents); //设置鼠标事件穿透

    moon = new QLabel(this);       //月亮图片
    pixmap.load(":/resource/background/moon.png");
    pixmap = pixmap.scaled(700,700,Qt::KeepAspectRatio);
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

#include "mysetwindow.h"
#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>

MySetWindow* MySetWindow::mySetWindow = nullptr;   //懒汉模式

MySetWindow::MySetWindow(QWidget *parent) : QMainWindow(parent)
{
    //配置场景
    this->setFixedSize(1282,800);
    this->setWindowTitle("游戏设置");
    this->setWindowIcon(QIcon(":/resource/mooncakeIcon.png"));

    backgroundInit();

    connect(yesBtn, &MyButton::clicked, [=]() {
        qnum = PersonNum->text();
        qname = PersonName->text();
        QTimer::singleShot(300, this, [=]() {
            //进入游戏场景
            qDebug() << qnum;
            qDebug() << qname;
            PlayWidget::playWidgetInstance()->show();
            this->hide();
        });
    });
    connect(gobackBtn, &MyButton::clicked, [=]() {
        QTimer::singleShot(300, this, [=]() {
            //告诉场景返回 主场景监听返回按钮
            this->close();
        });
    });
}

MySetWindow* MySetWindow::mySetWindowInstance()
{
    if (mySetWindow == nullptr) mySetWindow = new MySetWindow();
    return mySetWindow;
}

void MySetWindow::backgroundInit()
{
    //设置背景图片
    QPixmap pixmap;

    pixmap.load(":/resource/background/background.png");
    pixmap = pixmap.scaled(width(),height());
    background = new QLabel(this);
    background->setGeometry(0,0,width(),height());
    background->setPixmap(pixmap);

    pixmap.load(":/resource/setup.png");
    theSetPixmap = new QLabel(this);
    theSetPixmap->setFixedSize(pixmap.width(),pixmap.height());
    theSetPixmap->setPixmap(pixmap);
    theSetPixmap->move(this->width()*0.37,this->height()*0.15);

    //设置标题
    PersonNum = new QLineEdit(this);
    PersonNum->setFont(QFont("微软雅黑", 20, QFont::Bold));
    QPalette palette;
    palette.setColor(QPalette::Text, Qt::white);
    PersonNum->setPalette(palette);
    PersonNum->setPlaceholderText("请输入游戏人数 1~8");
    PersonNum->setEchoMode(QLineEdit::Normal);
    PersonNum->setParent(this);
    PersonNum->resize(280, 50);
    PersonNum->setStyleSheet("padding: -1");
    PersonNum->move(this->width() * 0.5 - 100, this->height() * 0.5 - 20);

    PersonName = new QLineEdit(this);
    PersonName->setFont(QFont("微软雅黑", 20, QFont::Bold));
    QPalette palettee;
    palettee.setColor(QPalette::Text, Qt::white);
    PersonName->setPalette(palette);
    PersonName->setPlaceholderText("请输入用户名");
    PersonName->setEchoMode(QLineEdit::Normal);
    PersonName->setParent(this);
    PersonName->resize(280,50);
    PersonName->setStyleSheet("padding: -1");
    PersonName->move(this->width()*0.5-100,this->height()*0.5+220);
    PersonName->setStyleSheet("background-color:rgba(0,0,0,0);");
    PersonNum->setStyleSheet("background-color:rgba(0,0,0,0);");
    PersonName->show();
    PersonNum->show();

    //确定按钮和返回按钮
    yesBtn = new MyButton(":/resource/button/yes.png",":/resource/button/yes2.png",this);
    yesBtn->move(this->width()*0.75,this->height()*0.6);
    gobackBtn = new MyButton(":/resource/button/return.png",":/resource/button/return2.png",this);
    gobackBtn->move(this->width()*0.75,this->height()*0.8);
}

void MySetWindow::closeEvent(QCloseEvent *)
{
    emit windowClose();
}

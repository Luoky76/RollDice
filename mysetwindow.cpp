#include "mysetwindow.h"

MySetWindow* MySetWindow::mySetWindow = nullptr;   //懒汉模式

MySetWindow::MySetWindow(QWidget *parent) : QMainWindow(parent)
{
    //配置场景
    this->setFixedSize(1282,800);
    this->setWindowTitle("游戏设置");
    this->setWindowIcon(QIcon(":/resource/mooncakeIcon.png"));

    backgroundInit();
    connect(personNum,&QLineEdit::textChanged,[=](){    //自动更正玩家数量的不合法输入
        int num = personNum->text().toInt();
        if (num>8) num = 8;
        if (num>0) personNum->setText(QString::number(num));
        else personNum->setText(QString(""));
    });
    connect(yesBtn,&MyButton::clicked,[=]() {
        qnum = personNum->text();
        qname = personName->text().simplified();    //去除首位空字符的玩家名
        QTimer::singleShot(300,this,[=](){
            //进入游戏场景
            if (qnum.toInt()==0) qnum = "1";    //默认为单人游戏
            if (playWidget == nullptr)
            {
                playWidget = new PlayWidget(qnum.toInt());
                //当游戏窗口关闭时，清除内存，关闭本窗口
                connect(playWidget,&PlayWidget::windowClose,[=](){
                    delete playWidget;
                    playWidget = nullptr;
                    this->close();
                });
            }
            if (!qname.isEmpty())   //输入的玩家名不为空
            {
                playWidget->setPlayerName(0,qname);   //设置0号玩家名称
            }
            playWidget->show();
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
    QPalette palette;
    palette.setColor(QPalette::Text, Qt::white);
    personNum = new QLineEdit(this);
    personNum->setFont(QFont("微软雅黑", 20, QFont::Bold));
    personNum->setPalette(palette);
    personNum->setPlaceholderText("请输入游戏人数 1~8");
    personNum->setEchoMode(QLineEdit::Normal);
    personNum->setValidator(new QIntValidator(personNum));  //限制只能输入整数
    personNum->resize(280, 50);
    personNum->setStyleSheet("padding: -1");
    personNum->setStyleSheet("background-color:rgba(0,0,0,0);");
    personNum->move(this->width() * 0.5 - 100, this->height() * 0.5 - 20);
    personNum->show();

    personName = new QLineEdit(this);
    personName->setFont(QFont("微软雅黑", 20, QFont::Bold));
    personName->setPalette(palette);
    personName->setPlaceholderText("请输入用户名");
    personName->setEchoMode(QLineEdit::Normal);
    personName->resize(280,50);
    personName->setStyleSheet("padding: -1");
    personName->setStyleSheet("background-color:rgba(0,0,0,0);");
    personName->move(this->width()*0.5-100,this->height()*0.5+220);
    personName->show();


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

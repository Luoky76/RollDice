#include "playerwidget.h"

PlayerWidget::PlayerWidget(QString pixmapPath, QWidget *parent) : QWidget(parent)
{
    this->pixmapPath = pixmapPath;
    this->setFixedSize(200,230);

    //设置玩家图片
    playerPixmap = new QLabel(this);
    playerPixmap->setFixedSize(200,200);
    playerPixmap->move(0,0);
    setPlayerPixmap();

    //设置玩家名编辑条
    QPalette palette;
    palette.setColor(QPalette::Text,Qt::black);
    playerName = new QLineEdit(this);
    playerName->setFont(QFont("微软雅黑", 15, QFont::Bold));
    playerName->setPalette(palette);
    playerName->setPlaceholderText("player's name");
    playerName->setEchoMode(QLineEdit::Normal);
    playerName->resize(150, 25);
    playerName->setAlignment(Qt::AlignHCenter); //设置文字居中
    playerName->setStyleSheet("background:transparent;border-width:0;border-style:outset"); //设置透明边框背景
    playerName->move(25,170);
    playerName->show();

    connect(playerName,&QLineEdit::editingFinished,[=](){
        if (playerName->text().simplified().isEmpty()) setRandomPlayerName(); //当玩家名变为空时，随机生成新玩家名
        playerName->clearFocus();   //当编辑完成时，隐藏光标
    });

    //设置玩家模式下拉框
    playerMode = new QComboBox(this);
    playerMode->setFixedSize(100,30);
    playerMode->move((this->width()-playerMode->width())*0.5,200);
    playerMode->addItem("人机",artificial);
    playerMode->addItem("玩家",person);
    playerMode->setCurrentText("玩家");   //设置默认为玩家模式

    //为玩家分配随机玩家名
    setRandomPlayerName();

    //初始化动画
    animationInit();
}

QString PlayerWidget::getPlayerName()
{
    return playerName->text();
}

void PlayerWidget::setPlayerName(QString name)
{
    playerName->setText(name);
}

int PlayerWidget::getPlayerMode()
{
    return playerMode->currentData().toInt();
}

void PlayerWidget::setPlayerMode(int mode)
{
    switch (mode) {
    case person:
        playerMode->setCurrentText("玩家");
        break;
    case artificial:
        playerMode->setCurrentText("人机");
        break;
    default:
        qDebug()<<"Unknown mode, please use PlayerWidget::person/artificail";
        break;
    }
}

void PlayerWidget::setPixmap(QString pixmapPath)
{
    this->pixmapPath = pixmapPath;
    setPlayerPixmap();
}

void PlayerWidget::animationStart()
{
    timer->start(30);
    animation->start();
    animationOn = true;
}

void PlayerWidget::animationStop()
{
    timer->stop();
    animation->stop();
    animationOn = false;
    this->update(); //更新以消除白框
}

void PlayerWidget::setPlayerPixmap()
{
    if (pixmapPath=="")
    {
        qDebug()<<"没有玩家的图片";
        return;
    }
    QPixmap pixmap(pixmapPath);
    pixmap = pixmap.scaled(playerPixmap->width(),playerPixmap->height());
    playerPixmap->setPixmap(pixmap);
}

void PlayerWidget::setRandomPlayerName()
{
    playerName->setText(NameBox::getInstance()->getRandomName());
}

void PlayerWidget::animationInit()
{
    borderColor = QColor(87,250,255);
    animation = new QPropertyAnimation(this);
    animation->setTargetObject(this);
    animation->setStartValue(50);
    animation->setKeyValueAt(0.5, 255); //插值
    animation->setEndValue(50);
    animation->setDuration(2000);
    animation->setLoopCount(-1);

    timer = new QTimer();
    connect(timer,&QTimer::timeout,[=](){
        this->update();
    }); //每次到时更新图片
}

void PlayerWidget::paintEvent(QPaintEvent *)
{
    if (animationOn)
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform); //抗锯齿，平滑像素
        borderColor.setAlpha(animation->currentValue().toInt());
        painter.setPen(QPen(borderColor,this->width()*0.1));
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(rect());
    }
    else
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform); //抗锯齿，平滑像素
        borderColor.setAlpha(0);
        painter.setPen(QPen(borderColor,this->width()*0.1));
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(rect());
    }
}

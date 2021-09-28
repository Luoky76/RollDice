#include "playwidget.h"

PlayWidget* PlayWidget::playWidget = nullptr;   //懒汉模式

PlayWidget::PlayWidget(QWidget *parent) : QWidget(parent)
{
    backgroundInit();
    prizeInit();
    connect(btn_roll,&MyLabel::mouseEntered,[=](){  //鼠标进入时，中间骰子的动画开始
        rollTimer1->start(30);
    });
    connect(btn_roll,&MyLabel::mouseLeft,[=](){     //鼠标离开时，中间骰子的动画停止
        rollTimer1->stop();
    });
    connect(rollTimer1,&QTimer::timeout,[=](){   //中间骰子的动画
        static int currentIconPath = 1;
        ++currentIconPath;
        if (currentIconPath > 6) currentIconPath = 1;
        btn_roll->setIcon(QString(":/resource/dice/%1.png").arg(currentIconPath));
     });
    connect(btn_roll,&MyLabel::click,[=]()  //点击按钮时，结束按钮动画，开始六个骰子的动画
    {
        rollTimer1->stop();
        rollTimer2->start(30);
    });
    connect(rollTimer2,&QTimer::timeout,this,&PlayWidget::handleRollTimer2);
}

void PlayWidget::handleRollTimer2()
{
    static int t = 0;   //进入函数的次数
    ++t;
    rollDice();
    if (t >= 10)
    {
        static int playerId = 0;    //记录当前为第几名玩家
        ++playerId;
        rollTimer2->stop();
        QString messageText = "     "+prizeGrade[calcPrizeGrade()]+"          ";
        QString messageTitle = "中奖情况";
        QMessageBox::information(this,messageTitle,messageText,QMessageBox::Ok);
        QListWidgetItem *item = new QListWidgetItem(QString("第 %1 位玩家：").arg(playerId)+messageText);   //点击ok后将获奖记录添加进表格
        prizeRecord->addItem(item);
        t=1;
    }
}

void PlayWidget::rollDice()
{
    QPixmap pixmap;
    for (int i=0;i<6;++i)
    {
        diceNumber[i] = QRandomGenerator::global()->bounded(1,7);  //随机生成摇出的点数
        pixmap.load(QString(":/resource/dice/3D%1.png").arg(diceNumber[i]));
        pixmap = pixmap.scaled(dices[i]->width(),dices[i]->height());
        dices[i]->setPixmap(pixmap);
    }
}

PlayWidget* PlayWidget::playWidgetInstance()
{
    if (playWidget == nullptr) playWidget = new PlayWidget();
    return playWidget;
}

void PlayWidget::closeEvent(QCloseEvent *)
{
    emit windowClose();
}

void PlayWidget::backgroundInit()
{
    setFixedSize(1500,927);
    setWindowIcon(QIcon(":/resource/mooncakeIcon.png"));
    setWindowTitle("开始博饼吧！");

    QPixmap pixmap; //背景图片
    pixmap.load(":/resource/background/background.png");
    pixmap = pixmap.scaled(width(),height());
    background = new QLabel(this);
    background->setGeometry(0,0,width(),height());
    background->setPixmap(pixmap);
    background->move(0,0);

    btn_roll = new MyLabel(":/resource/dice/1.png",this);   //掷骰子按钮
    btn_roll->move((width()-btn_roll->width())*0.8,(height()-btn_roll->height())*0.8);

    rollTimer1 = new QTimer(this);
    rollTimer2 = new QTimer(this);

    pixmap.load(":/resource/bowl.png");
    pixmap = pixmap.scaled(pixmap.width()*2,pixmap.height()*2);
    bowl = new QLabel(this);  //碗
    bowl->setFixedSize(pixmap.width(),pixmap.height());
    bowl->setPixmap(pixmap);
    bowl->move((width()-bowl->width())*0.5,(height()-bowl->height())*0.5);

    pixmap.fill(Qt::transparent);   //六枚骰子
    pixmap = pixmap.scaled(btn_roll->width()*0.3,btn_roll->height()*0.3);
    for (int i=0;i<6;++i)
    {
        dices[i] = new QLabel(this);
        dices[i]->setFixedSize(pixmap.width(),pixmap.height());
        dices[i]->setPixmap(pixmap);
        dices[i]->move(bowl->x()+bowl->width()*(0.25+i%3*0.2),bowl->y()+bowl->height()*(0.3+i/3*0.25));
    }

    prizeRecord = new QListWidget(this);    //获奖记录表
    prizeRecord->setFixedSize(300,600);
    prizeRecord->move(100,(height()-prizeRecord->height())*0.5);
    QString strStyle = ReadQssFile(":/resource/Style Sheet/whiteListWidget.qss");
    prizeRecord->setStyleSheet(strStyle);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenRect = screen->availableVirtualGeometry();  //获取屏幕长宽
    move((screenRect.width()-width())*0.5,(screenRect.height()-height())*0.5);    //居中创建页面
}

void PlayWidget::prizeInit()
{
    prizeGrade[0] = QString("状元插金花");
    prizeGrade[1] = QString("（状元）六博红");
    prizeGrade[2] = QString("（状元）六博黑");
    prizeGrade[3] = QString("（状元）五红");
    prizeGrade[4] = QString("（状元）五黑");
    prizeGrade[5] = QString("状元");
    prizeGrade[6] = QString("对堂");
    prizeGrade[7] = QString("三红");
    prizeGrade[8] = QString("四进");
    prizeGrade[9] = QString("二举");
    prizeGrade[10] = QString("一秀");
    prizeGrade[11] = QString("QAQ");
}

int PlayWidget::calcPrizeGrade()
{
    int eachNumber[7];  //先算出每种点数的骰子有几个
    for (int i=1;i<=6;++i) eachNumber[i] = 0;
    for (int i=0;i<6;++i) ++eachNumber[diceNumber[i]];
    if (eachNumber[4]==4 && eachNumber[1]==2) return 0;
    if (eachNumber[4]==6) return 1;
    for (int i=1;i<=6;++i)
    {
        if (eachNumber[i]==6 && i!=4) return 2;
    }
    if (eachNumber[4]==5) return 3;
    for (int i=1;i<=6;++i)
    {
        if (eachNumber[i]==5 && i!=4) return 4;
    }
    if (eachNumber[4]==4) return 5;
    if (eachNumber[1] && eachNumber[2] && eachNumber[3] && eachNumber[4] && eachNumber[5] && eachNumber[6]) return 6;
    if (eachNumber[4]==3) return 7;
    for (int i=1;i<=6;++i)
    {
        if (eachNumber[i]==4) return 8;
    }
    if (eachNumber[4]==2) return 9;
    if (eachNumber[4]==1) return 10;
    return 11;
}

QString PlayWidget::ReadQssFile(const QString &filePath)
{
    QString strStyleSheet = "";
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        strStyleSheet = QLatin1String(file.readAll());
    }
    return strStyleSheet;
}

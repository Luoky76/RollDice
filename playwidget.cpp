#include "playwidget.h"
PlayWidget::PlayWidget(int playerCnt,QWidget *parent) : QWidget(parent)
{
    setFixedSize(1282,800);
    setWindowIcon(QIcon(":/resource/mooncakeIcon.png"));
    setWindowTitle("开始博饼吧！");

    backgroundInit();   //初始化背景元素
    prizeInit();    //初始化获奖等级
    addPlayer(playerCnt);   //添加玩家

    connect(btn_roll,&MyLabel::mouseEntered,[=](){  //鼠标进入时，中间骰子的动画开始
        rollTimer1->start(30);
    });
    connect(btn_roll,&MyLabel::mouseLeft,[=](){     //鼠标离开时，中间骰子的动画停止
        rollTimer1->stop();
    });
    connect(rollTimer1,&QTimer::timeout,[=](){   //中间骰子的动画
        static int currentIconPath = 1;
        ++currentIconPath;
        if (currentIconPath>6) currentIconPath = 1;
        btn_roll->setIcon(QString(":/resource/dice/%1.png").arg(currentIconPath));
    });
    connect(btn_roll,&MyLabel::click,[=]()  //点击按钮时，结束按钮动画，开始六个骰子的动画
    {
        if (currentPlayer>=players.count()) return;
        if (players[currentPlayer]->getPlayerMode()==PlayerWidget::artificial) return; //当前并非玩家
        startRoll();
    });
    connect(rollTimer2,&QTimer::timeout,this,&PlayWidget::handleRollTimer2);
    connect(aiTimer,&QTimer::timeout,this,&PlayWidget::artificialStart);    //人机时钟和人机操作连接

    gameStart();    //开始游戏
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
        QString messageText = prizeGrade[calcPrizeGrade()];

        if (players[currentPlayer]->getPlayerMode() == PlayerWidget::person) //非人机玩家弹窗显示获奖
        {
            QString messageTitle = "中奖情况";
            QMessageBox::information(this,messageTitle,"     "+messageText+"          ",QMessageBox::Ok);
        }

        QListWidgetItem *item = new QListWidgetItem(QString(players[currentPlayer]->getPlayerName())+QString(" 获得了")+messageText);   //点击ok后将获奖记录添加进表格
        addRankItem(item);
        nextPlayer();   //下一名玩家
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

void PlayWidget::closeEvent(QCloseEvent *)
{
    gameOver();
    emit windowClose();
}

void PlayWidget::startRoll()
{
    if (btn_roll_locked) return;    //按钮处于锁定状态
    btn_roll_locked = true; //锁定按钮
    rollTimer1->stop();
    rollTimer2->start(30);
}

void PlayWidget::nextPlayer()
{
    players[currentPlayer]->animationStop();    //关闭选中动画
    currentPlayer = (currentPlayer+1)%players.count();
    players[currentPlayer]->animationStart();   //开始下一个玩家的动画
    btn_roll_locked = false;    //解锁按钮
}

void PlayWidget::backgroundInit()
{
    QPixmap pixmap; //背景图片
    pixmap.load(":/resource/background/background.png");
    pixmap = pixmap.scaled(width(),height());
    background = new QLabel(this);
    background->setGeometry(0,0,width(),height());
    background->setPixmap(pixmap);
    background->move(0,0);

    btn_roll = new MyLabel(":/resource/dice/1.png",this);   //掷骰子按钮
    btn_roll->move((width()-btn_roll->width())*0.9,(height()-btn_roll->height())*0.5);

    rollTimer1 = new QTimer(this);
    rollTimer2 = new QTimer(this);
    aiTimer = new QTimer(this);

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
    prizeRecord->setFixedSize(200,500);
    prizeRecord->move(50,(height()-prizeRecord->height())*0.5);
    QString strStyle = ReadQssFile(":/resource/Style Sheet/whiteListWidget.qss");
    prizeRecord->setStyleSheet(strStyle);   //设置样式

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

void PlayWidget::addRankItem(QListWidgetItem *item)
{
    prizeRecord->addItem(item);
    item->setSizeHint(QSize(150,60));   //设置item大小
    QFont font("微软雅黑");
    font.setPixelSize(15);
    item->setFont(font);    //设置字体
    if (prizeRecord->count()>8) //当列表内元素超过8时，删除最旧的一项
    {
        QListWidgetItem *oldItem = prizeRecord->takeItem(0);
        delete oldItem;
    }
}

void PlayWidget::addPlayer(int playerCnt)
{
    for (int i=0;i<players.count();++i) delete players[i];  //添加玩家时先清除原有玩家
    players.clear();

    for (int i=1;i<=playerCnt;++i)
    {
        int randomPlayerPixmap = QRandomGenerator::global()->bounded(1,7);
        players.append(new PlayerWidget(QString(":/resource/player/%1.png").arg(randomPlayerPixmap),this));
    }

    setPlayerPos(); //初始化玩家位置
    showPlayer();   //显示玩家
}

void PlayWidget::showPlayer()
{
    for (int i=0;i<players.count();++i)
    {
        players[i]->show();
        players[i]->raise();
    }
}

void PlayWidget::setPlayerPos()
{
    if (players.count()>=1)
    {
        players[0]->move(this->width()*0.2,30);
    }
    if (players.count()>=2)
    {
        players[1]->move(this->width()*0.35,0);
    }
    if (players.count()>=3)
    {
        players[2]->move(this->width()*0.5,0);
    }
    if (players.count()>=4)
    {
        players[3]->move(this->width()*0.65,30);
    }
    if (players.count()>=5)
    {
        players[4]->move(this->width()*0.65,this->height()-players[4]->height()-30);
    }
    if (players.count()>=6)
    {
        players[5]->move(this->width()*0.5,this->height()-players[5]->height());
    }
    if (players.count()>=7)
    {
        players[6]->move(this->width()*0.35,this->height()-players[6]->height());
    }
    if (players.count()>=8)
    {
        players[7]->move(this->width()*0.2,this->height()-players[7]->height()-30);
    }
}

void PlayWidget::setPlayerName(int idx, QString name)
{
    if (players.count()-1<idx)
    {
        qDebug()<<"不存在这位玩家";
        return;
    }
    players[idx]->setPlayerName(name);
    players[idx]->setPlayerMode(PlayerWidget::person);
}

void PlayWidget::gameStart()
{
    //每过一段时间，人机发起响应
    aiTimer->start(1000);
    players[currentPlayer]->animationStart();
    btn_roll_locked = false;    //解锁按钮
}

void PlayWidget::gameOver()
{
    aiTimer->stop();
    for (auto i:players) i->animationStop();
    btn_roll_locked = true; //锁定按钮
}

QString PlayWidget::ReadQssFile(const QString &filePath)    //用于读取样式文件
{
    QString strStyleSheet = "";
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        strStyleSheet = QLatin1String(file.readAll());
    }
    file.close();
    return strStyleSheet;
}

void PlayWidget::artificialStart()
{
    if (currentPlayer>=players.count()) return;
    if (players[currentPlayer]->getPlayerMode()==PlayerWidget::artificial)
    {
        startRoll(); //当为人机时自动摇骰子
    }
}

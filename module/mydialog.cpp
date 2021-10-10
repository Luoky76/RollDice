#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);

    //设置定时关闭对话框
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        this->countDown = this->countDown-1;
        QString countDownText;
        countDownText = btnText+QString("（")+QString::number(countDown)+QString("）");
        ui->btn_yes->setText(countDownText);
        if (countDown<=0)
        {
            timer->stop();
            this->close();
        }
    });

    //美化文本
    QFont ft;
    ft.setPointSize(20);
    QPalette label_pe;
    label_pe.setColor(QPalette::WindowText, Qt::red);
    ui->textLabel->setPalette(label_pe);
    ui->textLabel->setFont(ft);
    ui->textLabel->setAlignment(Qt::AlignCenter);   //设置文字居中
}

MyDialog::~MyDialog()
{
    delete ui;
    timer->stop();
    delete timer;
}

void MyDialog::setCountDown(int countDown)
{
    if (countDown<=0) return;
    this->countDown = countDown;
    timer->start(1000);
}

void MyDialog::setBtnText(QString btnText)
{
    this->btnText = btnText;
    ui->btn_yes->setText(btnText);
}

void MyDialog::setText(QString text)
{
    this->text = text;
    ui->textLabel->setText(text);
}

void MyDialog::setPixmapPath(QString pixmapPath)
{
    this->pixmapPath = pixmapPath;
    QPixmap pixmap(pixmapPath);
    pixmap = pixmap.scaled(ui->pixmapLabel->width(),ui->pixmapLabel->height());
    ui->pixmapLabel->setPixmap(pixmap);
}

void MyDialog::setIconPath(QString iconPath)
{
    this->iconPath = iconPath;
    QPixmap pixmap(iconPath);
    this->setWindowIcon(pixmap);
}

void MyDialog::setBackgroundPixmap(QString backgroundPixmap)
{
    this->backgroundPixmap = backgroundPixmap;
}

void MyDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (!backgroundPixmap.isEmpty())    //若有背景图片，则绘制背景图片
    {
        QPixmap pixmap(backgroundPixmap);
        pixmap = pixmap.scaled(this->width(),this->height());
        painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
    }
}

void MyDialog::closeEvent(QCloseEvent *)
{
    emit dialogClosed();
}

void MyDialog::on_btn_yes_clicked()
{
    emit selectYes();
}

#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QPalette>
#include <QFont>

namespace Ui {
class MyDialog;
}

class MyDialog : public QWidget
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();
    void setCountDown(int countDown);
    void setBtnText(QString btnText);
    void setText(QString text);
    void setPixmapPath(QString pixmapPath);
    void setIconPath(QString iconPath);
    void setBackgroundPixmap(QString backgroundPixmap);

protected:
    Ui::MyDialog *ui;
    int countDown = -1; //关闭倒计时
    QString btnText; //按钮上的文字
    QString text;   //对话框内的文字
    QString pixmapPath; //对话框内的图片
    QString iconPath;   //对话框的图标
    QString backgroundPixmap = "";   //对话框的背景图片
    QTimer* timer;  //计时器
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

signals:
    void selectYes();   //选择确定后发出该信号
    void dialogClosed();    //窗口关闭时发出该信号

private slots:
    void on_btn_yes_clicked();
};

#endif // MYDIALOG_H

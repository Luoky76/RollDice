#include "prizedialog.h"

PrizeDialog::PrizeDialog(QString text, QWidget *parent):MyDialog(parent)
{
    this->setBtnText("确定");
    this->setText(text);
    this->setPixmapPath(":/resource/messageicon.png");
    this->setIconPath(":/resource/mooncakeIcon.png");
    this->setBackgroundPixmap(":/resource/background/background.png");
    this->setCountDown(3);

    connect(this,&PrizeDialog::selectYes,this,&PrizeDialog::close);
}

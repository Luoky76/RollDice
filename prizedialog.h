#ifndef PRIZEDIALOG_H
#define PRIZEDIALOG_H

#include "module/mydialog.h"

class PrizeDialog : public MyDialog
{
    Q_OBJECT
public:
    PrizeDialog(QString text,QWidget* parent = nullptr);
};

#endif // PRIZEDIALOG_H

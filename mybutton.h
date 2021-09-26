#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QString normalImg,QString pressImg = "",QWidget *parent = nullptr);

private:
    QString normalImgPath;
    QString pressImgPath;
    void zoomDown(int dy = 10);
    void zoomUp(int dy = 10);
    void zoom();
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void enterEvent(QEnterEvent *ev) override;
    void leaveEvent(QEvent *ev) override;

signals:
    void mouseEntered();
    void mouseLeft();
};

#endif // MYBUTTON_H

#ifndef NAMEBOX_H
#define NAMEBOX_H

#include <QObject>
#include <QString>
#include <QStringDecoder>
#include <QFile>
#include <QList>
#include <QDebug>

/******************************************
该类为一个名字池，依赖于文件playerName.in
该类通过随机排序和循环返回名字，一定程度上防止了返回
重复的名字。
getInstance() 可以获取该类的唯一实例
getRandomName() 可以随机获取一个名字池中的玩家名
******************************************/
class NameBox : public QObject
{
    Q_OBJECT
public:
    static NameBox* getInstance();
    QString getRandomName();

private:
    explicit NameBox(QObject *parent = nullptr);
    static NameBox* instance;  //单例模式
    QList <QString> nameBox;  //玩家名池，用于随机生成玩家名
    void initNameBox(); //初始化玩家名池

signals:

};

#endif // NAMEBOX_H

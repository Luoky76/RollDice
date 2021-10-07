#include "namebox.h"

NameBox* NameBox::instance = nullptr;
NameBox::NameBox(QObject *parent) : QObject(parent)
{
    initNameBox();  //初始化名字池
}

NameBox *NameBox::getInstance()
{
    if (instance==nullptr) instance = new NameBox();
    return instance;
}

QString NameBox::getRandomName()
{
    if (nameBox.empty())
    {
        qDebug()<<"名字池中无内容";
        return QString("");
    }
    QString name = nameBox.front(); //取出名字池的首个元素，并将其置于队尾
    nameBox.pop_front();
    nameBox.push_back(name);

    return name;
}

void NameBox::initNameBox()
{
    QFile nameFile(":/resource/player/playerName.in");
    nameFile.open(QIODevice::ReadOnly); //以只读方式打开文件
    while (!nameFile.atEnd())
    {
        QByteArray byteContent = nameFile.readLine();
        auto toUtf8 = QStringDecoder(QStringDecoder::Utf8); //utf8解码工具
        QString singlePlayerName = toUtf8(byteContent);
        singlePlayerName = singlePlayerName.simplified();   //简化字符串
        nameBox.append(singlePlayerName);
    }
    nameFile.close();

    std::random_shuffle(nameBox.begin(),nameBox.end()); //对名字池随机排序
}

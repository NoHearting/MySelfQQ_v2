#include "EmojiHotWidget.h"
#include "ui_EmojiHotWidget.h"
#include "utils/Util.h"
#include "main/ReadQStyleSheet.h"
#include "main/StringUserData.h"

#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <QList>

QVector<QPair<QString, uint>> EmojiHotWidget::hotEmojiTimesVec;
QSet<QString> EmojiHotWidget::hotEmojiSet;

EmojiHotWidget::EmojiHotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmojiHotWidget)
{
    ui->setupUi(this);
    initResourceAndForm();
    initSignalsAndSlots();
    readFromFile();
}

EmojiHotWidget::~EmojiHotWidget()
{
    qInfo() << "deconstruct EmojiHotWidget";
    writeToFile();
    delete ui;

}

QVector<QString> EmojiHotWidget::topTotEmoji(int count)
{
    std::sort(hotEmojiTimesVec.begin(), hotEmojiTimesVec.end(), Compare());
    QVector<QString> result;
    for(int i = 0; i < hotEmojiSet.size() && i < count; i++)
    {
        result.push_back(hotEmojiTimesVec.at(i).first);
    }
    return result;
}

void EmojiHotWidget::recordHotEmoji(const QString &emoji)
{
    if(hotEmojiSet.contains(emoji))
    {
        for(auto &item : hotEmojiTimesVec)
        {
            if(item.first == emoji)
            {
                item.second++;
                return;
            }
        }
    }
    else
    {
        hotEmojiSet.insert(emoji);
        hotEmojiTimesVec.push_back(PAIR(emoji, 1));
    }
}

void EmojiHotWidget::adjustPosition(const QPoint &basePos)
{
    const int padding = 10;
    QPoint pos = basePos - QPoint(padding, this->height());
    const int toolBatHeight = 40;

    QSize windowSize = zsj::SystemUtil::getDesktopSize();

    // 顶部
    if(pos.y() < 0)
    {
        pos = basePos + QPoint(-padding, toolBatHeight);
    }
    if(pos.x() + this->width() > windowSize.width())
    {
        pos -= QPoint(pos.x() + this->width() - windowSize.width(), 0);
    }
    this->setGeometry(QRect(pos, this->size()));
}

void EmojiHotWidget::showEvent(QShowEvent *event)
{
    ui->tableWidget->showEmoji(topTotEmoji());

    QWidget::showEvent(event);
}

void EmojiHotWidget::initResourceAndForm()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    zsj::WidgetUtil::setWidgetBoxShadow(ui->widget);

    this->setStyleSheet(zsj::ReadQStyleSheet::readQss("://css/emoji.css"));
}

void EmojiHotWidget::initSignalsAndSlots()
{
    connect(ui->tableWidget, &EmojiTableWidget::cellClicked, this, [this](int row, int col)
    {
        QLabel *label = dynamic_cast<QLabel *>(ui->tableWidget->cellWidget(row, col));
        StringUserData *stringData = dynamic_cast<StringUserData *>(
                                         label->userData(row * EmojiTableWidget::EmojiHotColCount + col));
        if(stringData)
        {
            QString path = stringData->getData();
            emit sigChooseEmoji(type, path);
        }
        else
        {
            qCritical() << "choose emoji failed!";
        }
    });
}

void EmojiHotWidget::writeToFile()
{
    QString hotEmojiPath = "/data/hot_emoji/";
    QString absolutPath = zsj::SystemUtil::getProcessPath() + hotEmojiPath;
    qDebug() << absolutPath;
    bool isOk = zsj::FileUtil::judgeAndMakeDir(absolutPath);
    absolutPath += "hot_emoji.txt";
    if(isOk)
    {
        QFile file(absolutPath);
        if(file.open(QIODevice::WriteOnly))
        {

            for(const auto &item : hotEmojiTimesVec)
            {
                file.write(QString("%1 %2\n").arg(item.first).arg(item.second).toStdString().data());
            }
            qDebug() << "write to file ok";
        }
        else
        {
            qCritical() << file.errorString();
        }
    }
    else
    {
        qCritical() << absolutPath << " create failed or not exist";
    }
}

void EmojiHotWidget::readFromFile()
{

    QString hotEmojiPath = "/data/hot_emoji/";
    QString absolutPath = zsj::SystemUtil::getProcessPath() + hotEmojiPath;
    bool isOk = zsj::FileUtil::judgeAndMakeDir(absolutPath);
    absolutPath += "hot_emoji.txt";
    if(isOk)
    {
        QFile file(absolutPath);
        if(file.open(QIODevice::ReadOnly))
        {

            while(!file.atEnd())
            {
                QList<QByteArray> data = file.readLine().split(' ');
                QString path = QString(data.at(0).toStdString().data());
                int times = data.at(1).toInt();
                hotEmojiTimesVec.push_back(PAIR(path, times));
                hotEmojiSet.insert(path);
            }
            qDebug() << "read from file ok";
        }
        else
        {
            qCritical() << file.errorString();
        }
    }
    else
    {
        qCritical() << absolutPath << " create failed or not exist";
    }
    qInfo() << "read from file ok";
}

void EmojiHotWidget::show(zsj::global::UiType type)
{
    this->type = type;
    QWidget::show();
}

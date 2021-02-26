#include "EmojiTableWidget.h"

#include <QFileInfo>
#include <QDirIterator>
#include <QFile>
#include <QDebug>
#include <QHeaderView>
#include <QScrollBar>

#include "main/StringUserData.h"

EmojiTableWidget::EmojiTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    initTableWidget();
}

EmojiInfo EmojiTableWidget::loadEmoji(EmojiType type)
{
    QString prefix;
    switch(type)
    {
        case EmojiType::NORMAL:
            prefix = "normal";
            break;
        case EmojiType::SYMBOL:
            prefix = "symbol";
            break;
    }
    auto emojiVector = readAllEmoji(prefix);
    return EmojiInfo(type, prefix, emojiVector);
}

void EmojiTableWidget::showEmoji(EmojiType type)
{
    EmojiInfo emojiInfo = loadEmoji(type);
    qDebug() << emojiInfo.toString();

    int emojiRowCount = emojiInfo.getEmojiCount() / EmojiColCount;
    if(emojiInfo.getEmojiCount() % EmojiColCount)
    {
        emojiRowCount++;
    }
    this->setColumnCount(EmojiColCount);
    this->setRowCount(emojiRowCount);

    // 添加表情
    int rowIndex = 0, colIndex = 0;
    const auto & emojiVec = emojiInfo.getEmojiVector();
    for(int i = 0; i < emojiVec.size(); i++)
    {
        rowIndex = i / EmojiColCount;
        colIndex = i % EmojiColCount;
        QLabel *emojiLabel = packageEmojiLabel(emojiVec.at(i));
        if(emojiLabel)
        {
            this->setCellWidget(rowIndex, colIndex, emojiLabel);
            this->setColumnWidth(colIndex,38);
            this->setRowHeight(rowIndex,38);
            emojiLabel->setUserData(rowIndex * EmojiColCount + colIndex,new StringUserData(emojiVec.at(i)));
        }
    }
}

void EmojiTableWidget::showEmoji(const QVector<QString> &hotEmoji)
{
    const int emojiCount = hotEmoji.size();
    const int hotEmojiColCount = 5;
    int emojiRowCount = emojiCount / hotEmojiColCount;
    if(emojiCount % hotEmojiColCount){
        emojiRowCount++;
    }

    this->setColumnCount(hotEmojiColCount);
    this->setRowCount(emojiRowCount);
    // 添加表情
    int rowIndex = 0, colIndex = 0;
    const auto & emojiVec = hotEmoji;
    for(int i = 0; i < emojiVec.size(); i++)
    {
        rowIndex = i / hotEmojiColCount;
        colIndex = i % hotEmojiColCount;
        QLabel *emojiLabel = packageEmojiLabel(emojiVec.at(i));
        if(emojiLabel)
        {
            this->setCellWidget(rowIndex, colIndex, emojiLabel);
            this->setColumnWidth(colIndex,38);
            this->setRowHeight(rowIndex,38);
            emojiLabel->setUserData(rowIndex * hotEmojiColCount + colIndex,new StringUserData(emojiVec.at(i)));
        }
    }
}

void EmojiTableWidget::initTableWidget()
{
    verticalHeader()->setVisible(false);   // 垂直表头不显示
    horizontalHeader()->setVisible(false); // 水平表头不显示

    // 设置重新设置大小时的策略
//    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setShowGrid(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);  // 不可编辑
    setSelectionMode(QAbstractItemView::SingleSelection); // 设置只能单选

    // 禁用水平滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}

QVector<QString> EmojiTableWidget::readAllEmoji(QString pathPrefix)
{
    QVector<QString> resultEmojiList;
    QDirIterator it(":/" + pathPrefix, QDirIterator::Subdirectories);

    while (it.hasNext())
    {
        QString name = it.next();
        QFileInfo fileInfo = it.fileInfo();
        if (fileInfo.isFile()) // Do not add directories to the list
        {
            resultEmojiList.push_back(name);
        }
    }
    return resultEmojiList;
}

QLabel *EmojiTableWidget::packageEmojiLabel(const QString &emojiPath)
{
    QLabel *label = new QLabel(this);
    QPixmap origin(emojiPath);
    if(!origin.isNull())
    {
        QPixmap newPix = origin.scaled(EmojiSize + 4, EmojiSize + 4, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        label->setPixmap(newPix);
        label->setAlignment(Qt::AlignCenter);
        return label;
    }
    else
    {
        qCritical() << "Emoji " << emojiPath << " is not exist!";
        return nullptr;
    }
}

#ifndef EMOJITABLEWIDGET_H
#define EMOJITABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QVector>
#include <QString>
#include <QLabel>

#include "main/EmojiInfo.h"

class EmojiTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    /// 表情容器每一行允许的最大表情数
    const static int EmojiColCount = 12;

    /// 每一个表情的大小 24 x 24
    const static int EmojiSize = 24;

public:
    explicit EmojiTableWidget(QWidget *parent = nullptr);


    /**
     * @brief 加载表情
     * @param type 加载的表情类型
     * @return EmojiInfo 获取的表情信息
     */
    EmojiInfo loadEmoji(EmojiType type);

    /**
     * @brief 显示表情
     * @param type 加载的表情类型
     */
    void showEmoji(EmojiType type);

private:
    /**
     * @brief 初始化表情容器
     */
    void initTableWidget();

    /**
     * @brief  读取所有表情文件的路径
     * @param pathPrefix 表情分类前缀
     * @return  表情路径列表
     */
    QVector<QString> readAllEmoji(QString pathPrefix);

    /**
     * @brief 将表情封装到label中
     * @param emojiPath 表情的路径
     * @return QLabel
     */
    QLabel * packageEmojiLabel(const QString & emojiPath);
signals:

public slots:
};

#endif // EMOJITABLEWIDGET_H

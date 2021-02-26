#ifndef EMOJIHOTWIDGET_H
#define EMOJIHOTWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPair>
#include <QString>
#include <QSet>

#include "utils/Global.h"

namespace Ui {
class EmojiHotWidget;
}

class EmojiHotWidget : public QWidget
{
    Q_OBJECT
public:
    typedef QPair<QString,uint> PAIR;
private:
    struct Compare
    {
        Compare() {}
        bool operator ()(const PAIR & lhs,const PAIR & rhs){
            return lhs.second > rhs.second;
        }
    };

public:
    /// 记录常用表情使用的次数
    static QVector<QPair<QString,uint>> hotEmojiTimesVec;
    /// 记录了使用了那些表情
    static QSet<QString> hotEmojiSet;

public:
    explicit EmojiHotWidget(QWidget *parent = nullptr);
    ~EmojiHotWidget();

    /**
     * @brief 最常用的几个表情
     * @param count 最常用的个数
     * @return 常用表情列表
     */
    QVector<QString> topTotEmoji(int count = 15);


    /**
     * @brief 记录表情的使用次数
     * @param emoji 被记录的表情
     */
    void recordHotEmoji(const QString & emoji);

    void adjustPosition(const QPoint & basePos);


    /**
     * @brief 将使用最多的表情持久化
     */
    void writeToFile();

    /**
     * @brief 将使用最多的表情数据读出来
     */
    void readFromFile();

    /**
     * @brief 显示窗口
     * @param type 当前使用此窗口的ui的类型
     * @note 当前窗口被两套不同的ui共享使用
     */
    void show(zsj::global::UiType type);

protected:
    void showEvent(QShowEvent *event);

private:
    void initResourceAndForm();
    void initSignalsAndSlots();


private:
    Ui::EmojiHotWidget *ui;

    /// 当前窗口被用户和群组ui共享，type标识当前是哪一个ui在使用
    zsj::global::UiType type;

signals:
    /**
     * @brief 当点击表情时触发此信号
     * @param type 使用此窗口的ui类型
     * @param emojiPath 表情的路径
     */
    void sigChooseEmoji(zsj::global::UiType type,const QString & emojiPath);
};

#endif // EMOJIHOTWIDGET_H

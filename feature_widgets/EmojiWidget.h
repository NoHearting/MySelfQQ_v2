/**
  * @file EmojiWidget
  * @brief MQ表情容器
  * @date 2021年2月21日18:09:58
  * @author zsj
  */
#ifndef EMOJIWIDGET_H
#define EMOJIWIDGET_H

#include <QWidget>
#include <QPoint>

namespace Ui {
class EmojiWidget;
}

class EmojiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmojiWidget(QWidget *parent = nullptr);
    ~EmojiWidget();

    /**
     * @brief 设置表情窗口显示的位置
     * @param basePos 基本位置
     */
    void adjustPosition(const QPoint & basePos);

private:
    /**
     * @brief 初始化资源和ui
     */
    void initResourceAndForm();

    /**
     * @brief 初始化信号和槽
     */
    void initSignalsAndSlots();

    /**
     * @brief 初始化表情
     */
    void initEmoji();

private:
    Ui::EmojiWidget *ui;

signals:
    /**
     * @brief 当点击表情时触发此信号
     * @param emojiPath 表情的路径
     */
    void sigChooseEmoji(const QString & emojiPath);
};

#endif // EMOJIWIDGET_H

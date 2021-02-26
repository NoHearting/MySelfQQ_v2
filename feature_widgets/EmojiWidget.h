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
#include "utils/Global.h"


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

    /**
     * @brief 显示窗口
     * @param type 当前使用此窗口的ui的类型
     * @note 当前窗口被两套不同的ui共享使用
     */
    void show(zsj::global::UiType type);
protected:
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);

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

    /// 当前窗口被用户和群组ui共享，type标识当前是哪一个ui在使用
    zsj::global::UiType type;

signals:
    /**
     * @brief 当点击表情时触发此信号
     * @param type 使用此窗口的ui类型
     * @param emojiPath 表情的路径
     */
    void sigChooseEmoji(zsj::global::UiType type,const QString & emojiPath);

    /**
     * @brief 窗口关闭或隐藏时发送
     */
    void sigWindowClose();
};

#endif // EMOJIWIDGET_H

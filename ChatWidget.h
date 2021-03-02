#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include <QListWidget>

#include <QRect>
#include <QStringList>

#include "main/Frameless.h"
#include "main/Data.h"
#include "feature_widgets/EmojiWidget.h"
#include "feature_widgets/EmojiHotWidget.h"

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    enum class InputMessageType{
        PLAIN_TEXT = 0, // 只含文本
        IMAGE,          // 只含文件
        EMOJI_TEXT      // 包含表情和文本
    };
public:
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();


    /// @brief 全屏显示窗口
    void showMaximizedWindow();

    /// @brief 显示普通大小窗口
    void showNormalWindow();

protected:

    /// @brief 重写窗口大小改变事件
    void resizeEvent(QResizeEvent *event);


    bool event(QEvent *event);

private:


    /**
     * @brief 消息解析器
     */
    class MessageParser{
    public:
        /**
         * @brief 解析消息
         * @param originmessage 原生消息
         * @return
         */
        QMap<InputMessageType,QStringList> parserMessage(QString originmessage);


        /**
         * @brief 判定当前消息内容是否为空
         * @param content 内容
         * @return
         */
        bool contentJudgeEmpty(const QString & content);
    };

private:

    /// @brief 初始化成员堆对象
    void initObjects();

    /// @brief 初始化窗口资源和窗口布局
    void initResourceAndForm();

    /// @brief 初始化信号和槽
    void initSignalsAndSlots();


    /// @brief 设置聊天对象列表样式
    /// 如果没有一个元素，则隐藏
    void setChatObjListStyle();


    /// @brief 初始化所有菜单
    void initMenus();

    /// @brief 测试阶段
    void initTestData();

    /// @brief 初始化左边的聊天对象列表
    void initTestChatObjs();

    /// @brief 初始化消息列表
    void initTestMessageList();

private:

    /// @brief 设置当前聊天对象
    /// @param[in] data 设置数据
    void setCurrentData(zsj::Data::ptr data);

    /// @brief 添加消息item
    /// @param[in] listWidget 需要添加item的QListWidget
    /// @param[in] head 头像
    /// @param[in] message 聊天消息
    /// @note 废弃，参数过少，使用下面一个。后续删除
    void addMessageItem(QListWidget * listWidget,QPixmap & head,const QString & message,bool isSelf = true);


    /**
     * @brief 添加信息item
     * @param listWidget 需要添加item的QListWidget
     * @param head 头像
     * @param inputType 聊天信息的分类
     * @param message 聊天消息
     * @param isSelf 是否是自己所发信息
     */
    void addMessageItem(QListWidget * listWidget,QPixmap & head,InputMessageType inputType,
                        const QString & message,bool isSelf = true);


    /// @brief 切换聊天对象
    void switchChatObj();


    /// @brief 改变消息输入框的大小
    void changeMessageInput();

private:
    Ui::ChatWidget *ui;

    /// 设置窗口可拉伸和移动
    zsj::Frameless *frameless = nullptr;

    /// 当前聊天对象数据
    zsj::Data::ptr currentData = nullptr;

    /// 当前选择聊天对象的item
    QListWidgetItem * currentItem = nullptr;


    /// 消息发送菜单
    QMenu * sendMenu = nullptr;


    /// 当前窗口的位置大小
    QRect windowGeometry;

    /// 表情窗口
    EmojiWidget * emojiWidget = nullptr;

    /// 常用表情窗口
    EmojiHotWidget * emojiHotWidget = nullptr;


    /// 解析需要发送的消息
    MessageParser parser;

public slots:

    /// @brief 选择Enter发送消息
    void slotChooseEnter();

    /// @brief 选择Ctrl+Enter发送消息
    void slotChooseCtrlEnter();

private slots:

    /// @brief 最大化窗口，如果已经最大化则恢复之前的状态
    void slotShowMaxWindow();


    /// @brief 改变聊天对象
    void slotChangeChatObject(QListWidgetItem *item);

    /// @brief 删除聊天对象
    void slotDeleteChatObject(QPoint point);

    /// @brief 添加item时触发
    void slotItemAdd(QListWidgetItem * item);

    /// @brief 点击按钮发送消息
    void slotButtonToSendMessage();
    void slotButtonToSendMessageGroup();

    /// @brief 按键发送消息
    /// @param QString 发送的消息
    void slotKeyToSendMessage(const QString & msg);
    void slotKeyToSendMessageGroup(const QString &msg);

    /// @brief 最大化聊天框
    void slotMaxShowMessageList();
    void slotMaxShowMessageListGroup();

    /**
     * @brief 选择表情
     * @param emojiPath 表情路径
     */
    void slotChooseEmoji(zsj::global::UiType type, const QString & emojiPath);

    /**
     * @brief 截屏
     */
    void slotScreenShot();



    /**
     * @brief 显示表情窗口
     */
    void slotShowEmojiWidget();

    /**
     * @brief 选择图片文件
     */
    void slotChooseImageFile();
    void slotChooseImageFileGroup();

};

#endif // CHATWIDGET_H

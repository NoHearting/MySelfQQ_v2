#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include <QListWidget>

#include "Frameless.h"
#include "Data.h"

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();

protected:

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


    void setCurrentData(zsj::Data::ptr data);


private:
    Ui::ChatWidget *ui;

    /// 设置窗口可拉伸和移动
    zsj::Frameless *frameless = nullptr;

    /// 当前聊天对象数据
    zsj::Data::ptr currentData = nullptr;

    /// 当前选中聊天对象的坐标
    QModelIndex currentIndex;


    /// 消息发送菜单
    QMenu * sendMenu = nullptr;

public slots:

    /// @brief 选择Enter发送消息
    void slotChooseEnter();

    /// @brief 选择Ctrl+Enter发送消息
    void slotChooseCtrlEnter();

private slots:
    /// @brief 改变聊天对象
    void changeChatObject(const QModelIndex &index);

    /// @brief 删除聊天对象
    void slotDeleteChatObject(QPoint point);

    /// @brief 添加item时触发
    void slotItemAdd(QListWidgetItem * item);

    /// @brief 移除item时触发
    void slotItemTake();




};

#endif // CHATWIDGET_H

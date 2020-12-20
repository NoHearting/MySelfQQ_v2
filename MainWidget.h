#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTreeWidget>


#include "Frameless.h"
#include "SystemTray.h"
#include "Linkman.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    /// @brief 初始化窗口资源和窗口布局
    void initResourceAndForm();

    /// @brief 初始化信号和槽
    void initSignalsAndSlots();

    /// @brief 初始化成员堆对象
    void initObjects();


    /// @brief 初始化联系人好友列表
    void initManlinkFriend();

    /// @brief 初始化联系人群聊列表
    void initManlinkGroup();

    /// @brief 初始化消息列表
    void initMessageList();

private:
    /// @brief 添加好友列表的根节点
    ///
    /// @param treeWidget 好友列表
    /// @param group 根节点
    QTreeWidgetItem* addTreeWidgetRootNode(QTreeWidget * treeWidget,LinkmanGroupWidget * group);
    QTreeWidgetItem* addTreeWidgetRootNode(QTreeWidget * treeWidget,const QString & groupName,int active,int total);

    /// @brief 添加好友列表的子节点
    ///
    /// @param[in] 好友列表
    /// @param[in] 根节点
    /// @param[in] 子节点
    QTreeWidgetItem* addTreeWidgetChildNode(QTreeWidget * treeWidget,QTreeWidgetItem * rootNode,LinkmanItemWidget * item);
    QTreeWidgetItem* addTreeWidgetChildNode(QTreeWidget * treeWidget,QTreeWidgetItem * rootNode,
                                const QPixmap & head,const QString & nickname,const QString & remark,
                                const QString & signature);
    QTreeWidgetItem* addTreeWidgetChildNode(QTreeWidget * treeWidget,QTreeWidgetItem * rootNode,
                                const QPixmap & head,const QString & nickname,const QString & date);


    /// 设置头像
    void setHead(QPixmap & pixmap);
    void setHead(const QString & pixmapPath);

private:
    Ui::MainWidget *ui;


    /// 设置窗口可拉伸和移动
    Zsj::Frameless * frameless;

    /// 系统托盘
    Zsj::SystemTray * systemTray;

private slots:

    // ------- 最顶部功能按钮 ---------
    /// @brief 关闭窗口
    void closeWindow();

    /// @brief 最小化窗口
    void minWindow();

    /// @brief 界面管理器
    void interfaceManager();


    /// @brief 切换到消息界面
    void switchToMessageWidget();

    /// @brief 切换到联系人界面
    void switchToLinkmanWidget();

    /// @brief 切换到空间界面
    void switchToSpaceWidget();

    /// @brief 子项目点击，
    /// 如果为根节点则不变化背景颜色,并且展开内容
    void treeWidgetItemClick(QTreeWidgetItem * item, int column);

    /// @brief 子项目收缩时
    void collasped(QTreeWidgetItem * item);

    /// @brief 子项目展开时
    void expanded(QTreeWidgetItem * item);


};

#endif // MAINWIDGET_H

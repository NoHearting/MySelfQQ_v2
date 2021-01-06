#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

#include "Frameless.h"

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
#ifdef Q_OS_LINUX
    /// @brief 重写mouseMoveEvent函数
    ///
    ///     用户点击有可能点击登录页面之上的小部件然后拖动
    ///会出现抖动，此函数解决此问题
    void mouseMoveEvent(QMouseEvent *);

    /// @brief 重写mousePressEvent函数
    ///
    ///  鼠标按下事件，按下就获取当前鼠标坐标并计算出当前坐标和窗口左上角的差值
    void mousePressEvent(QMouseEvent *);

    /// @brief 重写mouseReleaseEvent函数
    void mouseReleaseEvent(QMouseEvent *);
#endif

private:

    /// @brief 初始化成员堆对象
    void initObjects();

    /// @brief 初始化窗口资源和窗口布局
    void initResourceAndForm();

    /// @brief 初始化信号和槽
    void initSignalsAndSlots();



private:
    Ui::ChatWidget *ui;

#ifdef Q_OS_LINUX
    QPoint offset;      /// 鼠标位移值
#endif

    /// 设置窗口可拉伸和移动
    zsj::Frameless *frameless = nullptr;
};

#endif // CHATWIDGET_H

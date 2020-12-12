#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

protected:
    //无边框窗口需要重写鼠标点击和移动时间
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

private:
    /// @brief 初始化窗口资源和窗口布局
    void initResourceAndForm();

    /// @brief 初始化信号和槽
    void initSignalsAndSlots();

private:
    Ui::LoginWidget *ui;

    QPoint offset;       ///鼠标点击位置和窗口左上角的差值

private slots:
    void closeWindow();
};

#endif // LOGINWIDGET_H

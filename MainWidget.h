#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>


#include "Frameless.h"
#include "SystemTray.h"

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

private:
    Ui::MainWidget *ui;


    /// 设置窗口可拉伸和移动
    Zsj::Frameless * frameless;

    /// 系统托盘
    Zsj::SystemTray * systemTray;

private slots:
    /// @brief 关闭窗口
    void closeWindow();

    /// @brief 最小化窗口
    void minWindow();


};

#endif // MAINWIDGET_H

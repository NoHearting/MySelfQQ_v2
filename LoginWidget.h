#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();


private:
    /// @brief 初始化窗口资源和窗口布局
    void initResourceAndForm();

private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H

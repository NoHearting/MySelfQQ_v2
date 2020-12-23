/**
  * @brief 自定义提示框。
  *     主要用在登录页面提示用户账号密码为空的情况
  * @author zsj
  * @date 2020年12月23日20:29:16
  */
#ifndef TOOLTIPWIDGET_H
#define TOOLTIPWIDGET_H

#include <QWidget>

namespace Ui {
class ToolTipWidget;
}

class ToolTipWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolTipWidget(QWidget *parent = 0);
    ~ToolTipWidget();

    /// @brief 显示提示框
    /// @param[in] msg 显示消息
    /// @param[in] x x坐标
    /// @param[in] y y坐标
    /// @param[in] width 提示框宽度，默认135
    /// @param[in] height 提示框高度，默认30
    void showToolTip(const QString & msg,int x,int y,int width = 135,int height = 30);

    /// @brief 设置提示框样式表
    /// @param[in] css 样式
    void setToolTipCss(const QString & css);
private:
    Ui::ToolTipWidget *ui;
};

#endif // TOOLTIPWIDGET_H

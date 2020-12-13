#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <QWidget>

class MyComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit MyComboBox(QWidget *parent = 0);

    /// @brief 显示下拉框
    void showPopup();

    /// @brief 隐藏下拉框
    void hidePopup();
signals:
    /// @brief 设置输入框的CSS样式为命中样式
    void setLineEditCssOn();

    /// @brief 设置输入框的CSS样式为普通样式
    void setLineEditCssOff();
public slots:
};

#endif // MYCOMBOBOX_H

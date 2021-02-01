/**
  * @brief 自定义QListWidget
  *     主要是解决垂直滚动条占据一定的空间。所以使用封装的FloatScrollBar让滚动条悬浮
  * @author zsj
  * @date 2020年12月23日20:19:24
  */
#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include "feature_widgets/FloatScrollBar.h"

#include <QWidget>
#include <QListWidget>

class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QWidget *parent = 0);

    /// @brief 设置滚动条的样式表
    /// @param[in] qss 样式
    void setScrollBarQss(const QString & qss);

    void addItem(QListWidgetItem *item);

    QListWidgetItem * takeItem(int row);
protected:
    void resizeEvent(QResizeEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
signals:

    void sigAddItem(QListWidgetItem * item);

    void sigTakeItem();

    /// @brief 窗口触发resize事件时发送此信号
    void sigResizeEvent();

public slots:
    void valueChanged(int value);
private:
    /// 浮动滚动条
    FloatScrollBar * floatScrollBar;

    /// 垂直滚动条宽度
    int verticalScrollBarWidth;


};

#endif // MYLISTWIDGET_H

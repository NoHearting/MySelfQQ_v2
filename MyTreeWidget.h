/**
  * @brief 自定义QTreeWidget
  *     主要是解决垂直滚动条占据一定的空间。所以使用封装的FloatScrollBar让滚动条悬浮
  * @author zsj
  * @date 2020年12月23日20:22:27
  */
#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include "FloatScrollBar.h"

#include <QWidget>
#include <QTreeWidget>

class MyTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit MyTreeWidget(QWidget *parent = 0);

    /// @brief 设置滚动条的样式表
    /// @param[in] qss 样式
    void setScrollBarQss(const QString & qss);

protected:
    void resizeEvent(QResizeEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

signals:

public slots:
    void valueChanged(int value);
private:
    /// 浮动滚动条
    FloatScrollBar * floatScrollBar;

    /// 垂直滚动条宽度
    int verticalScrollBarWidth;
};

#endif // MYTREEWIDGET_H

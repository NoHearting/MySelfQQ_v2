/**
  * @brief 浮动滚动条,默认为垂直滚动条
  *
  * @author zsj
  * @date 2020年12月23日19:15:31
  */
#ifndef FLOATSCROLLBAR_H
#define FLOATSCROLLBAR_H

#include <QWidget>
#include <QScrollBar>

class FloatScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit FloatScrollBar(Qt::Orientation orientation = Qt::Vertical, QWidget *parent = 0);


    /// @brief 设置滚动条的样式
    ///
    /// @param[in] qss 样式字符串
    void setQss(const QString & qss);
signals:

public slots:
    void valueChangedFloat(int value);
    void rangeChangedFloat(int min,int max);
};

#endif // FLOATSCROLLBAR_H

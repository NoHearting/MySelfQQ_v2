#ifndef FLOATSCROLLBAR_H
#define FLOATSCROLLBAR_H

#include <QWidget>
#include <QScrollBar>

class FloatScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit FloatScrollBar(Qt::Orientation orientation = Qt::Vertical, QWidget *parent = 0);


    void setQss(const QString & qss);
signals:

public slots:
    void valueChangedFloat(int value);
    void rangeChangedFloat(int min,int max);
};

#endif // FLOATSCROLLBAR_H

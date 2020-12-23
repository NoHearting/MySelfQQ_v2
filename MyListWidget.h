#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include "FloatScrollBar.h"

#include <QWidget>
#include <QListWidget>

class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QWidget *parent = 0);


    void setScrollBarQss(const QString & qss);
protected:
    void resizeEvent(QResizeEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
signals:

public slots:
    void valueChanged(int value);
private:
    FloatScrollBar * floatScrollBar;
    int verticalScrollBarWidth;
};

#endif // MYLISTWIDGET_H

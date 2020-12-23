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

#endif // MYTREEWIDGET_H

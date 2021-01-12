#ifndef CACHEWIDGET_H
#define CACHEWIDGET_H

#include <QWidget>

#include <QPainter>
#include <QColor>
#include <QBrush>

#include "Global.h"

class CacheWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CacheWidget(QWidget *parent = nullptr);


public:
    void showWidget(QWidget * innerWidget);

    void setBorderWidth(int value);

    void setBorderColor(const QColor &value);

protected:
    void paintEvent(QPaintEvent *event);




private:
    int borderWidth = 8;
    QColor borderColor = QColor(Qt::black);

    QPainter * painter = nullptr;
    QBrush brush;

signals:

public slots:
};

#endif // CACHEWIDGET_H

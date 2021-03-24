/**
  * @brief 作为一块画布，辅助画出登录界面头像四周的阴影
  *
  * @author zsj
  * @date 2020年12月12日21:28:08
  */

#ifndef HEADSHADOWWIDGET_H
#define HEADSHADOWWIDGET_H

#include <QWidget>

class HeadShadowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HeadShadowWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // HEADSHADOWWIDGET_H

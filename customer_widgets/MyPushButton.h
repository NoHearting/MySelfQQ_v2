/**
  * @file MyPushButton.h
  * @brief 自定义QPushButton。多个按钮情况下，同时只能有一个按钮被选中（checked）
  * @date 2021年3月9日17:38:02
  * @author zsj
  */
#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QVector>

class MyPushButton : public QPushButton
{
    Q_OBJECT
private:
    static QVector<QPushButton*> buttons;
public:
    explicit MyPushButton(QWidget *parent = nullptr);


    void setChecked(bool check);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H

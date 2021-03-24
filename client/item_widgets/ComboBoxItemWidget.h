/**
  * @brief 组合框（QComboBox）的下拉框的子项
  *
  * @author zsj
  * @date 2020年12月23日18:59:01
  */
#ifndef COMBOBOXITEMWIDGET_H
#define COMBOBOXITEMWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QDebug>
#include <QTextStream>

#include "main/LoginInfo.h"

namespace Ui {
class ComboBoxItemWidget;
}

class ComboBoxItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComboBoxItemWidget(QWidget *parent = 0);
    ComboBoxItemWidget(const QPixmap & head,const QString & nickname,
                       quint64 accountNum,const QString & password,
                       QWidget *parent = 0);
    ComboBoxItemWidget(zsj::LoginInfo::ptr info,QWidget * parent = 0);
    ~ComboBoxItemWidget();


    QTextStream & operator <<(QTextStream & out);
    QDebug & operator <<(QDebug & debug);

    QString toString()const;

    QPixmap getHead() const;
    void setHead(const QPixmap &value);

    QString getNickname() const;
    void setNickname(const QString &value);


    QString getPassword() const;
    void setPassword(const QString &value);

    quint64 getAccountNum() const;
    void setAccountNum(const quint64 &value);

    zsj::LoginInfo::ptr getInfo() const;

protected:
    /// @brief 鼠标松开时发送点击信号
    void mouseReleaseEvent(QMouseEvent *);

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:
    /// @brief 当鼠标点击然后松开之后发送此信号
    void sigClick(zsj::LoginInfo::ptr info);

    /// 删除item时发送信号
    void sigDeleteItem(const QPoint & pos);
public slots:
    void slotDeleteItem();
private:
    /// @brief 初始化窗口资源和窗口布局
    void initResourceAndForm();
private:
    Ui::ComboBoxItemWidget *ui;

    zsj::LoginInfo::ptr info;

    QPixmap head;
    QString nickname;
    quint64 accountNum;
    QString password;
};

#endif // COMBOBOXITEMWIDGET_H

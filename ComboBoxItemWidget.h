#ifndef COMBOBOXITEMWIDGET_H
#define COMBOBOXITEMWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QDebug>
#include <QTextStream>

namespace Ui {
class ComboBoxItemWidget;
}

class ComboBoxItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComboBoxItemWidget(QWidget *parent = 0);
    ComboBoxItemWidget(const QPixmap & head,const QString & nickname,
                       const QString & accountNum,const QString & password,
                       QWidget *parent = 0);
    ~ComboBoxItemWidget();


    QTextStream & operator <<(QTextStream & out);
    QDebug & operator <<(QDebug & debug);

    QString toString()const;

    QPixmap getHead() const;
    void setHead(const QPixmap &value);

    QString getNickname() const;
    void setNickname(const QString &value);

    QString getAccountNum() const;
    void setAccountNum(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

protected:
    void mousePressEvent(QMouseEvent *);

    /// @brief 鼠标松开时发送点击信号
    void mouseReleaseEvent(QMouseEvent *);


signals:
    /// @brief 当鼠标点击然后松开之后发送此信号
    void click(const QPixmap & head,const QString & accountNum,const QString & password);

private:
    /// @brief 初始化窗口资源和窗口布局
    void initResourceAndForm();
private:
    Ui::ComboBoxItemWidget *ui;

    QPixmap head;
    QString nickname;
    QString accountNum;
    QString password;
};

#endif // COMBOBOXITEMWIDGET_H

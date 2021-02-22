#ifndef MYTOOLBUTTON_H
#define MYTOOLBUTTON_H

#include <QWidget>
#include <QToolButton>

class MyToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit MyToolButton(QWidget *parent = nullptr);

protected:
    /**
     * @brief 进入时向上传递一个信号
     */
    void enterEvent(QEvent *);

    /**
     * @brief 离开时向上传递一个信号
     */
    void leaveEvent(QEvent *);


signals:
    void sigEnter();
    void sigLeave();

public slots:
};

#endif // MYTOOLBUTTON_H

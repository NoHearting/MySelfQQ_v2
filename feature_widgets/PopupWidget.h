/**
  * @file PopupWidget.h
  * @brief 与LineEdit配合，组成一个ComboBox。
  *     当前PopupWidget为ComboBox的下拉框
  * @date 2021年3月23日17:21:13
  * @author zsj
  */
#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H

#include <QWidget>

#include "main/LoginInfo.h"

#include "dao/LoginInfoDao.h"

namespace Ui {
class PopupWidget;
}

class PopupWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief PopupWidget
     * @param parent 必须要有值。但不是为了设置父元素
     * @note parent的值是为了定位下拉框显示的位置
     */
    explicit PopupWidget(QWidget *parent);
    ~PopupWidget();


    /**
     * @brief 显示窗口
     * @note 不使用QWidget::show();
     */
    void showWindow();


    /**
     * @brief 下拉框添加元素
     * @param info
     */
    void addItem(zsj::LoginInfo::ptr info);
    void addItem(const zsj::LoginInfo & info);
signals:
    void sigClick(zsj::LoginInfo::ptr info);
    void sigHide();
private slots:
    /**
     * @brief 删除账号下拉框中的候选项
     * @param pos 删除项的坐标
     */
    void slotDeleteItem(const QPoint & pos);

protected:
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);

private:
    void initObjects();
    void initResourceAndForm();
    void initSignalsAndSlots();

    /**
     * @brief 不能直接调用此函数
     */
    void show();
private:
    Ui::PopupWidget *ui;

    /// 下拉框属于哪个控件
    QWidget * parent;

    /// 下拉框item的高度
    const static int ItemHeight = 50;

    /// 整个下拉框的最高高度
    const static int ListMaxHeight = 180;

    zsj::LoginInfoDao * infoDao;
};

#endif // POPUPWIDGET_H

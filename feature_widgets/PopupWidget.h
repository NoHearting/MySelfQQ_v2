#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H

#include <QWidget>

namespace Ui {
class PopupWidget;
}

class PopupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PopupWidget(QWidget *parent = nullptr);
    ~PopupWidget();


    void showWindow();


//    void addItem(const QString & content);
signals:
    void sigClick();
    void sigHide();

protected:
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);

private:
    void initResourceAndForm();
    void initSignalsAndSlots();

private:
    Ui::PopupWidget *ui;


    const static int ItemHeight = 50;
    const static int ListMaxHeight = 200;
};

#endif // POPUPWIDGET_H

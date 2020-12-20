#ifndef LINKMANITEMWIDGET_H
#define LINKMANITEMWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QString>

namespace Ui {
class LinkmanItemWidget;
}

class LinkmanItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LinkmanItemWidget(QWidget *parent = 0);

    LinkmanItemWidget(QPixmap & head,const QString & nickname,const QString & remark,const QString & signature,QWidget *parent = 0);
    ~LinkmanItemWidget();

    void setHead(const QPixmap & head);
    void setHead(const QString & headPath);
    void setNickname(const QString & nickname);
    void setRemark(const QString & remark);
    void setSignature(const QString & signature);

private:
    Ui::LinkmanItemWidget *ui;
};

#endif // LINKMANITEMWIDGET_H

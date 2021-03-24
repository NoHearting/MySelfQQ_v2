#include "ComboBoxItemWidget.h"
#include "ui_ComboBoxItemWidget.h"

#include "main/ReadQStyleSheet.h"
#include "utils/Util.h"

#include <QMouseEvent>
#include <QPoint>
#include <QDebug>

ComboBoxItemWidget::ComboBoxItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComboBoxItemWidget)
{
    ui->setupUi(this);
    initResourceAndForm();
}

ComboBoxItemWidget::ComboBoxItemWidget(const QPixmap &head, const QString &nickname,
                                       quint64 accountNum, const QString &password, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ComboBoxItemWidget),
      head(head), nickname(nickname), accountNum(accountNum), password(password)
{
    ui->setupUi(this);
    initResourceAndForm();

}

ComboBoxItemWidget::ComboBoxItemWidget(zsj::LoginInfo::ptr info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComboBoxItemWidget),
    info(info)
{
    ui->setupUi(this);
    initResourceAndForm();
}


void ComboBoxItemWidget::initResourceAndForm()
{
    QPixmap pix(info->getHead());
    QPixmap result = zsj::adjustToHead(pix, zsj::HeadSize::loginItemDiameter);
    ui->labelHead->setPixmap(result);
    ui->labelNickname->setText(info->getNickname());
    ui->labelAccount->setText(QString::number(info->getAccount()));
    ui->toolButtonDelete->hide();


    connect(ui->toolButtonDelete,&QToolButton::clicked,this,&ComboBoxItemWidget::slotDeleteItem);
}

zsj::LoginInfo::ptr ComboBoxItemWidget::getInfo() const
{
    return info;
}

quint64 ComboBoxItemWidget::getAccountNum() const
{
    return accountNum;
}

void ComboBoxItemWidget::setAccountNum(const quint64 &value)
{
    accountNum = value;
}

ComboBoxItemWidget::~ComboBoxItemWidget()
{
    delete ui;
}

QTextStream &ComboBoxItemWidget::operator <<(QTextStream &out)
{
    out << toString() << "\n";
    return out;
}

QDebug &ComboBoxItemWidget::operator <<(QDebug &debug)
{
    debug << toString();
    return debug;
}

QString ComboBoxItemWidget::toString() const
{
    return QString("ComboBoxItemWidget{head:[%1px:%2px],nickname:%3,accountNum:%4,password:%5}")
           .arg(head.width()).arg(head.height()).arg(nickname)
           .arg(accountNum).arg(password);
}

QPixmap ComboBoxItemWidget::getHead() const
{
    return head;
}

void ComboBoxItemWidget::setHead(const QPixmap &value)
{
    head = value;
}

QString ComboBoxItemWidget::getNickname() const
{
    return nickname;
}

void ComboBoxItemWidget::setNickname(const QString &value)
{
    nickname = value;
}


QString ComboBoxItemWidget::getPassword() const
{
    return password;
}

void ComboBoxItemWidget::setPassword(const QString &value)
{
    password = value;
}

void ComboBoxItemWidget::mouseReleaseEvent(QMouseEvent *e)
{
    emit sigClick(info);
    QWidget::mouseReleaseEvent(e);
}

void ComboBoxItemWidget::enterEvent(QEvent *event)
{
    ui->toolButtonDelete->show();
    QWidget::enterEvent(event);
}

void ComboBoxItemWidget::leaveEvent(QEvent *event)
{
    ui->toolButtonDelete->hide();
    QWidget::leaveEvent(event);
}

void ComboBoxItemWidget::slotDeleteItem()
{
    QPoint globalPos= this->mapToGlobal(ui->toolButtonDelete->pos());
    emit sigDeleteItem(globalPos);

}



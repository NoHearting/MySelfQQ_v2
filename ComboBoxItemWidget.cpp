#include "ComboBoxItemWidget.h"
#include "ui_ComboBoxItemWidget.h"

#include "ReadQStyleSheet.h"
#include "Util.h"

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
                                       const QString &accountNum, const QString &password, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ComboBoxItemWidget),
      head(head), nickname(nickname), accountNum(accountNum), password(password)
{
    ui->setupUi(this);
    initResourceAndForm();

}


void ComboBoxItemWidget::initResourceAndForm()
{
    QPixmap result = zsj::adjustToHead(head, zsj::HeadSize::loginItemDiameter);
    ui->labelHead->setPixmap(result);
    ui->labelNickname->setText(nickname);
    ui->labelAccount->setText(accountNum);
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

QString ComboBoxItemWidget::getAccountNum() const
{
    return accountNum;
}

void ComboBoxItemWidget::setAccountNum(const QString &value)
{
    accountNum = value;
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
    QPixmap origin = zsj::scaledPixmap(head, zsj::HeadSize::loginMainDiameter,
                                       zsj::HeadSize::loginMainDiameter);
    emit click(origin, accountNum, password);
    QWidget::mouseReleaseEvent(e);
}



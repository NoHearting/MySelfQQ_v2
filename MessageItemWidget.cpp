#include "MessageItemWidget.h"
#include "ui_MessageItemWidget.h"
#include "Util.h"

#include <QtGlobal>
#include <QTime>

MessageItemWidget::MessageItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageItemWidget)
{
    ui->setupUi(this);
}

MessageItemWidget::MessageItemWidget(QPixmap &head, const QString &nickname,
                                     const QString &message, const QString &date,
                                     bool symbol, bool globalInform,
                                     zsj::global::DataType type,QWidget *parent):
    QWidget(parent),
    ui(new Ui::MessageItemWidget)
{

    ui->setupUi(this);
    this->type = type;

    QPixmap round = zsj::adjustToHead(head, zsj::HeadSize::messageItemDiameter);
    ui->labelHead->setPixmap(round);
    ui->labelDate->setText(date);
    ui->labelMessage->setText(message);
    ui->labelNickname->setText(nickname);
    if(globalInform)
    {
        ui->labelHint->setText("[有全体消息]");
    }

    if(symbol)
    {
        ui->labelSymbol->setStyleSheet("background:rgb(208,207,209);"
                                       "border-radius:9px;"
                                       "color:white;"
                                       "padding:0px 3px;");
        ui->labelSymbol->setText(QString::number(qrand() % 200));
    }

    ui->labelDate->adjustSize();
    ui->labelHint->adjustSize();
    ui->labelMessage->adjustSize();
    ui->labelNickname->adjustSize();
    ui->labelSymbol->adjustSize();

    initPosition();

}

MessageItemWidget::~MessageItemWidget()
{
    delete ui;
}

void MessageItemWidget::resizeEvent(QResizeEvent *)
{
    updatePosition();
}

void MessageItemWidget::initPosition()
{
    //设置日期label的位置
    ui->labelDate->setGeometry(this->width() - ui->labelDate->width() - 9, ui->labelNickname->pos().y(),
                               ui->labelDate->width(), ui->labelDate->height());

    //设置消息label的位置
    int offset = 0;
    if(ui->labelHint->text().isEmpty()){
        offset = ui->labelHint->width();
    }
    ui->labelMessage->setGeometry(ui->labelHint->pos().x() + ui->labelHint->width() - offset, ui->labelHint->pos().y(),
                                  ui->labelMessage->width(), ui->labelMessage->height());

    //设置标签label的位置
    ui->labelSymbol->setGeometry(this->width() - ui->labelSymbol->width() - 9, ui->labelHint->pos().y(),
                                 ui->labelSymbol->width(), ui->labelSymbol->height());
}

void MessageItemWidget::updatePosition()
{
    //设置日期label的位置
    ui->labelDate->setGeometry(this->width() - ui->labelDate->width() - 9, ui->labelNickname->pos().y(),
                               ui->labelDate->width(), ui->labelDate->height());

    //设置消息label的位置
    int offset = 0;
    if(ui->labelHint->text().isEmpty()){
        offset = ui->labelHint->width();
    }
    ui->labelMessage->setGeometry(ui->labelHint->pos().x() + ui->labelHint->width() - offset, ui->labelHint->pos().y(),
                                  ui->labelMessage->width(), ui->labelMessage->height());

    //设置标签label的位置
    ui->labelSymbol->setGeometry(this->width() - ui->labelSymbol->width() - 9, ui->labelHint->pos().y(),
                                 ui->labelSymbol->width(), ui->labelSymbol->height());
}

zsj::global::DataType MessageItemWidget::getType() const
{
    return type;
}

void MessageItemWidget::setType(const zsj::global::DataType &value)
{
    type = value;
}

QString MessageItemWidget::getNickname() const
{
    return ui->labelNickname->text();
}

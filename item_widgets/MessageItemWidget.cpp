#include "MessageItemWidget.h"
#include "ui_MessageItemWidget.h"
#include "utils/Util.h"

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
                                     zsj::global::DataType type, QWidget *parent):
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

MessageItemWidget::MessageItemWidget(const zsj::Data::ptr data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageItemWidget),
    data(data)
{
    ui->setupUi(this);
    QPixmap head = data->getHead();
    QPixmap round = zsj::adjustToHead(head, zsj::HeadSize::messageItemDiameter);
    ui->labelHead->setPixmap(round);
    ui->labelNickname->setText(data->getName());

    // 默认提示全体消息、显示消息未读条数的QLabel隐藏
    ui->labelSymbol->setVisible(false);
    ui->labelHint->setVisible(false);

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
    if(ui->labelHint->text().isEmpty())
    {
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
    if(ui->labelHint->text().isEmpty())
    {
        offset = ui->labelHint->width();
    }
    ui->labelMessage->setGeometry(ui->labelHint->pos().x() + ui->labelHint->width() - offset, ui->labelHint->pos().y(),
                                  ui->labelMessage->width(), ui->labelMessage->height());

    //设置标签label的位置
    ui->labelSymbol->setGeometry(this->width() - ui->labelSymbol->width() - 9, ui->labelHint->pos().y(),
                                 ui->labelSymbol->width(), ui->labelSymbol->height());
}

zsj::Data::ptr MessageItemWidget::getData() const
{
    return data;
}

void MessageItemWidget::setData(const zsj::Data::ptr &value)
{
    data = value;
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

void MessageItemWidget::setMessage(const QString &msg)
{
    QString result = zsj::HtmlUtil::RemoveOriginTagStyle(msg,zsj::TagType::TAG_ALL);
    ui->labelMessage->setText(result);
    ui->labelMessage->adjustSize();
}

void MessageItemWidget::setDateTime(const QDateTime &dateTime)
{
    ui->labelDate->setText(dateTime.toString("MM-dd hh:mm"));
    ui->labelDate->adjustSize();
}

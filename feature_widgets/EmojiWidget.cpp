#include "EmojiWidget.h"
#include "ui_EmojiWidget.h"

#include "utils/Util.h"
#include "main/StringUserData.h"
#include "main/ReadQStyleSheet.h"

EmojiWidget::EmojiWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmojiWidget)
{
    ui->setupUi(this);

    initResourceAndForm();
    initEmoji();
    initSignalsAndSlots();
}

EmojiWidget::~EmojiWidget()
{
    delete ui;
}

void EmojiWidget::adjustPosition(const QPoint &basePos)
{
    const int padding = 10;
    QPoint pos = basePos - QPoint(padding,this->height());
    const int toolBatHeight = 40;

    QSize windowSize = zsj::SystemUtil::getDesktopSize();

    // 顶部
    if(pos.y() < 0){
        pos = basePos + QPoint(-padding,toolBatHeight);
    }
    if(pos.x() + this->width() > windowSize.width()){
        pos -= QPoint(pos.x() + this->width() - windowSize.width(),0);
    }
    this->setGeometry(QRect(pos,this->size()));
}

void EmojiWidget::show(zsj::global::UiType type)
{
    this->type = type;
    QWidget::show();
}

void EmojiWidget::closeEvent(QCloseEvent *event)
{
    emit sigWindowClose();
    QWidget::closeEvent(event);
}

void EmojiWidget::hideEvent(QHideEvent *event)
{
    emit sigWindowClose();
    QWidget::hideEvent(event);
}



void EmojiWidget::initResourceAndForm()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    zsj::WidgetUtil::setWidgetBoxShadow(ui->widget);

    this->setStyleSheet(zsj::ReadQStyleSheet::readQss("://css/emoji.css"));
}

void EmojiWidget::initSignalsAndSlots()
{
    connect(ui->tableWidget, &EmojiTableWidget::cellClicked, this, [this](int row, int col)
    {
        QLabel *label = dynamic_cast<QLabel *>(ui->tableWidget->cellWidget(row, col));
        StringUserData *stringData = dynamic_cast<StringUserData *>(
                                         label->userData(row * EmojiTableWidget::EmojiColCount + col));
        if(stringData){
            QString path = stringData->getData();
            emit sigChooseEmoji(type,path);
        }
        else{
            qCritical() << "choose emoji failed!";
        }
    });
    connect(ui->tableWidgetSymbol, &EmojiTableWidget::cellClicked, this, [this](int row, int col)
    {
        QLabel *label = dynamic_cast<QLabel *>(ui->tableWidgetSymbol->cellWidget(row, col));
        StringUserData *stringData = dynamic_cast<StringUserData *>(
                                         label->userData(row * EmojiTableWidget::EmojiColCount + col));
        if(stringData){
            QString path = stringData->getData();
            emit sigChooseEmoji(type,path);
        }
        else{
            qCritical() << "choose emoji failed!";
        }
    });
}

void EmojiWidget::initEmoji()
{
    ui->tableWidget->showEmoji(EmojiType::NORMAL);
    ui->tableWidgetSymbol->showEmoji(EmojiType::SYMBOL);
}

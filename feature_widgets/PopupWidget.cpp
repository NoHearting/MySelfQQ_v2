#include "PopupWidget.h"
#include "ui_PopupWidget.h"

#include <QDebug>

#include "item_widgets/ComboBoxItemWidget.h"
#include "utils/Util.h"

PopupWidget::PopupWidget(QWidget *parent) :
    QWidget(nullptr),
    ui(new Ui::PopupWidget),
    parent(parent)
{
    ui->setupUi(this);
    initResourceAndForm();
    initSignalsAndSlots();
}

PopupWidget::~PopupWidget()
{
    delete ui;
}


void PopupWidget::initResourceAndForm()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setStyleSheet("QListWidget{background:rgba(255,255,255,0.9);"
                                "border-radius:5px;"
                                "border:1px solid rgb(233,233,233);};"
                  "QListWidget::item:hover,"
                  "QListWidget::item:selected{border:none;background:rgba(0,0,0,0.2);}");
}

void PopupWidget::initSignalsAndSlots()
{
    connect(ui->listWidget,&QListWidget::itemClicked,this,[=](QListWidgetItem *item){
        ComboBoxItemWidget * itemWidget =  zsj::WidgetUtil::widgetCast<QListWidget,QListWidgetItem,ComboBoxItemWidget>(
                    ui->listWidget,item);
        if(itemWidget){
            emit sigClick(itemWidget->getInfo());
        }
        else{
            qCritical() << "QListWidgetItem to ComboxItemWidget failed！";
        }
    });
}

void PopupWidget::show()
{
    QWidget::show();
}


void PopupWidget::closeEvent(QCloseEvent *event)
{
    emit sigHide();
    QWidget::closeEvent(event);
}

void PopupWidget::hideEvent(QHideEvent *event)
{
    emit sigHide();
    QWidget::hideEvent(event);
}

void PopupWidget::showWindow()
{
    qDebug() << "showWindow";
//    QWidget *parent = dynamic_cast<QWidget *>(this->parent()) ;
    if(parent)
    {
        if(ui->listWidget->count() < 1)
        {
            return;
        }
        QRect geo = parent->geometry();
        qDebug() << "parent geo: " << geo;
        QPoint pos = parent->pos();
        QSize size = parent->size();
        QPoint globalPos = parent->mapToGlobal(pos);
        qDebug() << "globalPos: " << globalPos;
//        qDebug() << geo;
        int height = ui->listWidget->count() * ItemHeight > ListMaxHeight
                     ? ListMaxHeight
                     : ui->listWidget->count() * ItemHeight;
        this->setGeometry(globalPos.x() - 90, globalPos.y() - 20,
                          size.width(), height);
        qDebug() << "curr geo: " << this->geometry();
        this->show();
    }
    else
    {
        qCritical() << "parent widget is null!";
    }

}

void PopupWidget::addItem(zsj::LoginInfo::ptr info)
{
    qDebug() << info->toString();
    QPixmap pix(info->getHead());
    QPixmap head = zsj::adjustToHead(pix, zsj::HeadSize::loginItemDiameter);
    ComboBoxItemWidget *item = new  ComboBoxItemWidget(std::make_shared<zsj::LoginInfo>(*(info.get())),
            ui->listWidget);
    item->setFixedSize(235, 50);
    QListWidgetItem *widgetItem = new QListWidgetItem(ui->listWidget);
//    connect(item, &ComboBoxItemWidget::sigClick, this, &LoginWidget::slotSetAccountAndPassword);
    ui->listWidget->setItemWidget(widgetItem, item);
    widgetItem->setSizeHint(QSize(235, 50));
}

void PopupWidget::addItem(const zsj::LoginInfo &info)
{
    qDebug() << info.toString();
    QPixmap pix(info.getHead());
    QPixmap head = zsj::adjustToHead(pix, zsj::HeadSize::loginItemDiameter);
    ComboBoxItemWidget *item = new  ComboBoxItemWidget(std::make_shared<zsj::LoginInfo>(info),
            ui->listWidget);
    item->setFixedSize(235, 50);
    QListWidgetItem *widgetItem = new QListWidgetItem(ui->listWidget);
//    connect(item, &ComboBoxItemWidget::sigClick, this, &LoginWidget::slotSetAccountAndPassword);
    ui->listWidget->setItemWidget(widgetItem, item);
    widgetItem->setSizeHint(QSize(235, 50));
}


#include "PopupWidget.h"
#include "ui_PopupWidget.h"

#include <QDebug>

#include "item_widgets/ComboBoxItemWidget.h"
#include "utils/Util.h"
#include "dao/LoginInfoDao.h"

PopupWidget::PopupWidget(QWidget *parent) :
    QWidget(nullptr),
    ui(new Ui::PopupWidget),
    parent(parent)
{
    ui->setupUi(this);
    initObjects();
    initResourceAndForm();
    initSignalsAndSlots();
}

PopupWidget::~PopupWidget()
{
    delete infoDao;
    infoDao = nullptr;
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
    connect(ui->listWidget, &QListWidget::itemClicked, this, [ = ](QListWidgetItem * item)
    {
        ComboBoxItemWidget *itemWidget =  zsj::WidgetUtil::widgetCast<QListWidget, QListWidgetItem, ComboBoxItemWidget>(
                                              ui->listWidget, item);
        if(itemWidget)
        {
            emit sigClick(itemWidget->getInfo());
        }
        else
        {
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

void PopupWidget::initObjects()
{
    infoDao = new zsj::LoginInfoDao;
}

void PopupWidget::showWindow()
{
    if(parent)
    {
        if(ui->listWidget->count() < 1)
        {
            return;
        }
        QPoint pos = parent->pos();
        QSize size = parent->size();
        QPoint globalPos = parent->mapToGlobal(pos);
        int height = ui->listWidget->count() * ItemHeight > ListMaxHeight
                     ? ListMaxHeight
                     : ui->listWidget->count() * ItemHeight;
        this->setGeometry(globalPos.x() - 90, globalPos.y() - 20,
                          size.width(), height);
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
    ui->listWidget->setItemWidget(widgetItem, item);
    widgetItem->setSizeHint(QSize(235, 50));
    connect(item, &ComboBoxItemWidget::sigDeleteItem, this, &PopupWidget::slotDeleteItem);
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
    ui->listWidget->setItemWidget(widgetItem, item);
    widgetItem->setSizeHint(QSize(235, 50));
    connect(item, &ComboBoxItemWidget::sigDeleteItem, this, &PopupWidget::slotDeleteItem);
}

void PopupWidget::slotDeleteItem(const QPoint &pos)
{
    QPoint localPos = ui->listWidget->mapFromGlobal(pos);
    QListWidgetItem *item = ui->listWidget->itemAt(localPos);
    if(item)
    {
        ComboBoxItemWidget *itemWidget = zsj::WidgetUtil::widgetCast <
                                         QListWidget, QListWidgetItem, ComboBoxItemWidget >
                                         (ui->listWidget, item);
        if(itemWidget)
        {
            // 数据库删除数据
            bool ret = infoDao->deleteLoginInfo(itemWidget->getInfo()->getId());
            if(!ret)
            {
                qCritical() << "delete combobox item failed!";
            }
            QListWidgetItem *deleteItem =
                ui->listWidget->takeItem(ui->listWidget->row(item));
            delete deleteItem;
            deleteItem = nullptr;
        }
        else
        {
            qCritical() << "dynamic QListWidgetItem to ComboBoxItemWidget failed!";
        }
    }
    else
    {
        qCritical() << "current pos: " << pos << " not have item";
    }
}


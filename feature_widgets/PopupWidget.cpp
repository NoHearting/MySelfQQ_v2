#include "PopupWidget.h"
#include "ui_PopupWidget.h"

#include <QDebug>

PopupWidget::PopupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopupWidget)
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
}

void PopupWidget::initSignalsAndSlots()
{

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
    QWidget *parent = dynamic_cast<QWidget *>(this->parent()) ;
    if(parent)
    {
//        if(ui->listWidget->count() < 1)
//        {
//            return;
//        }
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
        this->setGeometry(globalPos.x() - 40, globalPos.y() - 30,
                          size.width(), height);
        qDebug() << "curr geo: " << this->geometry();
        this->show();
    }
    else
    {
        qCritical() << "parent widget is null!";
    }

}


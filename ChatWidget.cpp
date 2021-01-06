#include "ChatWidget.h"
#include "ui_ChatWidget.h"
#include "ReadQStyleSheet.h"
#include "Util.h"


ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    initObjects();
    initResourceAndForm();
    initSignalsAndSlots();
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::initObjects()
{
    frameless = new zsj::Frameless(this);
}

void ChatWidget::initResourceAndForm()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);


    // ://css/chat.css
    this->setStyleSheet(zsj::ReadQStyleSheet::readQss("D:\\QT\\QtCode\\MySelfQQ_v2\\MySelfQQ_v2\\css\\chat.css"));
    zsj::WidgetUtil::setWidgetBoxShadow(ui->widgetBody);

}

void ChatWidget::initSignalsAndSlots()
{

}

#ifdef Q_OS_LINUX

// 含有一个移动bug
// 当打开比如下拉框、菜单的东西时，点击桌面（不点击下拉框和菜单），此时移动鼠标到窗口，
// 窗口会突然非法移动
void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPoint afterMovePos = e->globalPos();
    if(offset.x() != 0 && offset.y() != 0)
    {
        QPoint moveDis = afterMovePos - offset;
        move(moveDis);
    }
}

/*
    鼠标按下事件，按下就获取当前鼠标坐标并计算出当前坐标和窗口左上角的偏移量offset
*/
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    QPoint topLeft = ui->widgetTop->mapToGlobal(ui->widgetTop->pos()) - QPoint(0, 130);
    QRect realGeometry(topLeft, QSize(ui->widgetMain->size())); // 当前窗口的真实位置大小
    QPoint cursorPos = e->globalPos();              //当前鼠标的全局位置
    if(realGeometry.contains(cursorPos))
    {
        QPoint geometryTopLeft = this->geometry().topLeft();    //当前鼠标点击窗口的左上角坐标
        offset = cursorPos - geometryTopLeft;
    }
}

/*
    鼠标放开事件，当鼠标放开时，将偏移量offset初始化为0
*/
void MainWidget::mouseReleaseEvent(QMouseEvent *)
{
    offset = QPoint(0, 0);
}
#endif

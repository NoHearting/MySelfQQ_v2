#include "feature_widgets/ToolTipWidget.h"
#include "ui_ToolTipWidget.h"

#include <QGraphicsDropShadowEffect>

ToolTipWidget::ToolTipWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolTipWidget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);   //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(3);     //阴影的模糊半径
    ui->widget->setGraphicsEffect(shadow);

    this->setStyleSheet("#widget{background:white;border:1px solid black;"
                        "border-radius:3px;margin-top:3px;}");
}

ToolTipWidget::~ToolTipWidget()
{
    delete ui;
}

void ToolTipWidget::showToolTip(const QString &msg, int x, int y, int width, int height)
{
    ui->label->setText(msg);
    this->setGeometry(x,y,width,height);
    this->show();
}

void ToolTipWidget::setToolTipCss(const QString &css)
{
    if(!css.isEmpty()){
        this->setStyleSheet(css);
    }
}

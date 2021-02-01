#include "feature_widgets/AnimationStackedWidget.h"
#include <QByteArray>
#include <QRect>
#include <QPixmap>
#include <QDebug>

AnimationStackedWidget::AnimationStackedWidget(QWidget *parent ) : QStackedWidget(parent)
{
    isAnimation = false;
    isLeft = true;
    duration = 200;
    animation = new QPropertyAnimation(this, QByteArray());
    connect(animation, &QPropertyAnimation::valueChanged, this, &AnimationStackedWidget::valueChangedAnimation);
    connect(animation, &QPropertyAnimation::finished, this, &AnimationStackedWidget::animationFinished);
}

void AnimationStackedWidget::valueChangedAnimation(QVariant value)
{
    qDebug() << "valueChanged";
    currentValue = value;
    update();
}

void AnimationStackedWidget::animationFinished()
{
    isAnimation = false;
    this->widget(this->currentIndex())->show();
    this->setCurrentIndex(nextIndex);
}

void AnimationStackedWidget::nextWidget()
{
    if(!isAnimation)
    {
        isLeft = true;
        widgetCount = this->count();
        int index = this->currentIndex();
        nextIndex = (index + 1) % widgetCount;
        startAnimation(index);
    }
}

void AnimationStackedWidget::forwordWidget()
{
    if(!isAnimation)
    {
        isLeft = false;
        widgetCount = this->count();
        int index = this->currentIndex();
        nextIndex = (index - 1 + widgetCount) % widgetCount;
        startAnimation(index);
    }
}

void AnimationStackedWidget::startAnimation(int index)
{
    isAnimation = true;
    this->widget(index)->hide();
    QRect g = this->geometry();
    animation->setStartValue(g.width());
    animation->setEndValue(g.x());
    animation->setDuration(duration);
    animation->start();
}


void AnimationStackedWidget::paintEvent(QPaintEvent *)
{
    if(isAnimation)
    {
        QPainter painter(this);
        paintNext(painter, nextIndex);
        paintPreviouse(painter, this->currentIndex());
    }
}

void AnimationStackedWidget::paintPreviouse(QPainter &painter, int index)
{
    QWidget *widget = this->widget(index);
    QPixmap pixmap((widget->size()));
    widget->render(&pixmap);
    QRect rect = widget->geometry();

    double value = currentValue.toDouble();
    QRectF r1(0.0, 0.0, value, rect.height());
    QRectF r2(rect.width() - value, 0, value, rect.height());
    if(isLeft)
    {
        painter.drawPixmap(r1, pixmap, r2);
    }
    else
    {
        painter.drawPixmap(r2, pixmap, r1);
    }
}

void AnimationStackedWidget::paintNext(QPainter &painter, int index)
{
    QWidget *nextWidget = this->widget(index);
    QRect rect = this->geometry();
    nextWidget->resize(rect.width(), rect.height());
    QPixmap nextPixmap(nextWidget->size());
    nextWidget->render(&nextPixmap);
    double value = currentValue.toDouble();
    QRectF r1(value, 0, rect.width() - value, rect.height());
    QRectF r2(0, 0, rect.width() - value, rect.height());
    if(isLeft)
    {
        painter.drawPixmap(r1, nextPixmap, r2);
    }
    else
    {
        painter.drawPixmap(r2, nextPixmap, r1);
    }
}



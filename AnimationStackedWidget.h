#ifndef ANIMATIONSTACKEDWIDGET_H
#define ANIMATIONSTACKEDWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QVariant>
#include <QPropertyAnimation>
#include <QPainter>

class AnimationStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit AnimationStackedWidget(QWidget * parent = 0);

    /// @brief 下一个界面
    void nextWidget();

    /// @brief 上一个界面
    void forwordWidget();

public slots:
    /// @brief 值改变的槽函数
    void valueChanged(QVariant value);

    /// @brief 动画完成
    void animationFinished();



protected:
    void paintEvent(QPaintEvent * event);


private:
    /// @brief 画上一个界面
    void paintPreviouse(QPainter & painter,int index);

    /// @brief 画下一个界面
    void paintNext(QPainter & painter,int index);

    void startAnimation(int index);
private:
    QPropertyAnimation * animation;     ///过渡框架
    quint16 duration;       /// 过渡时间
    bool isAnimation;       /// 是否正在过渡
    QVariant currentValue;  /// 当前过渡到的值
    quint8 widgetCount;     /// stackedWidget的页面数
    quint8 nextIndex;       /// 下一个页面
    bool isLeft;            /// 是否向左过渡（只能左右过渡）

};

#endif // ANIMATIONSTACKEDWIDGET_H

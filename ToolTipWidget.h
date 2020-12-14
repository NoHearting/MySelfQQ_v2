#ifndef TOOLTIPWIDGET_H
#define TOOLTIPWIDGET_H

#include <QWidget>

namespace Ui {
class ToolTipWidget;
}

class ToolTipWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolTipWidget(QWidget *parent = 0);
    ~ToolTipWidget();


    void showToolTip(const QString & msg,int x,int y,int width = 135,int height = 30);

    void setToolTipCss(const QString & css);
private:
    Ui::ToolTipWidget *ui;
};

#endif // TOOLTIPWIDGET_H

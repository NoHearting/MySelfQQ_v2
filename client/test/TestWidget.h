#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>

namespace Ui {
class TestWidget;
}

class TestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestWidget(QWidget *parent = nullptr);
    ~TestWidget();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_pushButtonGet_clicked();

    void on_pushButtonPost_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::TestWidget *ui;

    QString * string;
};

#endif // TESTWIDGET_H

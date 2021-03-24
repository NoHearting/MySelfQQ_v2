#ifndef WARNDIALOG_H
#define WARNDIALOG_H

#include <QDialog>
#include <QString>
#include <QPixmap>

namespace Ui {
class WarnDialog;
}

class WarnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WarnDialog(QWidget *parent = 0);
    ~WarnDialog();


    void showDialog(const QString & title,const QString & info);
    void changeFlagPng(QPixmap & flag);
private:
    Ui::WarnDialog *ui;

signals:
    void sure();
private slots:
    void sendSureSignal();
};

#endif // WARNDIALOG_H

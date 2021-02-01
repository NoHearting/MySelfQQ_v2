#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QWidget>
#include <QTextEdit>

#include <QKeyEvent>

class MyTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit MyTextEdit(QWidget *parent = nullptr);

    bool getKeySendMsg() const;
    void setEnterSendMsg();
    void setCtrlEnterSendMsg();

protected:
    /// @brief 重写键盘点击事件
    /// 主要是处理Enter和Ctrl+Enter发送消息
    bool eventFilter(QObject *, QEvent *);

private:
    /// @brief 发送信号到父组件，进行发送消息
    void emitSigToSendMessage(bool EnterKeyFlag = true);

private:
    /// @brief 是否回车发送消息，默认为回车（Enter）发送，可以改为（Enter+Ctrl）发送
    bool isEnterSendMsg = true;
signals:
    /// @brief 按键发送消息
    void sigKeyToSendMsg(const QString & message);

    /// @brief 消息为空发出此信号
    void sigMsgEmpty();
public slots:
};

#endif // MYTEXTEDIT_H

#include "customer_widgets/MyTextEdit.h"

#include <QDebug>

MyTextEdit::MyTextEdit(QWidget *parent) : QTextEdit(parent)
{


    this->installEventFilter(this);
}

bool MyTextEdit::getKeySendMsg() const
{
    return isEnterSendMsg;
}

void MyTextEdit::setEnterSendMsg()
{
    isEnterSendMsg = true;
}

void MyTextEdit::setCtrlEnterSendMsg()
{
    isEnterSendMsg = false;
}

bool MyTextEdit::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == event->KeyPress)
    {
        /// 同时检测单个按键和组合键的情况下要先检测组合键，不然组合键无法被检测到
        QKeyEvent *keyEvent = (QKeyEvent *)event;

        if((keyEvent->modifiers() & Qt::ControlModifier)
                && (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter))
        {
            qDebug() << "Ctrl + Enter/Return";
            emitSigToSendMessage(!isEnterSendMsg);
            return true;
        }
        else if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter){
            qDebug() << "Return or Enter";
            emitSigToSendMessage(isEnterSendMsg);
            return true;
        }
    }
    return false;
}


void MyTextEdit::emitSigToSendMessage(bool EnterKeyFlag)
{
    if(EnterKeyFlag){
        QString msg = this->toPlainText();
        if(msg.isEmpty()){
            emit sigMsgEmpty();
            return;
        }
        emit sigKeyToSendMsg(msg);
    }
    else{
        // 如果当前按键并不是发送消息的按钮，则在文本框添加一个 \n
        this->insertPlainText("\n");
    }
}


#include "customer_widgets/MyTextEdit.h"

#include <QDebug>
#include <QClipboard>
#include <QDir>
#include <QMimeData>
#include <QObject>
#include <QWidget>
#include <QApplication>

#include "utils/Util.h"

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
        else if(keyEvent->modifiers() & Qt::ControlModifier &&
                keyEvent->key() == Qt::Key_V){
            // 粘贴
            QClipboard *clipboard = QApplication::clipboard();
            const QMimeData *mimeData = clipboard->mimeData();
            if(mimeData->hasImage()){
                QString processPath = zsj::SystemUtil::getProcessPath();

                QString screenShotPath = processPath + "/" + "screen_shot/";
                QString fileName = zsj::GetCurrentDateTime() + ".jpg";
                QPixmap pix = qvariant_cast<QPixmap>(mimeData->imageData());

                QSharedPointer<QDir> dir(new QDir);
                if(!dir->exists(screenShotPath)){
                    dir->mkdir(screenShotPath);
                }
                QString imagePath = screenShotPath + fileName;
                bool isOk = pix.save(imagePath,Q_NULLPTR,100);
                if(isOk){
                    int height = pix.height();
                    int width = pix.width();
                    int realHeight = height;
                    int realWidth = width;
                    if(height > width){
                        if(height >= 150){
                            realHeight = 150;
                            realWidth = 150 * 1.0 / height * width;
                        }
                    }
                    else{
                        if(width >= 150){
                            realWidth = 150;
                            realHeight = 150 * 1.0 / width * height;
                        }
                    }
//                    QString imgUrl = "<img src='"+imagePath+"' width=" +realWidth+" height="+realHeight+"'></img>";
                    QString imgUrl = QString("<img src='%1' width=%2 height=%3 ></img>")
                            .arg(imagePath).arg(realWidth).arg(realHeight);
                    qDebug() << imgUrl;
//                    clipboard->setText(imgUrl);
                    this->insertHtml(imgUrl);
                }
                else{
                    qDebug() << "save image failed";
                }
            }
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


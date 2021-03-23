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
                keyEvent->key() == Qt::Key_V)
        {
            // 粘贴
            QClipboard *clipboard = QApplication::clipboard();
            const QMimeData *mimeData = clipboard->mimeData();
            if(mimeData->hasImage())
            {
                QString processPath = zsj::SystemUtil::getProcessPath();

                QString screenShotPath = processPath + "/" + zsj::global::ScreenShotDirName + "/";
                QString fileName = zsj::GetCurrentDateTime("yyyy-MM-dd-HH-mm-ss") + ".jpg";
                QPixmap pix = qvariant_cast<QPixmap>(mimeData->imageData());

                bool isExist = zsj::FileUtil::judgeAndMakeDir(screenShotPath);
                if(!isExist)
                {
                    qCritical() << screenShotPath << " not exist or create failed!";
                    return true;
                }
                QString imagePath = screenShotPath + fileName;
                // 保存截屏到程序运行的一个路径下
                bool isOk = pix.save(imagePath, Q_NULLPTR, 100);
                if(isOk)
                {
                    QSize pasteSize = zsj::Util::ScaledImageSize(pix.size());
                    QString imgUrl = zsj::Util::PackageImageHtml(imagePath,pasteSize.width(),pasteSize.height());
                    this->insertHtml(imgUrl);
                }
                else
                {
                    qDebug() << "save image failed";
                }
            }
        }
        else if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            qDebug() << "Return or Enter";
            emitSigToSendMessage(isEnterSendMsg);
            return true;
        }
    }
    return false;

}


void MyTextEdit::emitSigToSendMessage(bool EnterKeyFlag)
{
    if(EnterKeyFlag)
    {
        QString content = getContents();
        if(content.isEmpty())
        {
            emit sigMsgEmpty();
            return;
        }
        emit sigKeyToSendMsg(content);
    }
    else
    {
        // 如果当前按键并不是发送消息的按钮，则在文本框添加一个 \n
        this->insertPlainText("\n");
    }
}

QString MyTextEdit::getContents()
{
    QString html = toHtml();
    int begin = html.indexOf("<body");
    int bodyEnd = html.indexOf("</body>",begin);
    QString content = html.mid(begin,bodyEnd-begin+7);
    return content;
}


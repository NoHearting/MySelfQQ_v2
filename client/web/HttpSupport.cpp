#include "HttpSupport.h"

#include <QEventLoop>
#include <QMutex>
#include <QMutexLocker>

#include <QPixmap>


#include "utils/Util.h"

namespace zsj {

HttpSupport::ptr HttpSupport::httpSupport;

HttpSupport *HttpSupport::Instance()
{
    if(!httpSupport){
        static QMutex mutex;
        QMutexLocker lock(&mutex);
        if(!httpSupport){
            httpSupport.reset(new HttpSupport);
        }
    }
    return httpSupport.get();
}


HttpSupport::HttpSupport(QObject *parent) :
    QObject(parent)
{
    manager.reset(new QNetworkAccessManager(parent));
}


QByteArray HttpSupport::syncGet(const QString &url)
{
    return syncGet(QUrl(url));
}

QByteArray HttpSupport::syncGet(const QString &url, const QUrlQuery &urlQuery)
{
    QUrl urlLocal(url);
    urlLocal.setQuery(urlQuery);
    return syncGet(urlLocal);
}

QByteArray HttpSupport::syncGet(const QString &url, const QMap<QString, QString> &data)
{
    QUrl urlLocal(url);
    QUrlQuery query;
    if(!data.empty()){
        for(auto iter = data.begin();iter!= data.end();++iter){
            query.addQueryItem(iter.key(),iter.value());
        }
    }
    urlLocal.setQuery(query);
    return syncGet(url);
}


QByteArray HttpSupport::syncGet(const QUrl &url)
{
    QNetworkRequest req;
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
    req.setUrl(url);
    return syncGet(req);
}

QByteArray HttpSupport::syncGet(const QNetworkRequest &req)
{
    QNetworkReply * reply = manager->get(req);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    return dealReply(reply);
}

QByteArray HttpSupport::syncPost(const QString &url)
{
    return syncPost(url,QByteArray());
}

QByteArray HttpSupport::syncPost(const QUrl &url)
{
    return syncPost(url.url(),QByteArray());
}

QByteArray HttpSupport::syncPost(const QString &url, const QMap<QString, QString> &data)
{
    QJsonObject obj;
    for(auto iter = data.begin();iter != data.end();++iter){
        obj.insert(iter.key(),iter.value());
    }
    return syncPost(url,QJsonDocument(obj).toJson());
}

QByteArray HttpSupport::syncPost(const QString &url, const QJsonObject &data)
{
    return syncPost(url,QJsonDocument(data).toJson());
}

QByteArray HttpSupport::syncPost(const QString &url, const QByteArray &data)
{
    QNetworkRequest req;
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
    req.setUrl(QUrl(url));
    return syncPost(req,data);
}

QByteArray HttpSupport::syncPost(const QNetworkRequest &req, const QByteArray &data)
{
    QNetworkReply *reply = manager->post(req, data);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    return dealReply(reply);
}

QString HttpSupport::downloadImage(const QString &url,
                                   const QString &path,
                                   const QString &imageName)
{
    QByteArray imageData = syncGet(url);
    if(!imageData.isEmpty()){
        QPixmap image;
        image.loadFromData(imageData);
        bool ret = FileUtil::judgeAndMakeDir(path);
        if(ret){
//            QString name = url.mid()
            int pos = url.lastIndexOf("/");
            QString name = url.mid(pos + 1);
            if(!imageName.isEmpty()){
                name = imageName;
            }
            QString actPath = path + name;
            qDebug() << actPath;
            bool saveRet = image.save(actPath,Q_NULLPTR,100);
            if(saveRet){
                qDebug() << "save " << actPath << " success";
                return actPath;
            }
            else{
                qCritical() << "save " << actPath << " failed!";
                return "";
            }
        }
        else{
            qCritical() << "create iamge folder failed!";
            return "";
        }
    }
    else{
        qCritical() << "get image failed!";
        return "";
    }
}

bool HttpSupport::uploadImage(const QString &url, const QString &path)
{
    return false;
}


QByteArray HttpSupport::dealReply(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        qCritical() << "reply error: " << reply->errorString();
        reply->deleteLater();
        return QByteArray();
    }
    else
    {
        //请求方式
        qDebug() << "operation:" << reply->operation();
        //状态码
        qDebug() << "status code:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << "url:" << reply->url();
        //qDebug()<<"raw header:"<<reply->rawHeaderList();

        //获取响应信息
        const QByteArray replyData = reply->readAll();
        reply->deleteLater();
        return replyData;
    }
}

} // namespace zsj

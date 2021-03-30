#include "LoginWebService.h"

#include "utils/Global.h"

namespace zsj {

LoginWebService::LoginWebService()
{
    httpSupport = HttpSupport::Instance();
}

QJsonObject LoginWebService::login(int id, QString password)
{
    QJsonObject obj;
    obj.insert("id",id);
    obj.insert("password",password);
    QByteArray data = httpSupport->syncPost(global::BgUrl::LoginUrl(),obj);
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isEmpty() && !doc.isNull()){
        return doc.object();
    }
    else{
        return QJsonObject();
    }
}

QString LoginWebService::downloadHeadPicture(const QString &url, const QString &path, const QString &imageName)
{
    return httpSupport->downloadImage(url,path,imageName);
}

} // namespace zsj

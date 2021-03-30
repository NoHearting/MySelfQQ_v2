#pragma once

#include <memory>

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

#include <QMap>

namespace zsj
{

class HttpSupport : public QObject
{
    Q_OBJECT
public:

    typedef std::shared_ptr<HttpSupport> ptr;

    static HttpSupport * Instance();

    /**
     * @brief 发送同步get请求
     * @return
     */
    QByteArray syncGet(const QString &url);
    QByteArray syncGet(const QUrl &url);
    QByteArray syncGet(const QString &url, const QUrlQuery &urlQuery);
    QByteArray syncGet(const QString &url, const QMap<QString, QString> &data);
    QByteArray syncGet(const QNetworkRequest &req);

    /**
     * @brief 发送同步post请求
     * @return QByteArray
     */
    QByteArray syncPost(const QString &url);
    QByteArray syncPost(const QUrl &url);
    QByteArray syncPost(const QString &url, const QMap<QString, QString> &data);
    QByteArray syncPost(const QString &url, const QJsonObject &data);
    QByteArray syncPost(const QString &url, const QByteArray &data);
    QByteArray syncPost(const QNetworkRequest &req, const QByteArray &data);



    /**
     * @brief 下载图片
     * @param url 图片下载的路径
     * @param path 图片想要存储的路径
     * @param imageName 需要设置的图片名字。不设置图片为url中名字
     * @return 当前文件所在的路径
     */
    QString downloadImage(const QString & url,
                          const QString & path,
                          const QString & imageName = "");

    /**
     * @brief 上传图片
     * @param url 图片上传的路径
     * @param path 图片的绝对路径
     * @return 是否上传成功
     * @note 实现后台web服务器之后才能使用此函数
     */
    bool uploadImage(const QString & url,const QString & path);

private:
    HttpSupport(QObject *parent = nullptr);

    /**
     * @brief 返回QNetworkReply中的数据
     * @param reply
     * @return QByteArray
     */
    QByteArray dealReply(QNetworkReply *reply);

private:
    std::shared_ptr<QNetworkAccessManager> manager;

    static HttpSupport::ptr httpSupport;
};

}

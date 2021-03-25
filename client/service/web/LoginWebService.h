#pragma once

#include "web/HttpSupport.h"
#include "main/UserData.h"
#include <QJsonObject>
#include <QJsonDocument>


namespace zsj {

class LoginWebService{

public:

    LoginWebService();

    /**
     * @brief 登录
     * @param id 账号
     * @param password 密码
     * @return  QJsonObject 登录结果
     */
    QJsonObject login(int id,QString password);

    /**
     * @brief 下载图片
     * @param url 图片下载的路径
     * @param path 图片想要存储的路径
     * @param imageName 需要设置的图片名字。不设置图片为url中名字
     * @return 当前文件所在的路径
     */
    QString downloadHeadPicture(const QString & url,
                                const QString & path,
                                const QString & imageName = "");

private:
    HttpSupport * httpSupport;
};

} // namespace zsj



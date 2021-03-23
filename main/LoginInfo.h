/**
  * @file LoginInfo.h
  * @brief 登录界面的用户登录信息
  * @author zsj
  * @date 2021年3月17日13:32:44
  */
#ifndef LOGININFO_H
#define LOGININFO_H

#include <QString>
#include <memory>

namespace zsj {


class LoginInfo
{
public:
    typedef std::shared_ptr<LoginInfo> ptr;

    LoginInfo(quint64 id,const QString & head,const QString & nickname,
              quint64 account,const QString & password,bool autoLogin,
              bool savePassword,quint64 lastUpdate);

    LoginInfo();

    LoginInfo(const LoginInfo & info);


    QString toString()const;

    QString getHead() const;
    void setHead(const QString &value);

    QString getNickname() const;
    void setNickname(const QString &value);

    quint64 getAccount() const;
    void setAccount(const quint64 &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    bool getAutoLogin() const;
    void setAutoLogin(bool value);

    bool getSavePassword() const;
    void setSavePassword(bool value);

    quint64 getId() const;
    void setId(const quint64 &value);

    quint64 getLastUpdate() const;
    void setLastUpdate(const quint64 &value);

private:
    quint64 id;
    QString head;
    QString nickname;
    quint64 account;
    QString password;
    bool autoLogin;
    bool savePassword;
    quint64 lastUpdate;
};

} // namespace zsj
#endif // LOGININFO_H

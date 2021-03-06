#include "LoginInfo.h"

namespace zsj
{





LoginInfo::LoginInfo(quint64 id, const QString &head,
                     const QString &nickname,
                     quint64 account,
                     const QString &password,
                     bool autoLogin,
                     bool savePassword,
                     quint64 lastUpdate) :
    id(id), head(head), nickname(nickname), account(account),
    password(password), autoLogin(autoLogin), savePassword(savePassword),
    lastUpdate(lastUpdate)
{

}

LoginInfo::LoginInfo(const LoginInfo &info) :
    id(info.getId()),head(info.getHead()),nickname(info.getNickname()),
    account(info.getAccount()),password(info.getPassword()),
    autoLogin(info.getAutoLogin()),savePassword(info.getSavePassword()),
    lastUpdate(info.getLastUpdate())
{

}

LoginInfo::LoginInfo() :
    id(0), head(""), nickname(""), account(-1), password(""),
    autoLogin(false), savePassword(false),lastUpdate(0)
{

}

QString LoginInfo::toString() const
{
    return QString("LoginInfo{id:%1,head:%2,nickname:%3,account:%4,"
                   "password:%5,autoLogin:%6,savePassword:%7}").arg(id).
           arg(head).arg(nickname).arg(account).arg(password).
           arg(autoLogin).arg(savePassword);
}

QString LoginInfo::getHead() const
{
    return head;
}

void LoginInfo::setHead(const QString &value)
{
    head = value;
}

QString LoginInfo::getNickname() const
{
    return nickname;
}

void LoginInfo::setNickname(const QString &value)
{
    nickname = value;
}

quint64 LoginInfo::getAccount() const
{
    return account;
}

void LoginInfo::setAccount(const quint64 &value)
{
    account = value;
}

QString LoginInfo::getPassword() const
{
    return password;
}

void LoginInfo::setPassword(const QString &value)
{
    password = value;
}

bool LoginInfo::getAutoLogin() const
{
    return autoLogin;
}

void LoginInfo::setAutoLogin(bool value)
{
    autoLogin = value;
}

bool LoginInfo::getSavePassword() const
{
    return savePassword;
}

void LoginInfo::setSavePassword(bool value)
{
    savePassword = value;
}

quint64 LoginInfo::getId() const
{
    return id;
}

void LoginInfo::setId(const quint64 &value)
{
    id = value;
}

quint64 LoginInfo::getLastUpdate() const
{
    return lastUpdate;
}

void LoginInfo::setLastUpdate(const quint64 &value)
{
    lastUpdate = value;
}


}

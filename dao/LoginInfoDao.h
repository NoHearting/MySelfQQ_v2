/**
  * @file LoginInfo.h
  * @brief 登录信息dao类，用于和数据库交互
  * @author zsj
  * @date 2021年3月17日10:28:50
  */

#pragma once

#include <QScopedPointer>
#include <QVector>


#include "main/LoginInfo.h"
#include "database/SQLiteDataBase.h"

namespace zsj {


class LoginInfoDao{

public:
    typedef QScopedPointer<LoginInfoDao> LIDao;

    LoginInfoDao();
    ~LoginInfoDao();
public:
    QVector<LoginInfo> listLoginInfo();

    bool deleteLoginInfo(quint64 id);

    bool updateLoginInfo(const LoginInfo & info);

    bool insertLoginInfo(const LoginInfo & info);

private:
    DataBase * db;
};
} // namespace zsj

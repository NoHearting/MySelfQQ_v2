#include "LoginInfoDao.h"

#include <QSqlQuery>
#include <QVariant>

#include <QDebug>
#include "utils/Util.h"
#include "main/ApplicationInfo.h"

namespace zsj
{

LoginInfoDao::LoginInfoDao()
{
    QString dbFile = "login_info.db";
    // 获取当前程序路径
    QString dbPath = zsj::ApplicationInfo::Instance()->getAppAbsoluteDir() +
                     zsj::global::LoginInfoDir;
    // 创建文件夹
    bool flag = zsj::FileUtil::judgeAndMakeDir(dbPath);
    if(!flag)
    {
        qCritical() << "create database path failed!";
    }
    dbPath += "/" + dbFile;
    db = SQLiteDataBase::Instance("QSQLITE", dbPath, DBDriverType::SQLITE);
}

LoginInfoDao::~LoginInfoDao()
{
}

QVector<LoginInfo> LoginInfoDao::listLoginInfo()
{
    QSqlQuery query(db->getDatabase());
    query.prepare("select * from login_info order by last_update desc");
    bool ret = db->selectQuery(query);
    QVector<LoginInfo> loginInfoVec;
    if(ret)
    {

        while(query.next())
        {
            LoginInfo info(query.value(0).toInt(),
                           query.value(1).toString(),
                           query.value(2).toString(),
                           query.value(3).toInt(),
                           query.value(4).toString(),
                           query.value(5).toBool(),
                           query.value(6).toBool(),
                           query.value(7).toInt());
            loginInfoVec.push_back(info);
        }
    }
    else
    {
        qCritical() << query.lastError();
    }
    return loginInfoVec;
}

bool LoginInfoDao::deleteLoginInfo(quint64 id)
{
    QSqlQuery query(db->getDatabase());
    query.prepare("delete from login_info where id = ?");
    query.bindValue(0, id);
    bool ret = db->deleteQuery(query);
    if(ret)
    {
        return true;
    }
    else
    {
        qCritical() << query.lastError();
        return false;
    }
}

bool LoginInfoDao::updateLoginInfo(const LoginInfo &info)
{
    QSqlQuery query(db->getDatabase());
    query.prepare("update login_info set head=?, "
                  "nickname=?,password=?,auto_login=?, "
                  "save_password=?,last_update=? where account=? ");
    query.bindValue(0, info.getHead());
    query.bindValue(1, info.getNickname());
    query.bindValue(2, info.getPassword());
    query.bindValue(3, info.getAutoLogin());
    query.bindValue(4, info.getSavePassword());
    query.bindValue(5, info.getLastUpdate());
    query.bindValue(6, info.getAccount());
    bool ret = db->updateQuery(query);
    if(ret)
    {
        return true;
    }
    else
    {
        qCritical() << query.lastError();
        return false;
    }
}

bool LoginInfoDao::insertLoginInfo(const LoginInfo &info)
{
    QSqlQuery query(db->getDatabase());
    query.prepare("insert into login_info(head,nickname,account,"
                  "password,auto_login,save_password,last_update) "
                  "values(?,?,?,?,?,?,?)");
    query.bindValue(0, info.getHead());
    query.bindValue(1, info.getNickname());
    query.bindValue(2, info.getAccount());
    query.bindValue(3, info.getPassword());
    query.bindValue(4, info.getAutoLogin());
    query.bindValue(5, info.getSavePassword());
    query.bindValue(6, info.getLastUpdate());
    bool ret = db->insertQuery(query);
    if(ret)
    {
        return true;
    }
    else
    {
        qCritical() << query.lastError();
        return false;
    }
}



} // namespace zsj

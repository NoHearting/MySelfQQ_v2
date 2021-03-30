#include "MainWebService.h"
#include "main/ApplicationInfo.h"
#include "main/Section.h"

#include <QMap>
#include <QJsonArray>
#include <QUrlQuery>
#include <QJsonValue>

namespace zsj
{



MainWebService::MainWebService()
{
    httpSupport = HttpSupport::Instance();
}

QVector<QVector<SectionData>> MainWebService::friendRelationship(quint64 id)
{
    QUrlQuery query;
    query.addQueryItem("id",QString::number(id));
    QByteArray data = httpSupport->syncGet(global::BgUrl::FriendRelationship(), query);
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QVector<QVector<SectionData>> result;
    if(!doc.isEmpty())
    {
        QJsonObject rootObj = doc.object();
        if(rootObj.value("status").toBool() == true)
        {
            qDebug() << "获取信息成功";
            QJsonObject dataObj = rootObj["data"].toObject();
            QJsonArray array = dataObj["relationship"].toArray();
            /// 好友列表
            QVector<SectionData> sectionUserVec;
            QJsonArray arrayUser = array.at(0).toArray();
            for(int i = 0; i < arrayUser.size(); i++)
            {
                QJsonObject sectionUserObj = arrayUser[i].toObject();

                // section 数据
                QJsonObject section = sectionUserObj["section"].toObject();
                SectionData sd(Section(section["id"].toInt(),
                               section["sectionName"].toString(),
                               section["belong"].toInt(),
                               section["size"].toInt(),
                               section["type"].toBool()));
                QJsonArray items = sectionUserObj["items"].toArray();
                QVector<zsj::Data::ptr> userItems;
                for(int j = 0; j < items.size(); j++)
                {
                    QJsonObject obj = items[j].toObject();
                    // todo 需要处理头像  是否下载
                    QString actPath = zsj::ApplicationInfo::Instance()->getAppAbsoluteDir();
                    QString headDir = QString("/image/%1/headImage/").arg(id);
                    QString headPath = httpSupport->downloadImage(
                                obj["head"].toString(),
                                actPath + headDir);
                    userItems.push_back(std::make_shared<zsj::UserData>(
                                            headPath,
                                            obj["nickname"].toString(),
                                            obj["id"].toInt(),
                                            obj["signature"].toString(),
                                            "",
                                            obj["vip"].toBool(),
                                            obj["level"].toInt()
                            ));
                }
                sd.setItems(userItems);
                sectionUserVec.push_back(sd);
            }

            result.push_back(sectionUserVec);

            QVector<SectionData> sectionGroupVec;
            QJsonArray arrayGroup = array.at(1).toArray();
            for(int i = 0; i < arrayGroup.size(); i++)
            {
                QJsonObject sectionGroupObj = arrayGroup[i].toObject();

                // section 数据
                QJsonObject section = sectionGroupObj["section"].toObject();
                SectionData sd(Section(section["id"].toInt(),
                               section["sectionName"].toString(),
                               section["belong"].toInt(),
                               section["size"].toInt(),
                               section["type"].toBool()));
                QJsonArray items = sectionGroupObj["items"].toArray();
                QVector<zsj::Data::ptr> groupItems;
                for(int j = 0; j < items.size(); j++)
                {
                    QJsonObject obj = items[j].toObject();
                    // todo 需要处理头像  是否下载
                    groupItems.push_back(std::make_shared<zsj::GroupData>(
                                            obj["head"].toString(),
                                            obj["nickname"].toString(),
                                            obj["id"].toInt(),
                                            obj["introduce"].toString(),
                                            obj["maxSize"].toInt(),
                                            obj["currentNum"].toInt(),
                                            obj["vip"].toBool()
                            ));
                }
                sd.setItems(groupItems);
                sectionGroupVec.push_back(sd);
            }

            result.push_back(sectionGroupVec);

            return result;
        }
        else
        {
            qCritical() << rootObj["message"];
            return result;
        }
    }
    else
    {
        qCritical() << "get data failed!";
        return result;
    }
}

bool MainWebService::addSection(const Section &section)
{
    QJsonObject data;
    data.insert("sectionName",section.getSectionName());
    data.insert("belong",(qint64)section.getBelong());
    data.insert("size",section.getSize());
    data.insert("type",section.getType());
    QByteArray result = httpSupport->syncPost(zsj::global::BgUrl::AddSection(),data);
    QJsonDocument doc = QJsonDocument::fromJson(result);
    if(!doc.isEmpty() && !doc.isNull()){
        QJsonObject resultObj = doc.object();
        if(resultObj["status"] == true){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool MainWebService::deleteSection(quint64 deleteSectionId, quint64 toSectionId, bool type)
{
    QJsonObject data;
    data.insert("deleteSectionId",(qint64)deleteSectionId);
    data.insert("toSectionId",(qint64)toSectionId);
    data.insert("type",type);
    QByteArray result = httpSupport->syncPost(zsj::global::BgUrl::DeleteSection(),data);
    QJsonDocument doc = QJsonDocument::fromJson(result);
    if(!doc.isEmpty() && !doc.isNull()){
        QJsonObject resultObj = doc.object();
        if(resultObj["status"] == true){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool MainWebService::moveSectionItem(quint64 fromSectionId,
                                     quint64 toSectionId,
                                     quint64 objectId, bool type)
{
    QJsonObject data;
    data.insert("fromSectionId",(qint64)fromSectionId);
    data.insert("toSectionId",(qint64)toSectionId);
    data.insert("objectId",(qint64)objectId);
    data.insert("type",type);
    QByteArray result = httpSupport->syncPost(zsj::global::BgUrl::MoveSectionItem(),data);
    QJsonDocument doc = QJsonDocument::fromJson(result);
    if(!doc.isEmpty() && !doc.isNull()){
        QJsonObject resultObj = doc.object();
        if(resultObj["status"] == true){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

} // namespace zsj

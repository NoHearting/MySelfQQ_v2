#ifndef MAINWEBSERVICE_H
#define MAINWEBSERVICE_H

#include "web/HttpSupport.h"
#include "main/UserData.h"
#include "main/GroupData.h"
#include "main/SectionData.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QVector>
#include <QMap>

namespace zsj {

class MainWebService
{
public:
    MainWebService();

    /**
     * @brief 好友群组关系列表
     * @param id
     * @return
     */
    QVector<QVector<SectionData>> friendRelationship(quint64 id);

    /**
     * @brief 添加分组
     * @param section 分组数据
     * @return
     */
    bool addSection(const Section & section);

    /**
     * @brief 删除分组
     * @param deleteSectionId 删除分组的id
     * @param toSectionId   删除分组内的item需要移动到的分组item
     * @param type  分组类型 true-群分组  false-用户分组
     * @return
     */
    bool deleteSection(quint64 deleteSectionId,quint64 toSectionId,bool type);


    /**
     * @brief 移动分组内的item
     * @param fromSectionId 从哪个分组移除
     * @param toSectionId   移入哪个分组
     * @param objectId  移动的对象
     * @param type
     * @return
     */
    bool moveSectionItem(quint64 fromSectionId,quint64 toSectionId,
                         quint64 objectId,bool type);
private:
    HttpSupport * httpSupport;
};
} // namespace zsj

#endif // MAINWEBSERVICE_H

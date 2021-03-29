package top.zsj.webserver.service.impl;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import top.zsj.webserver.domain.*;
import top.zsj.webserver.mapper.LoginMapper;
import top.zsj.webserver.mapper.MainMapper;
import top.zsj.webserver.service.MainService;

import java.util.ArrayList;
import java.util.List;

@Service
public class MainServiceImpl implements MainService {

    private static Logger logger = Logger.getLogger(MainServiceImpl.class);

    @Autowired
    private MainMapper mainMapper;

    @Autowired
    private LoginMapper loginMapper;

    @Override
    public void addSection(Section section) {
        loginMapper.insertSection(section);
    }

    /**
     * 获取好友的所有联系人信息
     *
     * @param id 当前好友
     * @return
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<List<SectionData>> acquireFriendRelationships(Long id) {
        List<List<SectionData>> result = new ArrayList<>();
        // 用户分组数据
        List<SectionData> sectionData = getUserSectionData(id);
        result.add(sectionData);
        // 群组分组数据
        List<SectionData> sectionDataGroup = getGroupSectionData(id);
        result.add(sectionDataGroup);

        return result;
    }

    /**
     * 获取群分组数据
     * @param id
     * @return
     */
    @Override
    public List<SectionData> getGroupSectionData(Long id){
        List<Section> groupSections = mainMapper.listGroupSection(id);
        List<SectionData> sectionDataGroup = new ArrayList<>();
        if (null != groupSections) {
            for (Section section : groupSections) {
                List<GroupData> sectionGroups = mainMapper.listSectionGroupMember(section.getId());
                sectionDataGroup.add(new SectionData(section, sectionGroups));
            }
        } else {
            logger.warn("group section is null");
        }
        return sectionDataGroup;
    }

    @Override
    public List<SectionData> getUserSectionData(Long id){
        List<Section> userSections = mainMapper.listUserSection(id);
        List<SectionData> sectionData = new ArrayList<>();
        if (null != userSections) {
            for (Section section : userSections) {
                logger.warn(section);
                List<UserData> sectionUsers = mainMapper.listSectionUserMember(section.getId());
                sectionData.add(new SectionData(section, sectionUsers));
            }
        } else {
            logger.warn("user sections is null");
        }
        return sectionData;
    }

    /**
     * 删除分组
     * @param deleteSectionId   删除的分组id
     * @param toSectionId   删除分组内的item需要移动到的分组的id
     * @param type true-群分组  false-好友分组
     */
    @Override
    @Transactional
    public void deleteSection(Long deleteSectionId, Long toSectionId, Boolean type) {
        // 1. 先将分组内的成员移动到其他分组.
        List<? extends BaseData> data = null;
        // 群分组
        if(type){
            data = mainMapper.listSectionGroupMember(deleteSectionId);
            for(BaseData baseData : data){
                mainMapper.updateGroupBelongSection(baseData.getId(),deleteSectionId,toSectionId);
            }
        }
        else{ // 好友分组
            data = mainMapper.listSectionUserMember(deleteSectionId);
            for(BaseData baseData : data){
                mainMapper.updateUserBelongSection(baseData.getId(),deleteSectionId,toSectionId);
            }
        }
        // 2. 删除分组
        mainMapper.deleteSection(deleteSectionId);
    }


    @Override
    public void moveSectionItem(Long fromSectionId, Long toSectionId, Long objectId, Boolean type) {
        if(type){
            mainMapper.updateGroupBelongSection(objectId,fromSectionId,toSectionId);
        }
        else{
            mainMapper.updateUserBelongSection(objectId,fromSectionId,toSectionId);
        }
    }
}

package top.zsj.webserver.service;

import top.zsj.webserver.domain.Section;
import top.zsj.webserver.domain.SectionData;

import java.util.List;

public interface MainService {


    void addSection(Section section);


    List<List<SectionData>> acquireFriendRelationships(Long id);


    void deleteSection(Long deleteSectionId, Long toSectionId, Boolean type);

    List<SectionData> getGroupSectionData(Long id);

    List<SectionData> getUserSectionData(Long id);

    void moveSectionItem(Long fromSectionId, Long toSectionId, Long objectId, Boolean type);


    void addFriend(Long fromId,Long toId);

}

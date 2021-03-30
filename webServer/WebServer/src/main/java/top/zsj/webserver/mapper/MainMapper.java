package top.zsj.webserver.mapper;


import org.apache.ibatis.annotations.*;
import top.zsj.webserver.domain.GroupData;
import top.zsj.webserver.domain.Section;
import top.zsj.webserver.domain.UserData;

import java.util.List;

public interface MainMapper {

    /**
     * 根据id查询用户分组
     * @param belong 用户账号
     * @return
     */
    @Select("select * from t_section where s_belong = #{belong} and s_type = 0;")
    @Results(id = "sectionMap",value = {
            @Result(property = "id",column = "s_id"),
            @Result(property = "sectionName",column = "s_section_name"),
            @Result(property = "belong",column = "s_belong"),
            @Result(property = "size",column = "s_size"),
            @Result(property = "type",column = "s_type")
    })
    List<Section> listUserSection(@Param("belong") Long belong);

    /**
     * 根据id查询群组分组
     * @param belong 用户账号
     * @return
     */
    @Select("select * from t_section where s_belong = #{belong} and s_type = 1;")
    @ResultMap("sectionMap")
    List<Section> listGroupSection(@Param("belong") Long belong);

    /**
     * 根据用户分组id查询分组成员
     * @param id
     * @return
     */
    @Select("select * from t_user where u_id in (select u_id from r_section_user as tsu where tsu.s_id=#{id});")
    @Results(id = "userDataMap",value = {
            @Result(property = "id",column = "u_id"),
            @Result(property = "nickname",column = "u_nickname"),
            @Result(property = "head",column = "u_head"),
            @Result(property = "password",column = "u_password"),
            @Result(property = "signature",column = "u_signature"),
            @Result(property = "level",column = "u_level"),
            @Result(property = "vip",column = "u_is_vip")
    })
    List<UserData> listSectionUserMember(Long id);

    /**
     * 根据群组分组id查询分组成员
     * @param id
     * @return
     */
    @Select("select * from t_group where g_id in (select g_id from r_section_group as tsg where tsg.s_id=#{id});")
    @Results(id = "groupDataMap",value = {
            @Result(property = "id",column = "g_id"),
            @Result(property = "nickname",column = "g_nickname"),
            @Result(property = "head",column = "g_head"),
            @Result(property = "introduce",column = "g_introduce"),
            @Result(property = "belong",column = "g_belong"),
            @Result(property = "maxSize",column = "g_max_size"),
            @Result(property = "currentNum",column = "g_cur_num"),
            @Result(property = "vip",column = "g_is_vip")
    })
    List<GroupData> listSectionGroupMember(Long id);


    /**
     * 插入用户分组成员
     * @param sectionId  分组id
     * @param memberId  成员id
     */
    @Insert("insert into r_section_user values(#{sId},#{mId});")
    void insertUserSectionMember(@Param("sId") Long sectionId, @Param("mId") Long memberId);

    /**
     * 插入群组分组成员
     * @param sectionId 分组id
     * @param memberId 成员id
     */
    @Insert("insert into r_section_group values(#{sId},#{mId});")
    void insertGroupSectionMember(@Param("sId") Long sectionId, @Param("mId") Long memberId);


    /**
     * 删除分组
     * @param id
     */
    @Delete("delete from t_section where s_id = #{id};")
    void deleteSection(@Param("id") Long id);


    /**
     * 移动好友到不同好友分组
     * @param userId
     * @param oldSectionId
     * @param newSectionId
     */
    @Update("update r_section_user set s_id = #{newSectionId} where s_id = #{oldSectionId} and u_id = #{userId};")
    void updateUserBelongSection(@Param("userId") Long userId,
                                 @Param("oldSectionId") Long oldSectionId,@Param("newSectionId") Long newSectionId);

    /**
     * 移动群组到不同群组分组
     * @param groupId
     * @param oldSectionId
     * @param newSectionId
     */
    @Update("update r_section_group set s_id = #{newSectionId} where s_id = #{oldSectionId} and g_id = #{groupId};")
    void updateGroupBelongSection(@Param("groupId") Long groupId,
                                 @Param("oldSectionId") Long oldSectionId,@Param("newSectionId") Long newSectionId);


    @Select("select s_id where t_section where s_belong=#{belong} and s_section_name=#{sectionName}")
    Long findSectionByBelongAndName(@Param("belong")Long belong,@Param("sectionName")String sectionName);


    @Update("update t_section set s_size = s_size + #{count} where s_id = #{sectionId};")
    void increaseSectionSize(@Param("sectionId")Long sectionId,@Param("count")int count);

    @Update("update t_section set s_size = s_size - #{count} where s_id = #{sectionId};")
    void decreaseSectionSize(@Param("sectionId")Long sectionId,@Param("count")int count);
}

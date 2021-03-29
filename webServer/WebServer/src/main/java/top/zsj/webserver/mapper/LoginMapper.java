package top.zsj.webserver.mapper;

import org.apache.ibatis.annotations.*;
import top.zsj.webserver.domain.GroupData;
import top.zsj.webserver.domain.UserData;
import top.zsj.webserver.domain.Section;

public interface LoginMapper {

    /**
     * 登录
     * @param id 账号
     * @param password 密码
     * @return 登录成功返回用户信息，失败返回null
     */
    @Select("select * from t_user where u_id=#{id} and u_password=#{password};")
    @Results(id = "userDataMap",value = {
            @Result(property = "id",column = "u_id"),
            @Result(property = "nickname",column = "u_nickname"),
            @Result(property = "head",column = "u_head"),
            @Result(property = "password",column = "u_password"),
            @Result(property = "signature",column = "u_signature"),
            @Result(property = "level",column = "u_level"),
            @Result(property = "vip",column = "u_is_vip")
    })
    UserData login(@Param("id") Long id, @Param("password") String password);

    /**
     * 添加用户
     * @param user 用户
     * @return 是否插入成功
     */
    @Insert("insert into t_user(u_nickname,u_head,u_password,u_signature,u_level,u_is_vip)" +
            " values(#{user.nickname},#{user.head},#{user.password},#{user.signature},#{user.level},#{user.vip});")
    @ResultMap("userDataMap")
    @Options(useGeneratedKeys=true, keyProperty="user.id",keyColumn = "u_id")
    Integer insertUser(@Param("user") UserData user);


    /**
     * 添加分组
     * @param section   分组
     * @return 分组id
     */
    @Insert("insert into t_section(s_section_name,s_belong,s_size,s_type) " +
            "values(#{section.sectionName},#{section.belong},#{section.size},#{section.type});")
    @Results(id = "sectionMap",value = {
            @Result(property = "id",column = "s_id"),
            @Result(property = "sectionName",column = "s_section_name"),
            @Result(property = "belong",column = "s_belong"),
            @Result(property = "size",column = "s_size"),
            @Result(property = "type",column = "s_type")
    })
    @Options(useGeneratedKeys=true, keyProperty="section.id",keyColumn = "s_id")
    Integer insertSection(@Param("section") Section section);

    @Insert("insert into t_group(g_nickname,g_head,g_introduce,g_belong,g_max_size,g_cur_num,g_is_vip) " +
            "values(#{group.nickname},#{group.head},#{group.introduce},#{group.belong},#{group.maxSize},#{group.currentNum},#{group.vip});")
    @Results(id = "groupDataMap",value = {
            @Result(property = "id",column = "g_id"),
            @Result(property = "nickname",column = "g_nickname"),
            @Result(property = "head",column = "g_head"),
            @Result(property = "introduce",column = "g_introduce"),
            @Result(property = "belong",column = "g_belong"),
            @Result(property = "maxSize",column = "g_maxSize"),
            @Result(property = "currentNum",column = "g_currentNum"),
            @Result(property = "vip",column = "g_is_vip")
    })
    @Options(useGeneratedKeys=true, keyProperty="group.id",keyColumn = "g_id")
    void insertGroup(@Param("group") GroupData group);
}

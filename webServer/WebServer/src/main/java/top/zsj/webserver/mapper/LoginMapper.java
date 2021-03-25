package top.zsj.webserver.mapper;

import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Result;
import org.apache.ibatis.annotations.Results;
import org.apache.ibatis.annotations.Select;
import top.zsj.webserver.domain.User;

public interface LoginMapper {

    @Select("select * from t_user where u_id=#{id} and u_password=#{password};")
    @Results(id = "userMap",value = {
            @Result(property = "id",column = "u_id"),
            @Result(property = "nickname",column = "u_nickname"),
            @Result(property = "head",column = "u_head"),
            @Result(property = "password",column = "u_password"),
            @Result(property = "signature",column = "u_signature"),
            @Result(property = "level",column = "u_level"),
            @Result(property = "vip",column = "u_vip")
    })
    User login(@Param("id") Integer id,@Param("password") String password);
}

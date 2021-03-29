package top.zsj.webserver.service;

import top.zsj.webserver.domain.UserData;

public interface LoginService {

    public UserData login(Long id, String password);


    /**
     * 注册用户
     * @param user
     * @return 新用户数据
     */
    UserData registerUser(UserData user);
}

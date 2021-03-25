package top.zsj.webserver.service;

import top.zsj.webserver.domain.User;

public interface LoginService {

    public User login(Integer id, String password);
}

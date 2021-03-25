package top.zsj.webserver.service.impl;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import top.zsj.webserver.domain.User;
import top.zsj.webserver.mapper.LoginMapper;
import top.zsj.webserver.service.LoginService;


@Service
public class LoginServiceImpl implements LoginService {

    @Autowired
    LoginMapper loginMapper;

    @Override
    public User login(Integer id, String password) {
        return loginMapper.login(id, password);
    }
}

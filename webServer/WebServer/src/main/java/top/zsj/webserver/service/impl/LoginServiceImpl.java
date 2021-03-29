package top.zsj.webserver.service.impl;

import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import top.zsj.webserver.domain.UserData;
import top.zsj.webserver.domain.Section;
import top.zsj.webserver.mapper.LoginMapper;
import top.zsj.webserver.service.LoginService;


@Service
public class LoginServiceImpl implements LoginService {

    private static Logger logger = Logger.getLogger(LoginServiceImpl.class);

    @Autowired
    LoginMapper loginMapper;

    @Override
    public UserData login(Long id, String password) {
        return loginMapper.login(id, password);
    }


    @Override
//    @Transactional(rollbackFor = Exception.class)
    public UserData registerUser(UserData user)  {

        // 插入用户数据
        loginMapper.insertUser(user);
        Long id = user.getId();
        logger.info("id = " + id);
        Section sectionGroup = new Section(0L,"我的群组",id,0,true);
        Section sectionUser = new Section(0L,"我的好友",id,0,false);
        // 插入群分组数据
        loginMapper.insertSection(sectionGroup);
        // 插入好友分组
        loginMapper.insertSection(sectionUser);
        return user;
    }
}

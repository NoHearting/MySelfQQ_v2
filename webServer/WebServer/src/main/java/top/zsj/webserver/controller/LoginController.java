package top.zsj.webserver.controller;


import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import top.zsj.webserver.domain.LoginData;
import top.zsj.webserver.domain.User;
import top.zsj.webserver.domain.response.ResponseResult;
import top.zsj.webserver.domain.response.ResultCode;
import top.zsj.webserver.service.LoginService;

@RestController
public class LoginController {

    private static Logger logger = Logger.getLogger(LoginController.class);

    @Autowired
    LoginService loginService;

    @ResponseBody
    @RequestMapping(value = "/login", method = RequestMethod.POST)
    public ResponseResult login(@RequestBody LoginData data) {
        logger.info("id=" + data.getId() + "  password=" + data.getPassword());
        User user = loginService.login(data.getId(), data.getPassword());
        ResponseResult result;
        logger.warn(user);
        if(null != user){
            result = new ResponseResult(ResultCode.SUCCESS, "user", user);
        }
        else{
            result = ResponseResult.exception("账号或者密码错误");
        }
        return result;
    }



}

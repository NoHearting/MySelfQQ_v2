package top.zsj.webserver.controller;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;
import top.zsj.webserver.domain.User;
import top.zsj.webserver.domain.response.ResponseResult;
import top.zsj.webserver.domain.response.ResultCode;
import top.zsj.webserver.service.LoginService;

@RestController
public class LoginController {

    @Autowired
    LoginService loginService;

    @ResponseBody
    @RequestMapping(value = "/login", method = RequestMethod.POST)
    public ResponseResult login(Integer id, String password) {
        User user = loginService.login(id, password);
        ResponseResult result = new ResponseResult(ResultCode.SUCCESS, "user", user);
        result.addData("test", 1111);
        return result;
    }
}

package top.zsj.webserver.controller;


import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import top.zsj.webserver.domain.LoginData;
import top.zsj.webserver.domain.UserData;
import top.zsj.webserver.domain.response.ResponseResult;
import top.zsj.webserver.domain.response.ResultCode;
import top.zsj.webserver.service.LoginService;

@RestController
public class LoginController {

    private static String defaultHead = "http://120.78.223.0/group1/M00/00/00/rBAxBWBdhZiAVnVTAAC2-_QY7Ek837.jpg";
    private static Logger logger = Logger.getLogger(LoginController.class);

    @Autowired
    LoginService loginService;

    @ResponseBody
    @RequestMapping(value = "/login", method = RequestMethod.POST)
    public ResponseResult login(@RequestBody LoginData data) {
        logger.info("id=" + data.getId() + "  password=" + data.getPassword());
        UserData user = loginService.login(data.getId(), data.getPassword());
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


    @ResponseBody
    @PostMapping("registerLogic")
    public ResponseResult register(@RequestBody String data){
        logger.info(data);
        JSONObject jsonObject = JSON.parseObject(data);
        String nickname = (String)jsonObject.get("nickname");
        String password = (String)jsonObject.get("password");
        logger.info("nickname=" + nickname + "  password="+password);
        if(nickname == null || password == null){
            return new ResponseResult(ResultCode.PARAM_ERROR);
        }
        UserData user = new UserData(nickname,defaultHead,password,"",1,false);
        UserData resultUser = loginService.registerUser(user);

        ResponseResult result = null;
        if(resultUser != null){
            result = ResponseResult.success("注册账号成功");
            result.addData("user",resultUser);
        }
        else {
            result = ResponseResult.exception("注册账号失败");
        }
        return result;
    }

    /**
     * 找回密码
     * @return
     * @Note 后续完善此逻辑
     */
    @RequestMapping("/findPassword")
    public ResponseResult findPassword(){
        return new ResponseResult(ResultCode.SUCCESS);
    }

}

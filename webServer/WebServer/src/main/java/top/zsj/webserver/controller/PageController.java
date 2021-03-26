package top.zsj.webserver.controller;


import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class PageController {

    @RequestMapping("/updatePassword")
    public String updatePasswod(){
        return "page/find-password.html";
    }

    @RequestMapping("/register")
    public String register(){
        return "page/register.html";
    }

}

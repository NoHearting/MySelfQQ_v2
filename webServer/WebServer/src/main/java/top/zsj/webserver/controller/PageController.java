package top.zsj.webserver.controller;


import org.apache.log4j.Logger;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;


@Controller
public class PageController {

    private static Logger logger = Logger.getLogger(PageController.class);

    @RequestMapping("register")
    public String register(){
        logger.info("register");
        return "page/register-pwd.html";
    }

    @RequestMapping("success")
    public ModelAndView success(String nickname,Long id){
        ModelAndView mav = new ModelAndView();
        mav.setViewName("page/success.html");
        mav.addObject("nickname",nickname);
        mav.addObject("id",id);
        return mav;
    }

}

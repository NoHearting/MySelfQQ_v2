package top.zsj.webserver.controller;


import com.alibaba.fastjson.JSONObject;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import top.zsj.webserver.domain.Section;
import top.zsj.webserver.domain.SectionData;
import top.zsj.webserver.domain.response.ResponseResult;
import top.zsj.webserver.domain.response.ResultCode;
import top.zsj.webserver.service.LoginService;
import top.zsj.webserver.service.MainService;

import java.util.List;

@RestController
public class MainController {
    private static Logger logger = Logger.getLogger(LoginController.class);

    @Autowired
    private LoginService loginService;

    @Autowired
    private MainService mainService;

    /**
     * 添加分组
     * @param section
     * @return
     */
    @PostMapping("addSection")
    public ResponseResult addSection(@RequestBody Section section) {
        mainService.addSection(section);
        return new ResponseResult(ResultCode.SUCCESS);
    }

    /**
     * 删除分组
     * @param data
     * @return
     */
    @PostMapping("deleteSection")
    public ResponseResult deleteSection(@RequestBody String data){
        JSONObject jsonObject = JSONObject.parseObject(data);
        Long deleteSectionId = jsonObject.getLong("deleteSectionId");
        Long toSectionId = jsonObject.getLong("toSectionId");
        Boolean type = jsonObject.getBoolean("type");     // 删除群分组还是用户分组 true-群分组  false-用户分组
        mainService.deleteSection(deleteSectionId,toSectionId,type);
        return ResponseResult.success("删除分组成功");
    }


    /**
     * 移动分组
     * @param data
     * @return
     */
    @PostMapping("moveSectionItem")
    public ResponseResult moveSectionItem(@RequestBody String data){
        JSONObject jsonObject = JSONObject.parseObject(data);
        Long fromSectionId = jsonObject.getLong("fromSectionId");
        Long toSectionId = jsonObject.getLong("toSectionId");
        Long objectId = jsonObject.getLong("objectId");
        Boolean type = jsonObject.getBoolean("type");
        mainService.moveSectionItem(new Long(fromSectionId),new Long(toSectionId),new Long(objectId),type);
        return ResponseResult.success("移动分组成功");
    }

    /**
     * 加好友请求
     * @param data
     * @return
     */
    @PostMapping("addFriendRequest")
    public ResponseResult addFriendRequest(@RequestBody String data){
        // todo
        return ResponseResult.success("请求添加好友成功");
    }

    /**
     * 确认添加好友
     * @param data
     * @return
     */
    @PostMapping("addFriendSure")
    public ResponseResult addFriendSure(@RequestBody String data){
        // todo
        return ResponseResult.success("添加好友成功");
    }

    /**
     * 添加好友
     * @param data
     * @return
     * @note 目前功能不完善，使用此接口
     */
    @PostMapping("addFriend")
    public ResponseResult addFriend(@RequestBody String data){
        JSONObject jsonObject = JSONObject.parseObject(data);
        Long fromId = jsonObject.getLong("fromId");
        Long toId = jsonObject.getLong("toId");
        mainService.addFriend(fromId,toId);
        return ResponseResult.success("添加好友成功");
    }


    /**
     * 好友、群列表
     * @param id
     * @return
     */
    @GetMapping("friendRelationship")
    public ResponseResult getFriendRelationship(Long id) {
        List<List<SectionData>> relationships = mainService.acquireFriendRelationships(id);
        ResponseResult result = new ResponseResult(ResultCode.SUCCESS);
        result.addData("relationship",relationships);
        return result;
    }

    /**
     * 用户分组数据
     * @param id
     * @return
     */
    @GetMapping("userSection")
    public ResponseResult getUserSectionData(Long id){
        List<SectionData> userSectionData = mainService.getUserSectionData(id);
        return ResponseResult.success("用户分组数据").addData("userSection",userSectionData);
    }

    /**
     * 群组分组数据
     * @param id
     * @return
     */
    @GetMapping("groupSection")
    public ResponseResult getGroupSectionData(Long id){
        List<SectionData> groupSectionData = mainService.getGroupSectionData(id);
        return ResponseResult.success("群组分组数据").addData("groupSection",groupSectionData);
    }

}

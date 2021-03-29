package top.zsj.webserver;

import org.apache.log4j.Logger;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import top.zsj.webserver.domain.GroupData;
import top.zsj.webserver.domain.Section;
import top.zsj.webserver.domain.UserData;
import top.zsj.webserver.mapper.LoginMapper;
import top.zsj.webserver.mapper.MainMapper;

import java.util.ArrayList;
import java.util.List;


@SpringBootTest
class WebServerApplicationTests {

	private static Logger logger = Logger.getLogger(WebServerApplicationTests.class);
	private static String defaultHead = "http://120.78.223.0/group1/M00/00/00/rBAxBWBdhZiAVnVTAAC2-_QY7Ek837.jpg";
	@Autowired
	private LoginMapper loginMapper;

	@Autowired
	private MainMapper mainMapper;

    Long ids = 0L;

    List<UserData> listUser = new ArrayList<>();
    List<Section>  sectionGroupList = new ArrayList<>();
    List<Section>  sectionUserList = new ArrayList<>();
    List<GroupData> listGroup = new ArrayList<>();
	@Test
	void contextLoads() {


	}


	@Test
	void testLog4j(){
		logger.debug("debug info");
		logger.info("info info");
		logger.warn("warn info");
		logger.error("error info");
		logger.fatal("fatal error");
	}


	@Test
	void testAddUserInfo(){

		Long id = 0L;
		listUser.add(new UserData(id,"重邮青年志愿者",defaultHead,"1","",42,true));
        listUser.add(new UserData(id,"Ariel",defaultHead,"1","称为可以着凉这个世界的大人吧",60,true));
        listUser.add(new UserData(id,"SpaceTime",defaultHead,"1","用梦想整改时空！",93,true));
        listUser.add(new UserData(id,"SnowShine",defaultHead,"1","",86,true));
        listUser.add(new UserData(id,"Deceive",defaultHead,"1","我也有失眠的时候啊",73,true));
        listUser.add(new UserData(id,"defis",defaultHead,"1","早睡早起，规律作息，坚持运动。。。",83,true));
        listUser.add(new UserData(id,"卐卍",defaultHead,"1","",65,true));
        listUser.add(new UserData(id,"Dean",defaultHead,"1","三人秋千，瑶瑶晃晃在我心中",75,false));
        listUser.add(new UserData(id,"忧国忧民",defaultHead,"1","",50,true));
        listUser.add(new UserData(id,"芋泥波波奶茶",defaultHead,"1","",74,true));

        Long key = 0L;
        List<Long> keys = new ArrayList<>();
        for(UserData user : listUser){
            loginMapper.insertUser(user);
            key = user.getId();
            keys.add(key);
        }
        for(Long v : keys){
            addFriendAndSection(v);
        }


	}


    /**
     * 添加好友、添加分组、添加群分组、创建群
     * @param belong 用户id
     */
	void addFriendAndSection(Long belong){
	    sectionUserList.clear();
	    sectionGroupList.clear();
	    // 先添加分组
        Long id = 0L;
        sectionUserList.add(new Section(id,"小学",belong,0,false));
        sectionUserList.add(new Section(id,"初中",belong,0,false));
        sectionUserList.add(new Section(id,"高中",belong,0,false));
        sectionUserList.add(new Section(id,"大学",belong,0,false));
        int index = 0;
        // 添加用户分组
        for(Section section : sectionUserList){
            loginMapper.insertSection(section);
            // 为每个用户分组添加2个成员
            for(int i = 0;i<2;i++)
            {
                Long sId = section.getId();
                Long uId= listUser.get(index).getId();
                logger.info(sId + ":" + uId + " - index:" + index);

                mainMapper.insertUserSectionMember(sId,uId);
                index++;
            }
        }

        sectionGroupList.add(new Section(id,"置顶群聊",belong,0,true));
        sectionGroupList.add(new Section(id,"我创建的群聊",belong,0,true));
        sectionGroupList.add(new Section(id,"我管理的群聊",belong,0,true));
        sectionGroupList.add(new Section(id,"我加入的群聊",belong,0,true));
        // 添加群组分组
        for(Section section : sectionGroupList){
            loginMapper.insertSection(section);
        }

        createGroup(belong);
    }

    /**
     * 创建群组
     * @param id  用户id
     */
    void createGroup(Long id){
	    Long ids = 0L;
	    listGroup.clear();
	    listGroup.add(new GroupData(ids,"sylar技术群",defaultHead,"无介绍",id,100,1,false));
        listGroup.add(new GroupData(ids,"2017级计科专业",defaultHead,"无介绍",id,100,1,false));
        listGroup.add(new GroupData(ids,"重邮限制买卖互助群",defaultHead,"无介绍",id,100,1,false));
        listGroup.add(new GroupData(ids,"京东科技未来之星",defaultHead,"无介绍",id,100,1,false));

        // 将群全部添加到 “我创建的群聊”中去
        for(GroupData group : listGroup){
            loginMapper.insertGroup(group);
            mainMapper.insertGroupSectionMember(sectionGroupList.get(1).getId(),group.getId());
        }
	}



	@Test
	void testInsertUser(){
        listUser.add(new UserData(ids,"重邮青年志愿者",defaultHead,"1","",42,true));
        listUser.add(new UserData(ids,"Ariel",defaultHead,"1","称为可以着凉这个世界的大人吧",60,true));
        listUser.add(new UserData(ids,"SpaceTime",defaultHead,"1","用梦想整改时空！",93,true));
        listUser.add(new UserData(ids,"SnowShine",defaultHead,"1","",86,true));
        listUser.add(new UserData(ids,"Deceive",defaultHead,"1","我也有失眠的时候啊",73,true));
        listUser.add(new UserData(ids,"defis",defaultHead,"1","早睡早起，规律作息，坚持运动。。。",83,true));
        listUser.add(new UserData(ids,"卐卍",defaultHead,"1","",65,true));
        listUser.add(new UserData(ids,"Dean",defaultHead,"1","三人秋千，瑶瑶晃晃在我心中",75,false));
        listUser.add(new UserData(ids,"忧国忧民",defaultHead,"1","",50,true));
        listUser.add(new UserData(ids,"芋泥波波奶茶",defaultHead,"1","",74,true));
        for(UserData user : listUser){
            loginMapper.insertUser(user);
        }
    }

	@Test
	void testInsertGroup(){

        GroupData group = new GroupData(ids,"sylar技术群",defaultHead,"无介绍",1L,100,1,false);
        loginMapper.insertGroup(group);
        logger.info(group.getId());
    }

    @Test
    void testInsetSectionGroup(){
        Section section  = new Section(ids,"置顶群聊",1L,0,true);
        loginMapper.insertSection(section);
        logger.info(section.getId());
    }

    @Test
    void testInsertSectionUser(){
        Section section =new Section(ids,"小学",1L,0,false);
        loginMapper.insertSection(section);
        logger.info(section.getId());
    }

    @Test
    void testInsertSectionUserMember(){
        mainMapper.insertUserSectionMember(2L,3L);
    }

    @Test
    void testInsertSectionGroupMember(){
        mainMapper.insertGroupSectionMember(1L,1L);
    }


    @Test
    void testListUsetSection(){
        Long belong = 1L;
        List<Section> sections = mainMapper.listUserSection(belong);
        logger.info(sections);
    }

    @Test
    void testDeleteSection(){
        mainMapper.deleteSection(1L);
    }
}

/**
  * @brief 保存全局静态不可变的变量
  *  一般保存图片路径、文件路径
  * @author zsj
  * @date  2021年1月6日19:54:29
  */
#ifndef GLOBAL_H
#define GLOBAL_H

#include <QIcon>

namespace zsj {

namespace global {

/**
 * @brief 数据类型
 */
enum class DataType{
    USER_DATA = 0,
    GROUP_DATA = 1,
    SYSTEM_DATA = 2
};

/**
 * @brief 消息输入窗口ui类型
 * @note 消息输入窗口有两套UI，群组和用户
 *  因为两套UI有共享的数据，所以在设置一些参数时需要分类
 */
enum class UiType{
    USER = 0,
    GROUP
};

/**
 * @brief 消息的类型
 */
enum class MessageType{
    TEXT = 0,       /// 文本
    IMAGE,          /// 图片
    FILE,           /// 文件
    AUDIO,          /// 音频
    VIDEO           /// 视频
};




/// 默认的菜单项的透明icon的路径，为了对齐菜单项
/// 如果一些菜单有icon，一些没有，则菜单项文字对不齐
const static QString TransparentMenuIconPath =":/main/res/main/transparent.png";

/// 默认头像路径
const static QString DefaultHead = ":/global/res/global/default-head.png";

/// 最外层窗口和内层内容窗口之间的padding
const static int TopLayoutPadding = 9;

/// 截屏保存的文件夹名称
const static QString ScreenShotDirName = "screen_shot";


}




}


#endif // GLOBAL_H

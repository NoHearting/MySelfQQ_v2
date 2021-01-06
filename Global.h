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

/// 默认的菜单项的透明icon的路径，为了对齐菜单项
/// 如果一些菜单有icon，一些没有，则菜单项文字对不齐
const static QString transparentMenuIconPath =":/main/res/main/transparent.png";


}




}


#endif // GLOBAL_H

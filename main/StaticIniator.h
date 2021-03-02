/**
  * @brief 静态初始化器，用于初始化静态的布局，不可改的对象，资源
  *
  * @author zsj
  * @date 2020年12月25日19:13:45
  */
#ifndef STATICINIATOR_H
#define STATICINIATOR_H


#include <QScopedPointer>
#include <QMenu>
#include <QWidget>
#include <QObject>

namespace zsj{

class StaticIniator : public QObject
{
    Q_OBJECT
public:
    static StaticIniator * Instance();
public:

    void initFirendMenu(QMenu * menu,QWidget * owner);
    void initFirendSectionMenu(QMenu * menu,QWidget * owner);
    void initGroupMenu(QMenu * menu,QWidget * owner);
    void initGroupSectionMenu(QMenu * menu,QWidget * owner);

    void initMenusStyle(QMenu * menu);


    /// @brief 初始化聊天窗口的发送选项菜单
    void initSendMenu(QMenu * menu,QWidget * owner);

private:
    StaticIniator(){}

    static QScopedPointer<StaticIniator> staticIniator;
};

}



#endif // STATICINIATOR_H

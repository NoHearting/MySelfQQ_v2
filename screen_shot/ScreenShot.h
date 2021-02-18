#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <QSharedPointer>
#include <QRect>
#include <QPixmap>
#include <QTimer>
#include <QMenu>

#include "Amplifier.h"

typedef QSharedPointer<QPixmap> pixPtr;

namespace zsj {



class Screen;
class Rect;

class ScreenShot : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenShot(QWidget *parent = nullptr);


    /**
     * @brief 窗口实例
     * @return 返回ScreenShot实例指针
     */
    static ScreenShot *Instance();

    /**
     * @brief 销毁截图窗口
     */
    static void Destory();

protected:
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

#ifdef Q_OS_WIN
    /**
     * @brief 更新当前鼠标选取的窗口
     */
    void updateMouse();
#endif

private:
    /**
     * @brief 初始化放大镜，色彩采集器。需要屏幕的原画作为放大器的放大元素
     * @param originPainting 放大器的放大的原画图片
     * @note 需要先获取屏幕的原画
     */
    void initAmplifier(pixPtr originPainting = nullptr);

    /**
     * @brief 测量控件，大小感知器
     */
    void initMeasureWidget();

    /**
     * @brief 初始化截屏背景
     * @return QSharedPointer<QPixmap> 经过暗色处理的屏幕图
     */
    pixPtr initGlobalScreen();

    /**
     * @brief 初始化鼠标图标，为鼠标设置默认状态下的图标样式
     * @param ico 鼠标图片的资源文件路径
     * @remark 如果未设置图标路径则采用默认的鼠标logo
     */
    void initCursor(const QString &ico = "");

    /**
     * @brief 创建截图器，若截图器实例存在则直接返回不会重复创建
     * @param pos 截图器的起始位置
     * @return 截图器实例
     * @remark 创建截图器前，需要创建相关的组件
     */
    QSharedPointer<Screen> createScreen(const QPoint &pos);


    /**
     * @brief 销毁截图器。若截图器存在则销毁实例并清理相关资源
     */
    void destoryScreen();

    /**
     * @brief 获得当前屏幕的大小
     * @return 返回屏幕大小
     * @note 这个函数是支持多屏幕的。双屏幕 QRect（-1920,0,3840,1080）
     */
    const QRect &getScreenRect();

    /**
     * @brief 获得当前桌面原画
     * @return QSharedPointer<QPixmap> 桌面原画
     * @note 不会重复获得，如果有，则直接返回。若想重新获得屏幕原画，则需要清理原有资源
     */
    pixPtr getGlobalScreen();

private:
    /// 截屏窗口是否已经展示
    bool isLeftPresssed;
    /// 用于检测误操作
    QPoint startPoint;
    /// 当前桌面屏幕的矩形数据
    QRect desktopRect;
    /// 屏幕暗色背景图
    pixPtr backgroundScreen;
    /// 屏幕原画
    pixPtr originPainting;
    /// 截图屏幕
    QSharedPointer<Screen> pScreen;
    /// 截图器大小感知器
    QSharedPointer<Rect> pRect;
    /// 放大取色器
    QSharedPointer<Amplifier> pAmplifier;
    /// 当前鼠标选取最小的矩形窗口
    QRect windowRect;

    /// 截屏实例对象
    static ScreenShot * Self;
    /// 活动窗口
    static bool IsActivity;
    /// 置顶定时器
    QTimer * egoisticTimer;
signals:
    /**
     * @brief 鼠标移动信号
     * @param int x轴坐标
     * @param int y轴坐标
     */
    void sigCursorPosChange(int, int);


    /**
     * @brief 鼠标双击信号
     */
    void sigDoubleClick();

    /**
     * @brief 鼠标当前位置最小的子窗口
     * @param QRect 当前窗口的矩形数据
     */
    void sigFindChildWindow(QRect);

public slots:
private slots:
    /**
     * @brief window下置顶
     * @remark 使用该函数时，会中止右键菜单行为。
     */
    void slotEgoistic();
};







class Rect : public QWidget{
    Q_OBJECT
public:
    explicit Rect(QWidget * widget = nullptr);

protected:
    void paintEvent(QPaintEvent *event);

public slots:
    /**
     * @brief 外部组件位置修改
     * @param xPos 横向位置
     * @param yPos  纵向位置
     */
    void slotPositionChange(int xPos,int yPos);

    /**
     * @brief 外部组件位置修改
     * @param width 宽度
     * @param height 高度
     * @note 感知器修改显示的大小数据
     */
    void slotSizeChange(int width,int height);

private:
    /// 背景色
    pixPtr backgroundPixmap;
    /// 显示的文字信息
    QString info;
};

/**
 * @brief 截图器
 * @note 主要关于图片的编辑与保存
 */
class Screen : public QWidget{
    Q_OBJECT
signals:
    /**
     * @brief 截图器大小修改
     * @param int 宽度
     * @param int 高度
     */
    void sigSizeChange(int,int);


    /**
     * @brief 截图器窗口的位置
     * @param int 窗口的横向位置
     * @param int 窗口的纵向位置
     */
    void sigPositionChange(int,int);

    /**
     * @brief 双击
     */
    void sigDoubleClick();

protected:
    /// 内边距，决定拖拽的触发
    const int PADDING = 6;

    /// 方位枚举
    enum DIRECTION{
        TOP = 0,
        BOTTOM = 1,
        LEFT,
        RIGHT,
        LEFT_TOP,
        LEFT_BOTTOM,
        RIGHT_TOP,
        RIGHT_BOTTOM,
        NONE
    };
public:
    explicit Screen(pixPtr originPainting,QPoint pos,QWidget*parent = nullptr);
    ~Screen(){IsInit = false;}


    static bool State(){return IsInit;}

    QRect getCurrentRect() const;
    void setCurrentRect(const QRect &value);

protected:
    /**
     * @brief 获得当前坐标点的边界方位
     * @param cursor 当前鼠标的位置
     * @return 鼠标的方位
     */
    DIRECTION getRegion(const QPoint & cursor);

    /**
     * @brief 呼出菜单事件
     */
    void contextMenuEvent(QContextMenuEvent *);

    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void moveEvent(QMoveEvent *event);
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    /**
     * @brief 获得一个以时间格式命名的文件名
     * @return QString 文件名
     */
    const QString getFileName();

public slots:
    /**
     * @brief 根据鼠标位置修改窗口
     * @param xPos 鼠标的横向位置
     * @param yPos 鼠标的纵向位置
     */
    void slotMouseChange(int xPos,int yPos);

    /**
     * @brief 保存屏幕到剪切板中
     */
    void slotSaveScreen();

protected slots:
    /**
     * @brief 将截图另存为
     */
    void slotSaveScreenOther();

    /**
     * @brief 退出当前截图窗口
     */
    void slotQuitScreenShot();

protected:
    /// 是否已经设置初始大小
    static bool IsInit;
    /// 窗口大小改变时，记录改变方向
    DIRECTION direction;
    /// 起点
    QPoint originPoint;
    /// 鼠标是否按下
    bool isPressed;
    /// 拖动的距离
    QPoint movePos;
    /// 标记锚点
    QPolygon listMarker;
    /// 屏幕原画
    pixPtr originPainting;
    /// 当前窗口几何数据，用于绘制截图区域
    QRect currentRect;
    /// 右键菜单对象
    QMenu * menu;
};

} // namespace zsj

#endif // SCREENSHOT_H

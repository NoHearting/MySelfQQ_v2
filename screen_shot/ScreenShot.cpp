#include "ScreenShot.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QMouseEvent>
#include <QFileDialog>
#include <QClipboard>
#include <QDateTime>
#include <QPainter>
#include <QScreen>
#include <QCursor>
#include <QMutex>
#include <QMenu>
#include <QPen>
#include <QDebug>

#ifdef Q_OS_WIN
    #include <windows.h>
#endif

#include "Amplifier.h"
#include "CommonHelper.h"

namespace zsj
{



/// 鼠标按钮图片的十六进制数据
static const unsigned char UCMouseImage[] =
{
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,  0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52
    , 0x00, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x00, 0x2D,  0x08, 0x06, 0x00, 0x00, 0x00, 0x52, 0xE9, 0x60
    , 0xA2, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59,  0x73, 0x00, 0x00, 0x0B, 0x13, 0x00, 0x00, 0x0B
    , 0x13, 0x01, 0x00, 0x9A, 0x9C, 0x18, 0x00, 0x00,  0x01, 0x40, 0x49, 0x44, 0x41, 0x54, 0x58, 0x85
    , 0xED, 0xD5, 0x21, 0x6E, 0xC3, 0x30, 0x14, 0xC6,  0xF1, 0xFF, 0x9B, 0xC6, 0x36, 0x30, 0x38, 0xA9
    , 0x05, 0x01, 0x05, 0x81, 0x05, 0x03, 0x39, 0xCA,  0x60, 0x8F, 0xD2, 0x03, 0xEC, 0x10, 0x3B, 0x46
    , 0xC1, 0xC0, 0xC6, 0x0A, 0x3B, 0x96, 0xB1, 0x80,  0x82, 0xC1, 0x56, 0x2A, 0xFF, 0x06, 0xE2, 0x36
    , 0x75, 0x9A, 0xB4, 0xCA, 0xEC, 0x4E, 0x9A, 0xE4,  0x2F, 0xB2, 0x42, 0x22, 0xFF, 0xF2, 0xFC, 0x9C
    , 0x18, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52,  0x52, 0x52, 0x52, 0xFE, 0x55, 0xE4, 0xC6, 0xA0
    , 0xDC, 0xC4, 0x71, 0x87, 0xC1, 0xC1, 0x68, 0x01,  0xCC, 0x06, 0xC2, 0x51, 0xD0, 0x29, 0xB0, 0x18
    , 0x00, 0xDF, 0xC6, 0x40, 0x33, 0x37, 0x84, 0x30,  0x4C, 0x80, 0x85, 0xCE, 0x7B, 0x2E, 0x2A, 0x91
    , 0x84, 0x24, 0xBE, 0x25, 0xDE, 0x25, 0x5E, 0x2F,  0x6E, 0xAE, 0xD0, 0x37, 0x92, 0x10, 0xF0, 0x09
    , 0x54, 0x40, 0xE9, 0xEE, 0x15, 0xC6, 0xA2, 0x77,  0xFE, 0xE0, 0xE5, 0x85, 0x8F, 0x16, 0x58, 0xDF
    , 0x35, 0x06, 0x5B, 0xD3, 0xB9, 0xD4, 0x11, 0xD0,  0xA5, 0x8F, 0xDE, 0x57, 0x75, 0x83, 0x73, 0x50
    , 0x06, 0xF6, 0x72, 0x0A, 0x47, 0x40, 0x57, 0x0D,  0x38, 0xDE, 0xC0, 0x04, 0x6F, 0x68, 0x05, 0x36
    , 0xF5, 0xE1, 0x08, 0x3D, 0xCD, 0xEA, 0xEA, 0x5A,  0xD8, 0xBE, 0x5A, 0x46, 0xB0, 0x05, 0x1E, 0xAC
    , 0xF1, 0xC2, 0xD1, 0xCC, 0x01, 0x6D, 0x74, 0x02,  0xDB, 0x3B, 0xBF, 0xD3, 0x73, 0x07, 0x87, 0x2F
    , 0xEF, 0x53, 0x07, 0x38, 0x82, 0x2F, 0xF6, 0xFB,  0xB8, 0x81, 0x73, 0x41, 0x69, 0x28, 0x3A, 0x7A
    , 0x5C, 0xDD, 0x73, 0xCF, 0x3A, 0x86, 0xA3, 0x05,  0x87, 0xEA, 0xCC, 0x60, 0xA1, 0x06, 0x75, 0x89
    , 0xFE, 0x77, 0x92, 0x76, 0x68, 0x23, 0xEF, 0x88,  0xD3, 0x4C, 0xA8, 0x10, 0x7A, 0xD4, 0xEF, 0x8E
    , 0xBE, 0x8B, 0x68, 0x79, 0x3A, 0xB1, 0x72, 0xE1,  0xAE, 0xBC, 0x13, 0x0D, 0xDE, 0xBD, 0x3D, 0xF3
    , 0x08, 0x15, 0xD4, 0xDF, 0x4C, 0x06, 0x36, 0xF7,  0x9E, 0x09, 0xED, 0xE9, 0x99, 0x97, 0x3E, 0x42
    , 0xFF, 0x30, 0x42, 0x4B, 0xA1, 0x8D, 0xD8, 0xE9,  0x2A, 0xBD, 0xED, 0x41, 0x25, 0x2A, 0x89, 0x37
    , 0x1F, 0xBD, 0xEA, 0x61, 0x8B, 0x5F, 0xDD, 0xC1,  0xFA, 0x01, 0xD8, 0xA3, 0x8F, 0xFB, 0xCA, 0x70
    , 0x16, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45,  0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
};

ScreenShot *ScreenShot::Self = nullptr;
bool ScreenShot::IsActivity = false;
bool Screen::IsInit = false;

ScreenShot::ScreenShot(QWidget *parent) : QWidget(parent),
    isLeftPresssed(false), backgroundScreen(nullptr), originPainting(nullptr), pScreen(nullptr)
{
    setWindowFlags(Qt::FramelessWindowHint);

    /// 初始化鼠标
    // 初始化鼠标样式图片
    initCursor();

    // 截取屏幕信息
    initGlobalScreen();

    // 初始化鼠标放大器
    initAmplifier();

    // 初始化大小感知器
    initMeasureWidget();

    // 全屏窗口
    showFullScreen();

    // 窗口与显示屏对齐
    setGeometry(getScreenRect());

    // 置顶
    slotEgoistic();

    // 开启鼠标实时追踪
    setMouseTracking(true);

    // 更新鼠标的位置
    emit sigCursorPosChange(cursor().pos().x(), cursor().pos().y());
#ifdef Q_OS_WIN
    // 更新鼠标区域位置
    updateMouse();
#endif
    // 展示窗口
    show();

}

ScreenShot *ScreenShot::Instance()
{
    if(!IsActivity && Self)
    {
        Destory();
    }
    static QMutex mutex;
    if(!Self)
    {
        QMutexLocker locker(&mutex);
        if(!Self)
        {
            IsActivity = true;
            Self = new ScreenShot;
        }
    }
    return Self;
}

void ScreenShot::Destory()
{
    if(!IsActivity && Self)
    {
        delete Self;
        Self = nullptr;
    }
}

void ScreenShot::hideEvent(QHideEvent *event)
{
    IsActivity = false;

    QWidget::hideEvent(event);
}

void ScreenShot::closeEvent(QCloseEvent *event)
{
    IsActivity = false;
    QWidget::closeEvent(event);
}

void ScreenShot::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit sigDoubleClick();
    QWidget::mouseDoubleClickEvent(event);
}



void ScreenShot::initAmplifier(pixPtr originPainting)
{
    pixPtr tempPm = originPainting;
    if(tempPm == nullptr)
    {
        tempPm = this->originPainting;
    }
    this->pAmplifier.reset(new Amplifier(tempPm, this));
    connect(this, &ScreenShot::sigCursorPosChange, pAmplifier.get(), &Amplifier::slotPositionChange);
    pAmplifier->show();
    pAmplifier->raise();
}

void ScreenShot::initMeasureWidget()
{
    pRect.reset(new Rect(this));
    pRect->raise();
}

const QRect &ScreenShot::getScreenRect()
{
    if(!desktopRect.isEmpty())
    {
        return desktopRect;
    }

    /// 兼容多个屏幕问题
    desktopRect = QRect(QApplication::desktop()->pos(), QApplication::desktop()->size());
    return desktopRect;
}

pixPtr ScreenShot::initGlobalScreen()
{
    if(backgroundScreen.get() != nullptr)
    {
        return backgroundScreen;
    }

    // 获得屏幕原画
    pixPtr tempScreen = getGlobalScreen();

    // 制作暗色屏幕背景
    QPixmap tempDimPix(tempScreen->width(), tempScreen->height());
    tempDimPix.fill(QColor(0, 0, 0, 160));
    backgroundScreen.reset(new QPixmap(*tempScreen));
    QPainter p(backgroundScreen.get());
    p.drawPixmap(0, 0, tempDimPix);

    return backgroundScreen;
}



pixPtr ScreenShot::getGlobalScreen()
{
    if(originPainting.get() == nullptr)
    {
        // 截取当前桌面，作为截屏的背景图
        QScreen *screen = QGuiApplication::primaryScreen();
        const QRect &tempRect = getScreenRect();
        originPainting.reset(new QPixmap(screen->grabWindow(0,
                                         tempRect.x(), tempRect.y(), tempRect.width(), tempRect.height())));
    }
    return originPainting;
}

void ScreenShot::slotEgoistic()
{
    /// 窗口置顶
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
}

/**
 * @brief 初始化鼠标
 * @param ico 鼠标图片资源文件
 */
void ScreenShot::initCursor(const QString &ico)
{
    QPixmap pixmap;
    if(ico.isEmpty())
    {
        pixmap.loadFromData(UCMouseImage, sizeof(UCMouseImage));
    }
    else
    {
        pixmap.load(ico);
    }
    QCursor cursor;
    cursor = QCursor(pixmap, 15, 23);
    setCursor(cursor);
}

QSharedPointer<Screen> ScreenShot::createScreen(const QPoint &pos)
{
    if(pScreen.get() == nullptr)
    {
        /// 创建截图器
        pScreen.reset(new Screen(originPainting, pos, this));
        connect(this, &ScreenShot::sigCursorPosChange, pScreen.get(), &Screen::slotMouseChange);

        // 建立主界面双击保存信号关联
        connect(this, &ScreenShot::sigDoubleClick, pScreen.get(), &Screen::slotSaveScreen);

        // 建立截图器大小关联
        connect(pScreen.get(), &Screen::sigSizeChange, pRect.get(), &Rect::slotSizeChange);
        connect(pScreen.get(), &Screen::sigSizeChange, pAmplifier.get(), &Amplifier::slotSizeChange);

        // 建立截图器与感知器的位置关联
        connect(pScreen.get(), &Screen::sigPositionChange, pRect.get(), &Rect::slotPositionChange);

        // 获得截图器当前起始位置
        startPoint = pos;
        isLeftPresssed = true;
    }
    return pScreen;
}

void ScreenShot::destoryScreen()
{
    if(pScreen.get() != nullptr)
    {
        /// 断开信号资源
        disconnect(this, &ScreenShot::sigDoubleClick, pScreen.get(), &Screen::slotSaveScreen);
        disconnect(pScreen.get(), &Screen::sigSizeChange, pRect.get(), &Rect::slotSizeChange);
        disconnect(pScreen.get(), &Screen::sigPositionChange, pRect.get(), &Rect::slotPositionChange);

        /// 清理工具
        pScreen.reset();
        pScreen = nullptr;
        isLeftPresssed = false;
        update();
        return;
    }
}

void ScreenShot::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        createScreen(event->pos());
        return;
    }
}

void ScreenShot::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        if(pScreen.get() != nullptr)
        {
            pRect->hide();
            pAmplifier->slotPositionChange(event->x(), event->y());
            pAmplifier->show();

#ifdef Q_OS_WIN
            /// 更新当前鼠标选中的窗口
            updateMouse();
#endif
            return destoryScreen();
        }
        close();
        return;
    }
    else if(isLeftPresssed == true && event->button() == Qt::LeftButton)
    {
        /// 选择窗口选区
        if(startPoint == event->pos() && !windowRect.isEmpty())
        {
            pScreen->setCurrentRect(windowRect);
            pScreen->setGeometry(windowRect);
            pScreen->show();
            windowRect = {};
        }
        // 断开鼠标移动的信号
        disconnect(this, &ScreenShot::sigCursorPosChange, pScreen.get(), &Screen::slotMouseChange);

        // 隐藏放大器
        pAmplifier->hide();
        // 断开截图器的大小修改信号
        disconnect(pScreen.get(), &Screen::sigSizeChange, pAmplifier.get(), &Amplifier::slotSizeChange);
        isLeftPresssed = false;
    }
    QWidget::mouseReleaseEvent(event);
}

void ScreenShot::mouseMoveEvent(QMouseEvent *event)
{
    emit sigCursorPosChange(event->x(), event->y());

    if(isLeftPresssed)
    {
        pAmplifier->raise();
        windowRect = {};
        update();
    }
    else if(isLeftPresssed == false && false == Screen::State())
    {
        // 置顶
        slotEgoistic();
#ifdef Q_OS_WIN
        // 更新当前鼠标选中的窗口
        updateMouse();
#endif
    }

    QWidget::mouseMoveEvent(event);
}


void ScreenShot::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 画全屏图
    painter.drawPixmap(0, 0, desktopRect.width(), desktopRect.height(), *backgroundScreen);

    if(!windowRect.isEmpty())
    {
        // 绘制选区
        QPen pen = painter.pen();
        pen.setColor(QColor(0, 175, 175));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawRect(windowRect);
        painter.drawPixmap(QPoint(windowRect.x(), windowRect.y()), *originPainting, windowRect);
    }
    QWidget::paintEvent(event);
}

#ifdef Q_OS_WIN
void ScreenShot::updateMouse()
{
    // 获取当前鼠标选中的窗口
    ::EnableWindow((HWND)winId(), FALSE);
    /// @marker 只更新一次，可以修复用户误操作导致的查找窗口与识别界面窗口不一致
    CommonHelper::getSmallestWindowFromCursor(windowRect);
    QPoint tempPt = mapFromGlobal(QPoint(windowRect.x(), windowRect.y()));
    windowRect = QRect(tempPt.x(), tempPt.y(), windowRect.width(), windowRect.height());
    ::EnableWindow((HWND)winId(), TRUE);
    pAmplifier->slotSizeChange(windowRect.width(), windowRect.height());
    emit sigFindChildWindow(windowRect);
    update();
}
#endif

void ScreenShot::keyPressEvent(QKeyEvent *event)
{
    // Esc 退出截图
    if(event->key() == Qt::Key_Escape)
    {
        close();
    }
    else
    {
        event->ignore();
    }

}





QRect Screen::getCurrentRect() const
{
    return currentRect;
}

void Screen::setCurrentRect(const QRect &value)
{
    currentRect = value;
}



Rect::Rect(QWidget *widget) : QWidget(widget)
{
    // 设置感知器默认大小
    setFixedSize(95 * CommonHelper::getWindowHeightMultiplyingPower(),
                 20 * CommonHelper::getWindowWidthMultiplyingPower());

    // 填充默认背景
    backgroundPixmap.reset(new QPixmap(width(), height()));
    backgroundPixmap->fill(QColor(8, 8, 8, 160));

    // 默认隐藏
    hide();
}

void Rect::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), *backgroundPixmap);
    painter.setPen(QPen(QColor(Qt::white)));
    painter.drawText(rect(), Qt::AlignCenter, info);

    QWidget::paintEvent(event);
}

void Rect::slotPositionChange(int xPos, int yPos)
{
    if(xPos < 0)
    {
        xPos = 0;
    }
    if(yPos < 0)
    {
        yPos = 0;
    }
    int ry = yPos - height()  - 1;
    if(ry < 0)
    {
        this->raise();
    }
    move(xPos, (ry < 0) ? yPos : ry);
    show();
}

void Rect::slotSizeChange(int width, int height)
{
    info = QString("%1 x %2").arg(width).arg(height);
}


Screen::Screen(pixPtr originPainting, QPoint pos, QWidget *parent) : QWidget(parent),
    direction(NONE), originPoint(pos),
    isPressed(false), originPainting(originPainting)
{
    menu = new QMenu(this);
    menu->addAction("完成截图", this, SLOT(slotSaveScreen()));
    menu->addAction("保存", this, SLOT(slotSaveScreenOther()));
    menu->addSeparator();
    menu->addAction("退出截图", this, SLOT(slotQuitScreenShot()));

    // 双击完成
    connect(this, &Screen::sigDoubleClick, this, &Screen::slotSaveScreen);

    // 开启鼠标实时追踪
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
    // 默认隐藏
    hide();
}

Screen::DIRECTION Screen::getRegion(const QPoint &cursor)
{
    if (!IsInit)
    {
        return NONE;
    }
    Screen::DIRECTION ret_dir = NONE;
    // left upper
    QPoint pt_lu = mapToParent(rect().topLeft());
    // right lower
    QPoint pt_rl = mapToParent(rect().bottomRight());

    int x = cursor.x();
    int y = cursor.y();

    /// 获得鼠标当前所处窗口的边界方向
    if(pt_lu.x() + PADDING >= x
            && pt_lu.x() <= x
            && pt_lu.y() + PADDING >= y
            && pt_lu.y() <= y)
    {
        // 左上角
        ret_dir = LEFT_TOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if(x >= pt_rl.x() - PADDING
            && x <= pt_rl.x()
            && y >= pt_rl.y() - PADDING
            && y <= pt_rl.y())
    {
        // 右下角
        ret_dir = RIGHT_BOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if(x <= pt_lu.x() + PADDING
            && x >= pt_lu.x()
            && y >= pt_rl.y() - PADDING
            && y <= pt_rl.y())
    {
        // 左下角
        ret_dir = LEFT_BOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if(x <= pt_rl.x()
            && x >= pt_rl.x() - PADDING
            && y >= pt_lu.y()
            && y <= pt_lu.y() + PADDING)
    {
        // 右上角
        ret_dir = RIGHT_TOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if(x <= pt_lu.x() + PADDING
            && x >= pt_lu.x())
    {
        // 左边
        ret_dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if( x <= pt_rl.x()
             && x >= pt_rl.x() - PADDING)
    {
        // 右边
        ret_dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if(y >= pt_lu.y()
            && y <= pt_lu.y() + PADDING)
    {
        // 上边
        ret_dir = TOP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if(y <= pt_rl.y()
            && y >= pt_rl.y() - PADDING)
    {
        // 下边
        ret_dir = BOTTOM;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else
    {
        // 默认
        ret_dir = NONE;
        this->setCursor(QCursor(Qt::SizeAllCursor));
    }
    return ret_dir;
}

void Screen::contextMenuEvent(QContextMenuEvent *)
{
    menu->exec(cursor().pos());
}

void Screen::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit sigDoubleClick();
        event->accept();
    }
}

void Screen::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isPressed = true;
        if(direction != NONE)
        {
            this->mouseGrabber();
        }

        /// @bug 这里可能出现问题，不应当使用globalPos
        movePos = event->globalPos() - pos();
    }
}

void Screen::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isPressed = false;
        if(direction != NONE)
        {
            setCursor(QCursor(Qt::SizeAllCursor));
        }
    }
}

void Screen::mouseMoveEvent(QMouseEvent *event)
{
    QPoint gloPoint = mapToParent(event->pos());
    // left upper
    QPoint pt_lu = mapToParent(rect().topLeft());
    // left lower
    QPoint pt_ll = mapToParent(rect().bottomLeft());
    // right lower
    QPoint pt_rl = mapToParent(rect().bottomRight());
    // right upper
    QPoint pt_ru = mapToParent(rect().topRight());
    if(!isPressed)
    {
        /// 检查鼠标鼠标方向
        direction = getRegion(gloPoint);

        /// 根据方位判断拖拉对应支点
        switch(direction)
        {
            case NONE:
            case RIGHT:
            case RIGHT_BOTTOM:
                originPoint = pt_lu;
                break;
            case RIGHT_TOP:
                originPoint = pt_ll;
                break;
            case LEFT:
            case LEFT_BOTTOM:
                originPoint = pt_ru;
                break;
            case LEFT_TOP:
            case TOP:
                originPoint = pt_rl;
                break;
            case BOTTOM:
                originPoint = pt_lu;
                break;
        }
    }
    else
    {
        if(direction != NONE)
        {
            const int &global_x = gloPoint.x();

            /// 鼠标进行拖拉拽
            switch(direction)
            {
                case LEFT:
                    return slotMouseChange(global_x, pt_ll.y() + 1);
                case RIGHT:
                    return slotMouseChange(global_x, pt_rl.y() + 1);
                case TOP:
                    return slotMouseChange(pt_lu.x(), gloPoint.y());
                case BOTTOM:
                    return slotMouseChange(pt_rl.x() + 1, gloPoint.y());
                case LEFT_TOP:
                case RIGHT_TOP:
                case LEFT_BOTTOM:
                case RIGHT_BOTTOM:
                    return slotMouseChange(global_x, gloPoint.y());
                default:
                    break;
            }
        }
        else
        {
            /// 窗口的移动
            /// @bug :这里可能存在问题, 不应当使用globalPos
            move(event->globalPos() - movePos);
            movePos = event->globalPos() - pos();
        }
    }
    currentRect = geometry();
}

void Screen::moveEvent(QMoveEvent *event)
{
    emit sigPositionChange(x(), y());

    QWidget::moveEvent(event);
}

void Screen::resizeEvent(QResizeEvent *event)
{
    listMarker.clear();

    /// 重新计算八个锚点
    // 角点
    listMarker.push_back(QPoint(0, 0));
    listMarker.push_back(QPoint(width(), 0));
    listMarker.push_back(QPoint(0, height()));
    listMarker.push_back(QPoint(width(), height()));

    // 中点
    listMarker.push_back(QPoint((width() >> 1), 0));
    listMarker.push_back(QPoint((width() >> 1), height()));
    listMarker.push_back(QPoint(0, (height() >> 1)));
    listMarker.push_back(QPoint(width(), (height() >> 1)));

    emit sigSizeChange(width(), height());

    QWidget::resizeEvent(event);
}

void Screen::showEvent(QShowEvent *event)
{
    IsInit = true;

    QWidget::showEvent(event);
}

void Screen::hideEvent(QHideEvent *event)
{
    currentRect = {};
    movePos = {};
    originPoint = {};
    IsInit = false;

    QWidget::hideEvent(event);
}

void Screen::enterEvent(QEvent *event)
{
    setCursor(Qt::SizeAllCursor);
    QWidget::enterEvent(event);
}

void Screen::leaveEvent(QEvent *event)
{
    setCursor(Qt::ArrowCursor);
    QWidget::leaveEvent(event);
}

void Screen::closeEvent(QCloseEvent *event)
{
    IsInit = false;
    QWidget::closeEvent(event);
}

void Screen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 绘制截屏编辑窗口
    painter.drawPixmap(QPoint(0, 0), *originPainting, currentRect);

    // 绘制边框线
    QPen pen(QColor(0, 174, 255), 2);
    painter.setPen(pen);
    painter.drawRect(rect());

    // 绘制八个点
    // 改变点的宽度
    pen.setWidth(4);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPoints(listMarker);

    QWidget::paintEvent(event);

}

const QString Screen::getFileName()
{
    QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd HH-mm-ss");
    return fileName;
}

void Screen::slotMouseChange(int xPos, int yPos)
{
    show();
    if(xPos < 0 || yPos < 0)
    {
        return;
    }

    int rx = (xPos >= originPoint.x()) ? originPoint.x() : xPos;
    int ry = (yPos >= originPoint.y()) ? originPoint.y() : yPos;
    int rw = abs(xPos - originPoint.x());
    int rh = abs(yPos - originPoint.y());

    // 改变大小
    currentRect = QRect(rx, ry, rw, rh);

    this->setGeometry(currentRect);

    // 改变大小后更新父窗口，防止父窗口未及时刷新而导致的问题
    parentWidget()->update();
}



void Screen::slotSaveScreenOther()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存图片", getFileName(), "JPEG Files (*.jpg)");
    if(fileName.length() > 0)
    {
        originPainting->copy(currentRect).save(fileName, "jpg");
        slotQuitScreenShot();
    }
}

void Screen::slotQuitScreenShot()
{
    close();
    parentWidget()->close();
}

void Screen::slotSaveScreen()
{
    // 把图片放入剪切板
    QClipboard *board = QApplication::clipboard();
    board->setPixmap(originPainting->copy(currentRect));
    // 退出当前截图
    slotQuitScreenShot();
}


extern "C" void ScreenShot()
{
    ScreenShot::Instance();
}

} // namespace zsj

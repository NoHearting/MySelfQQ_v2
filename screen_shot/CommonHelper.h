#ifndef COMMONHELPER_H
#define COMMONHELPER_H

#include <QString>
#include <QRect>
#include <QWidget>


namespace zsj {



class CommonHelper
{
public:
    CommonHelper();

    /**
     * @brief 设置qss样式
     * @param style qss文件名
     * @remark 如果是qrc路径，请带上 qrc:/
     */
    static void setStyle(const QString & style);

    /**
     * @brief 设置语言包
     * @param language 语言包的文件名
     */
    static void setLanguagePack(const QString & language);

    /**
     * @brief 将窗口移动到中心
     * @param widget 要移动的窗口
     * @param parentRect 矩形几何数据
     */
    static void moveCenter(QWidget *widget,QRect parentRect = {});

    /**
     * @brief 获得当前界面与开发时界面之间的横向倍率
     * @return float 倍率
     * @remark 开发时的桌面和运行时的桌面大小可能不一样
     */
    static float getWindowWidthMultiplyingPower();

    /**
     * @brief 获得当前界面与开发时界面之间的纵向倍率
     * @return float 倍率
     * @remark 开发时的桌面和运行时的桌面大小可能不一样
     */
    static float getWindowHeightMultiplyingPower();

#ifdef Q_OS_WIN
    /**
     * @brief 获得当前鼠标位置最小的子窗口
     * @param smallRect 最小矩形
     * @return bool 是否成功
     */
    static bool getSmallestWindowFromCursor(QRect & smallRect);

    /**
     * @brief getCurrentWindowFromCursor
     * @param[out] currRect
     * @return bool 是否成功
     */
    static bool getCurrentWindowFromCursor(QRect & currRect);
#endif

protected:
    /**
     * @brief 更新窗口赔率
     */
    static void updateWindowSizeMultiplyingPower();

private:
    /// 窗口横向倍率
    static float widthMultiplyingPower;

    /// 窗口纵向倍率
    static float heightMultiplyingPower;

};
} // namespace zsj

#endif // COMMONHELPER_H

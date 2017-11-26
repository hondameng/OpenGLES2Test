//
 // Created by mhd on 2017/8/25.
//


#include <list>
#include <vector>
#include "GLBaseView.h"
#include "GLContext.h"
#include "GLStaticView.h"
#include "GLScrollView.h"
#ifndef GLENGINE_H
#define GLENGINE_H

//
//GL 全局引擎，用于控制全部子view和资源初始化、释放
//
class GLEngine
{
private:
    vector<GLBaseView *> viewVector;

public:

    //保存GL环境信息
    GLContext *pGLContext;

    GLEngine();
    ~GLEngine();

    /**
     * 初始化GL环境信息
     * @param viewWidth GL viewport 宽
     * @param viewHeight GL viewport 高
 */
    void initGlContext(int viewWidth , int viewHeight);

    /**
     * 创建固定坐标view
     * @param posX 起始X轴位置
     * @param posY 起始Y轴位置
     * @param realWidth 数据帧原始宽
     * @param realHeight 数据帧原始高
     * @param drawWidth  绘制的宽
     * @param drawHeight 绘制的高
     * @return
     */
    GLBaseView *createStaticView(int posX, int posY, int realWidth, int realHeight, int drawWidth, int drawHeight);

    //创建自动移动的子view
    GLBaseView *createScrollView(
            int posX,               //起始X轴位置
            int posY,               //起始Y轴位置
            int realWidth,          //数据帧原始宽
            int realHeight,         //数据帧原始高
            int drawWidth,          //绘制的宽
            int drawHeight          //绘制的高
    );

    /**
     * 绘制子view
     * @param view
     */
    void drawGlView(GLBaseView * view,bool isFrameUpdate);

    void drawFBOView();

    /**
     * 从GL中获取绘制的帧数据
    * @return
    */
    signed char *getScreenFrame();

    //清除界面上的图像
    void clearView();

};


#endif //GLENGINE_H

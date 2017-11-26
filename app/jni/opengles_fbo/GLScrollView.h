//
// Created by mhd on 2017/8/25.
//
#define _GLIBCXX_USE_C99_MATH 1
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "GLContext.h"
#include "gl_utils.h"
#include "matrix.h"
#include "GLBaseView.h"
#include "GLTexture.h"

#ifndef GLSCROLLVIEW_H
#define GLSCROLLVIEW_H

class GLScrollView : public GLBaseView
{

private:
    /**
     * 计算滚动位置，当view碰边自动物理反弹
     * @param scaleX     宽的缩放值
     * @param scaleY     高的缩放值
     * @param xy        当前坐标
     * @param xOffset   当前偏X轴移量
     * @param yOffset   当前偏Y轴移量
     */
    void calculatePosition(float scaleX, float scaleY, float *xy, float *xOffset, float *yOffset);

public:
    /**
     * 初始化自由滚动view
     * @param context GL环境信息
     * @param posX 起始X轴位置
     * @param posY 起始Y轴位置
     * @param realW 数据帧原始宽
     * @param realH 数据帧原始高
     * @param drawW 绘制的宽
     * @param drawH 绘制的高
     */
    GLScrollView(GLContext *context, int posX, int posY, int realWidth, int realHeight, int drawWidth, int drawHeight);

    ~GLScrollView();


    float positionArr[2];           //当前坐标
    float xOffset;                  //当前X偏移量
    float yOffset;                  //当前Y偏移量

    virtual void drawFrame(bool isFrameUpdate);
};

#endif //GLSCROLLVIEW_H
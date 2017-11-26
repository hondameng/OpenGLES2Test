//
// Created by mhd on 2017/8/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "GLContext.h"
#include "gl_utils.h"
#include "matrix.h"
#include "GLBaseView.h"

#ifndef GLSTATICVIEW_H
#define GLSTATICVIEW_H


class GLStaticView : public GLBaseView
{

public:

    /**
     * 初始化固定坐标的view
     * @param context GL环境信息
     * @param posX 起始X轴位置
     * @param posY 起始Y轴位置
     * @param realW 数据帧原始宽
     * @param realH 数据帧原始高
     * @param drawW 绘制的宽
     * @param drawH 绘制的高
    */
    GLStaticView(GLContext *context, int posX, int posY, int realWidth, int realHeight, int drawWidth, int drawHeight);

    ~GLStaticView();

    //绘制
    virtual void drawFrame(bool isFrameUpdate);
};

#endif //GLSTATICVIEW_H
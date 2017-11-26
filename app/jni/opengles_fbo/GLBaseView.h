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
#include "GLProgram.h"

#ifndef GLBASEVIEW_H
#define GLBASEVIEW_H

//所有GL子view的基类
class GLBaseView
{

public:
    GLContext *glContext;

    GLProgram *pGLProgram;

    GLTexture *pGLTexture;

    //rgb
    signed char *rgbBuffer;
    unsigned long rgbBufferSize;
    bool isFrameUpdate = false;

    //原尺寸
    int realWidth;
    int realHeight;

    //实际绘画大小
    int drawWidth;
    int drawHeight;

    //起始位置（ 左上角为（0，0））
    int positionX;
    int positionY;

    //长宽的缩放，铺满view时都为1
    float scaleX;
    float scaleY;

    float *maMVPMatrix;

    virtual ~GLBaseView();

    //用于基类调用所有派生类的绘制函数
    virtual void drawFrame(bool isFrameUpdate)=0;
};

#endif //GLBASEVIEW_H

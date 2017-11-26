//
// Created by mhd on 2017/9/4.
//
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "GLContext.h"
#include "GLTexture.h"

#ifndef GLPROGRAM_H
#define GLPROGRAM_H


class GLProgram
{
public:
    //顶点着色器位置数据引用
    GLint maPositionHandle;

    //顶点着色器纹理坐标引用
    GLint maTexCoorHandle;

    //着色器程序引用
    GLuint pProgram;
    //顶点着色器最终变化矩阵引用
    GLint maMVPMatrixHandle;

    //片元着色器采样器引用
    GLint mrgbTextureHandle;

    const char *vertexShader;
    const char *fragShader;

    /**
     * 初始化
     * @param texW 纹理宽度
     * @param texH 纹理高度
     */
    GLProgram(const char *vertexShader, const char *fragShader);

    ~GLProgram();

    void createProgram();

    /**
     * 绘制纹理
     * @param maMVPMatrix 控制矩阵
     * @param  glTexture 将要绘制的纹理
     */
    void draw(float *maMVPMatrix , GLTexture *glTexture);

};


#endif //GLPROGRAM_H

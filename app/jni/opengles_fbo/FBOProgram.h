//
// Created by mhd on 2017/9/4.
//
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#ifndef OPENGLES2TEST_FBOPROGRAM_H
#define OPENGLES2TEST_FBOPROGRAM_H


class FBOProgram
{
public:
    //FBO顶点着色器位置数据引用
    GLint maFboPositionHandle;

    //FBO顶点着色器纹理坐标引用
    GLint maFboTexCoorHandle;

    //FBO着色器程序引用
    GLuint pFboProgram;

    //FBO顶点着色器最终变化矩阵引用
    GLint maFboMVPMatrixHandle;

    //FBO片元着色器采样器引用
    GLint mFboTextureHandle;

    //纹理数据FBO
    GLuint fboTexture;
    GLuint framebufferId;
    GLuint renderbufferID;

    /**
     * FBOProgram
     * @param fboW FBO宽度
     * @param fboH FBO高度
     */
    FBOProgram(int fboW, int fboH,const char *vertexShader, const char *fragShader);
    ~FBOProgram();

    /**
     * 渲染FBO内容到屏幕上
     * @param maMVPMatrix 控制矩阵
     */
    void draw(float *maMVPMatrix);
};


#endif //OPENGLES2TEST_FBOPROGRAM_H

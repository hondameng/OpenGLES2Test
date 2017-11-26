//
// Created by mhd on 2017/9/4.
//

#include "FBOProgram.h"
#include "GLContext.h"

/**
 * FBOProgram
 * @param fboW FBO宽度
 * @param fboH FBO高度
 */
FBOProgram::FBOProgram(int fboW, int fboH,const char *vertexShader, const char *fragShader)
{
    // FBO的创建和绑定
    glGenFramebuffers(1,&framebufferId);
    glBindFramebuffer(GL_FRAMEBUFFER,framebufferId);

    //创建FBO纹理
    glGenTextures(1, &fboTexture);
    glBindTexture(GL_TEXTURE_2D, fboTexture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,fboW, fboH,0,GL_RGB,GL_UNSIGNED_BYTE,0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // 创建深度缓冲区
    glGenRenderbuffers(1, &renderbufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbufferID);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT, fboW, fboH);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbufferID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    //初始化FBO Shader信息
    GLuint shaders[2] = {0};
    shaders[0] = initShader(vertexShader, GL_VERTEX_SHADER);
    shaders[1] = initShader(fragShader, GL_FRAGMENT_SHADER);
    pFboProgram = initProgram(shaders, 2);
    glDeleteShader(shaders[0]);
    glDeleteShader(shaders[1]);
    maFboMVPMatrixHandle = glGetUniformLocation(pFboProgram, UMVPMATRIX_NAME);
    maFboPositionHandle = glGetAttribLocation(pFboProgram, APOSITION_NAME);
    maFboTexCoorHandle = glGetAttribLocation(pFboProgram, ATEXCOOR_NAME);
    mFboTextureHandle = glGetUniformLocation(pFboProgram, TEXTURE_NAME);
}

FBOProgram::~FBOProgram()
{
    glDeleteProgram(pFboProgram);
    glDeleteTextures(1, &fboTexture);
    glDeleteFramebuffers(1, &framebufferId);
    glDeleteRenderbuffers(1, &renderbufferID);
}


/**
 * 渲染FBO内容到屏幕上
 * @param maMVPMatrix 控制矩阵
 */
void FBOProgram::draw(float *maMVPMatrix)
{
    //绘制FBO绑定的纹理
    glUseProgram(pFboProgram);
    glUniformMatrix4fv(maFboMVPMatrixHandle, 1, GL_FALSE, maMVPMatrix);
    glVertexAttribPointer(maFboPositionHandle, 3, GL_FLOAT, GL_FALSE, 3 * 4, _dataVertexFbo);
    glVertexAttribPointer(maFboTexCoorHandle, 2, GL_FLOAT, GL_FALSE, 2 * 4, _dataTexCoorFbo);

    //绘制FBO
    glBindTexture(GL_TEXTURE_2D, fboTexture);

    glUniform1i(mFboTextureHandle, 0);
    glEnableVertexAttribArray(maFboPositionHandle);
    glEnableVertexAttribArray(maFboTexCoorHandle);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(maFboPositionHandle);
    glDisableVertexAttribArray(maFboTexCoorHandle);
}


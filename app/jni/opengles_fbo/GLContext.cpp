//
// Created by mhd on 2017/8/25.
//
#include <string>
#include "GLContext.h"


/**
 *
 * @param viewW view的宽度
 * @param viewH view的高度
 * @return
 */
GLContext::GLContext(int viewW , int viewH)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    viewWidth = viewW;
    viewHeight = viewH;
    pFBOProgram = new FBOProgram(viewW,viewH,_codeVertexFBOShader,_codeFragFBOShader);
}

GLContext::~GLContext()
{
    delete pFBOProgram;
}


/**
 * 将FBO绘制到屏幕
 */
void GLContext::drawFBO()
{
    //初始化FBO矩阵
    maMVPMatrixFbo = getRotateM(NULL, 0, 0, 0, 0, 1);
    glViewport(0, 0, viewWidth, viewHeight);
    pFBOProgram->draw(maMVPMatrixFbo);
    free(maMVPMatrixFbo);
}

/**
 * 清空FBO已绘制的内容
 */
void GLContext::clearFBO()
{
    //进入FBO空间，在FBO上绘制我的纹理
    glBindFramebuffer(GL_FRAMEBUFFER, pFBOProgram->framebufferId);
    glViewport(0, 0, viewWidth, viewHeight);
    glClearColor(1.0, 1.0, 0.6, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //退出FBO空间
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/**
 * 获取fbo ID
 * @return  fbo ID
 */
GLuint GLContext::getFramebufferId()
{
    if(pFBOProgram != NULL)
    {
        return pFBOProgram->framebufferId;
    }
    return 0;
}

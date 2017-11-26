//
// Created by mhd on 2017/8/25.
//

#include "GLStaticView.h"

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
GLStaticView::GLStaticView(GLContext *context, int posX, int posY, int realW, int realH, int drawW, int drawH)
{
    glContext = context;
    realWidth = realW;
    realHeight = realH;
    drawWidth = drawW;
    drawHeight = drawH;
    positionX = posX;
    positionY = posY;
    rgbBufferSize = sizeof(char) * realW * realH * 3;
    rgbBuffer = (signed char *) malloc(rgbBufferSize);
    memset(rgbBuffer, 0, rgbBufferSize);
    scaleX = 1.00f * drawWidth / glContext->viewWidth;
    scaleY = 1.00f * realHeight / realWidth * glContext->viewWidth / glContext->viewHeight * scaleX;

    pGLProgram = new GLProgram(_codeVertexShader,_codeFragShader);
    pGLTexture = new GLTexture(realW,realH);
}


GLStaticView::~GLStaticView()
{
    delete pGLProgram;
    pGLProgram = nullptr;

    delete pGLTexture;
    pGLTexture = nullptr;
    free(rgbBuffer);
    LOGI_EU("~GLStaticView");
}


//绘制
void GLStaticView::drawFrame(bool isUpdate)
{
    //进入FBO空间，在FBO上绘制我的纹理
    glBindFramebuffer(GL_FRAMEBUFFER, glContext->getFramebufferId());

    maMVPMatrix = getRotateM(NULL, 0, 0, 0, 0, 1);
    float right = -1 + scaleX;
    float top = 1 - scaleY;
    float tranX = right + 2.00f / glContext->viewWidth * positionX;  //先移动到左上角（right,top），再以左上角为基准
    float tranY = top - (2.00f / glContext->viewHeight * positionY);
    translateM(maMVPMatrix, 0, tranX, tranY, 0);                      //必须向位移再缩放
    scaleM(maMVPMatrix, scaleX, scaleY, 1);
    glViewport(0, 0, glContext->viewWidth, glContext->viewHeight);

//    pGLTexture->setUpdateStatus(isUpdate);
    if(isUpdate)
    {
        pGLTexture->frameData = rgbBuffer;
    }
    pGLProgram->draw(maMVPMatrix,pGLTexture);

    free(maMVPMatrix);

    //退出FBO空间
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


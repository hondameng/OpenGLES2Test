//
// Created by mhd on 2017/8/25.
//

#include "GLScrollView.h"

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
GLScrollView::GLScrollView(GLContext *context, int posX, int posY, int realW, int realH, int drawW,int drawH)
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

    float right = -1 + scaleX;
    float top = 1 - scaleY;
    xOffset = 0.03;
    yOffset = 0.03;
    positionArr[0] = right + 2.00f / glContext->viewWidth * positionX;
    positionArr[1] = top - (2.00f / glContext->viewHeight * positionY);

    pGLProgram = new GLProgram(_codeVertexShader,_codeFragShader);
    pGLTexture = new GLTexture(realW,realH);
}


GLScrollView::~GLScrollView()
{
    delete pGLProgram;
    pGLProgram = nullptr;

    delete pGLTexture;
    pGLTexture = nullptr;
    free(rgbBuffer);
    LOGI_EU("~GLScrollView");
}

/**
 * 计算滚动位置，当view碰边自动物理反弹
 * @param scaleX     宽的缩放值
 * @param scaleYP     高的缩放值
 * @param xy        当前坐标
 * @param xOffset   当前偏X轴移量
 * @param yOffset   当前偏Y轴移量
 */
void GLScrollView::calculatePosition(float scaleX, float scaleYP, float *xy, float *xOffset, float *yOffset)
{
    float left = -1 + scaleX;       //左边
    float right = 1 - scaleX;       //右边
    float top = 1 - scaleYP;         //顶部
    float bottem = -1 + scaleYP;     //底部

    float x = *xy;
    float y = *(xy + 1);

    //判断是否碰边，碰到后把偏移量改变
    if (x >= right)
    {
        *xOffset = -0.03f;
    }
    if (x <= left)
    {
        *xOffset = 0.03f;
    }
    if (y >= top)
    {
        *yOffset = -0.05f;
    }
    if (y <= bottem)
    {
        *yOffset = 0.03f;
    }
    xy[0] = x + *xOffset;
    xy[1] = y + *yOffset;
}

/**
 * 绘制纹理
 */
void GLScrollView::drawFrame(bool isUpdate)
{
    //进入FBO空间
    glBindFramebuffer(GL_FRAMEBUFFER, glContext->getFramebufferId());

    //计算缩放平移矩阵
    maMVPMatrix = getRotateM(NULL, 0, 0, 0, 0, 1);
    float scaleYP = 1.00f * realHeight / realWidth * glContext->viewWidth / glContext->viewHeight;
    float scaleX = 1.00f * drawWidth / glContext->viewWidth;;
    scaleYP = scaleYP * scaleX;
    calculatePosition(scaleX, scaleYP, positionArr, &xOffset, &yOffset);        //计算出这次绘制的坐标
    translateM(maMVPMatrix, 0, *positionArr, *(positionArr + 1), 0);
    scaleM(maMVPMatrix, scaleX, scaleYP, 1);                                    //缩放到需要绘制的大小，不执行缩放会占满整个viewport

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

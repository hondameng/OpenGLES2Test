//
// Created by mhd on 2017/8/25.
//

#include "GLEngine.h"

GLEngine::GLEngine()
{
    LOGI_EU("GLEngine");
}

GLEngine::~GLEngine()
{
    LOGI_EU("~GLEngine");

    //遍历view的列表，全部释放掉
    for(int i = 0 ; i < viewVector.size(); i ++)
    {
        GLBaseView *baseView = viewVector[i];
        if(baseView != NULL)
            delete baseView;
    }
    viewVector.clear();
    if (pGLContext != NULL)
        delete pGLContext;
    pGLContext = NULL;
}


/**
 * //初始化GL环境信息
 * @param viewWidth GL viewport 宽
 * @param viewHeight GL viewport 高
 */
void GLEngine::initGlContext(int viewWidth, int viewHeight)
{
    if (pGLContext != NULL)
    {
        delete pGLContext;
    }
    pGLContext = new GLContext(viewWidth,viewHeight);
}

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
GLBaseView *GLEngine::createStaticView(int posX, int posY,
                                          int realWidth, int realHeight,
                                          int drawWidth, int drawHeight)
{
    GLBaseView *glStaticView = new GLStaticView(pGLContext, posX, posY, realWidth, realHeight, drawWidth,drawHeight);
    viewVector.push_back(glStaticView);
    return glStaticView;
}

/**
 * 创建自由随机滚动view
 * @param posX 起始X轴位置
 * @param posY 起始Y轴位置
 * @param realWidth 数据帧原始宽
 * @param realHeight 数据帧原始高
 * @param drawWidth  绘制的宽
 * @param drawHeight 绘制的高
 * @return
 */
GLBaseView *GLEngine::createScrollView(int posX, int posY,
                                        int realWidth, int realHeight,
                                        int drawWidth, int drawHeight)
{
    GLBaseView *glScrollView = new GLScrollView(pGLContext, posX, posY, realWidth, realHeight, drawWidth,drawHeight);
    viewVector.push_back(glScrollView);
    return glScrollView;
}

/**
 * 绘制子view
 * @param view
 */
void GLEngine::drawGlView(GLBaseView *view,bool isFrameUpdate)
{
    view->drawFrame(isFrameUpdate);
}

void GLEngine::drawFBOView()
{
    pGLContext->drawFBO();
}

/**
 * 从GL中获取绘制的帧数据
 * @return 帧数据
 */
signed char *GLEngine::getScreenFrame()
{
    if (pGLContext != NULL)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, pGLContext->getFramebufferId());
        glViewport(0, 0, pGLContext->viewWidth, pGLContext->viewHeight);
        int w = pGLContext->viewWidth;
        int h = pGLContext->viewHeight;
        int bufferSize = w * h * 3 * sizeof(GLbyte);
        pGLContext->colorBufferSize = bufferSize;
        GLbyte *colorArr = (GLbyte *) malloc(bufferSize);
        glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, colorArr);
        GLbyte *colorArrConverted = (GLbyte *) malloc(bufferSize);

        //倒置帧数据
        int i, j, pixels_index = 0;
        for (i = h - 1; i >= 0; i--)
        {
            for (j = 0; j < w * 3; j++)
            {
                colorArrConverted[pixels_index] = colorArr[i * w * 3 + j];
                pixels_index++;
            }
        }
        free(colorArr);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return colorArrConverted;
    } else
    {
        return NULL;
    }
}

/**
 * 清空绘制的图像
 */
void GLEngine::clearView()
{
    pGLContext->clearFBO();
}

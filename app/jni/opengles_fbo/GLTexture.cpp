//
// Created by mhd on 2017/9/5.
//

#include "GLTexture.h"

/**
 * 创建一个纹理
 * @param texW 纹理宽度
 * @param texH 纹理高度
 */
GLTexture::GLTexture(int texW, int texH)
{
    texWidth = texW;
    texHeight = texH;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, frameData);
    glBindTexture(GL_TEXTURE_2D, 0);
//    isFrameDataUpdate = true;
}

GLTexture::~GLTexture()
{
    LOGI_EU("~GLTexture()");
    glDeleteTextures(1, &texture);
}

/**
 * 启用纹理
 */
void GLTexture::activeTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
//    if(isFrameDataUpdate)
//    {
        glTexSubImage2D(GL_TEXTURE_2D,0,0,0,texWidth,texHeight,GL_RGB,GL_UNSIGNED_BYTE,frameData);
//    }
}

/**
 * 设置纹理是否需要更新
 * @param isUpdate
 */
//void GLTexture::setUpdateStatus(bool isUpdate)
//{
//    isFrameDataUpdate = isUpdate;
//}

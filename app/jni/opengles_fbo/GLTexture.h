//
// Created by mhd on 2017/9/5.
//
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "gl_utils.h"

#ifndef OPENGLES2TEST_GLTEXTURE_H
#define OPENGLES2TEST_GLTEXTURE_H


class GLTexture
{
public:
    //纹理数据
    GLuint texture;

    //原尺寸
    int texWidth;
    int texHeight;
    GLbyte *frameData;

//    bool isFrameDataUpdate;

    GLTexture(int texW, int texH);
    ~GLTexture();

//    void setUpdateStatus(bool isUpdate);
    void activeTexture();

};


#endif //OPENGLES2TEST_GLTEXTURE_H

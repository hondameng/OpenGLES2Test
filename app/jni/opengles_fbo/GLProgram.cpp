//
// Created by mhd on 2017/9/4.
//

#include "GLProgram.h"

/**
 * 初始化
 * @param texW 纹理宽度
 * @param texH 纹理高度
 */
GLProgram::GLProgram(const char *vertexShader, const char *fragShader)
{
    this->vertexShader = vertexShader;
    this->fragShader = fragShader;
    createProgram();
    maMVPMatrixHandle = glGetUniformLocation(pProgram, UMVPMATRIX_NAME);
    maPositionHandle = glGetAttribLocation(pProgram, APOSITION_NAME);
    maTexCoorHandle = glGetAttribLocation(pProgram, ATEXCOOR_NAME);
    mrgbTextureHandle = glGetUniformLocation(pProgram, TEXTURE_NAME);
    glUniform1i(mrgbTextureHandle, 0);
    glEnableVertexAttribArray(maPositionHandle);
    glEnableVertexAttribArray(maTexCoorHandle);
}

GLProgram::~GLProgram()
{
    LOGI_EU("~GLProgram()");
    glDeleteProgram(pProgram);
}

/**
 * 绘制纹理
 * @param maMVPMatrix 控制矩阵
 * @param  glTexture 将要绘制的纹理
 */
void GLProgram::draw(float *maMVPMatrix, GLTexture *glTexture)
{
    glUseProgram(pProgram);
    glUniformMatrix4fv(maMVPMatrixHandle, 1, GL_FALSE, maMVPMatrix);
    glVertexAttribPointer(maPositionHandle, 3, GL_FLOAT, GL_FALSE, 3 * 4, _dataVertex);
    glVertexAttribPointer(maTexCoorHandle, 2, GL_FLOAT, GL_FALSE, 2 * 4, _dataTexCoor);
    glUniform1i(mrgbTextureHandle, 0);
    glEnableVertexAttribArray(maPositionHandle);
    glEnableVertexAttribArray(maTexCoorHandle);

    glTexture->activeTexture();

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(maPositionHandle);
    glDisableVertexAttribArray(maTexCoorHandle);
}

void GLProgram::createProgram()
{
    GLuint *shaders = new GLuint[2];
    shaders[0] = initShader(vertexShader, GL_VERTEX_SHADER);
    shaders[1] = initShader(fragShader, GL_FRAGMENT_SHADER);
    pProgram = initProgram(shaders, 2);
    glDeleteShader(shaders[0]);
    glDeleteShader(shaders[1]);
    delete []shaders;
}

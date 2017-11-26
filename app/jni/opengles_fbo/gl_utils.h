/***此类用于生成一些OpenGL ES 2.0 的对象****/
#ifndef _CM_ES_UTIL_
#define _CM_ES_UTIL_
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define LOG_TAG "esUtil"
#define LOGI_EU(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGW_EU(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE_EU(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define UNIT 1
#define TEXTURE_COOR_UNIT 1

/**
 * 初始化着色器
 */
GLuint
initShader(const char * strShaderCode, unsigned int shaderType);

/**
 * 检查着色器初始化状态
 */
GLint
checkInitShader(GLint pShader);

/**
 * 初始化渲染程序
 */
GLuint
initProgram(GLuint* shaderArray, GLint size);

/**
 * 检查程序链接状态
 */
GLint
checkLinkProgram(GLint pProgram);

char* loadFileChar(const char* filename);


#endif

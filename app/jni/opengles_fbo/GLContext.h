//
// Created by mhd on 2017/8/25.
//

#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <string>

#include "gl_utils.h"
#include "matrix.h"
#include "FBOProgram.h"


#define UNIT 1
#define TEXTURE_COOR_UNIT 1

using namespace std;

//全局使用的顶点着色器
static const char * _codeVertexShader = \
"attribute vec3 aPosition;							\n" \
"uniform mat4 uMVPMatrix;	 						\n" \
"attribute vec2 aTexCoor; 							\n" \
"varying vec2 vTexCoor;		 						\n" \
"void main() 										\n" \
"{ 													\n" \
"	gl_Position = uMVPMatrix * vec4(aPosition, 1); 	\n" \
" 	vTexCoor = aTexCoor;							\n" \
"} 													\n" \
;

//全局使用的片段着色器
static const char * _codeFragShader = \
"precision mediump float;						            	\n" \
"varying vec2 vTexCoor;							                \n" \
"uniform sampler2D texture;					                  	\n" \
"void main()							                        \n" \
"{					                            	         	\n" \
"   vec4 colorraw = texture2D(texture, vTexCoor);    	    	\n" \
"   vec3 color = vec3(colorraw.r,colorraw.g,colorraw.b);		\n" \
"   gl_FragColor = vec4(color,1);				    			\n" \
"}																\n" \
;

//FBO全局使用的顶点着色器
static const char * _codeVertexFBOShader = \
"attribute vec3 aPosition;						                                            	\n" \
"uniform mat4 uMVPMatrix;	 		                                        			    	\n" \
"attribute vec2 aTexCoor; 						                                            	\n" \
"varying vec2 vTexCoor;		 						                                            \n" \
"void main() 									                                            	\n" \
"{ 												                                            	\n" \
"	gl_Position = uMVPMatrix * vec4(aPosition.x, -aPosition.y , aPosition.z, 1);               	\n" \
" 	vTexCoor = aTexCoor;						                                        	    \n" \
"} 													                                            \n" \
;


//FBO全局使用的片段着色器
static const char * _codeFragFBOShader = \
"precision mediump float;						            	\n" \
"varying vec2 vTexCoor;							                \n" \
"uniform sampler2D texture;					                	\n" \
"void main()							                        \n" \
"{					                            	         	\n" \
"   vec4 colorraw = texture2D(texture, vTexCoor);    	    	\n" \
"   vec3 color = vec3(colorraw.r,colorraw.g,colorraw.b);		\n" \
"   gl_FragColor = vec4(color,1);				    			\n" \
"}																\n" \
;

static float _dataVertex[] =
        {
                -1 * UNIT, 1 * UNIT, 0,
                -1 * UNIT, -1 * UNIT, 0,
                1 * UNIT, 1 * UNIT, 0,
                1 * UNIT, -1 * UNIT, 0
        };

static float _dataTexCoor[] =
        {
                0 * TEXTURE_COOR_UNIT, 0 * TEXTURE_COOR_UNIT,
                0 * TEXTURE_COOR_UNIT, 1 * TEXTURE_COOR_UNIT,
                1 * TEXTURE_COOR_UNIT, 0 * TEXTURE_COOR_UNIT,
                1 * TEXTURE_COOR_UNIT, 1 * TEXTURE_COOR_UNIT
        };

static float _dataVertexFbo[] =
        {
                -1 * UNIT, 1 * UNIT, 0,
                -1 * UNIT, -1 * UNIT, 0,
                1 * UNIT, 1 * UNIT, 0,
                1 * UNIT, -1 * UNIT, 0
        };

static float _dataTexCoorFbo[] =
        {
                0 * TEXTURE_COOR_UNIT, 0 * TEXTURE_COOR_UNIT,
                0 * TEXTURE_COOR_UNIT, 1 * TEXTURE_COOR_UNIT,
                1 * TEXTURE_COOR_UNIT, 0 * TEXTURE_COOR_UNIT,
                1 * TEXTURE_COOR_UNIT, 1 * TEXTURE_COOR_UNIT
        };

#define UMVPMATRIX_NAME  "uMVPMatrix"
#define APOSITION_NAME  "aPosition"
#define ATEXCOOR_NAME  "aTexCoor"
#define TEXTURE_NAME  "texture"

//GL的环境信息类和全局变量
class GLContext
{

public:
    GLContext(int viewWidth , int viewHeight);

    ~GLContext();

    unsigned long colorBufferSize;

    FBOProgram *pFBOProgram;

    //整个GLview宽高
    int viewWidth;
    int viewHeight;

    //FBO矩阵
    float *maMVPMatrixFbo;

    //将FBO绘制到屏幕
    void drawFBO();

    //清空FBO已绘制的内容
    void clearFBO();

    //获取fbo ID
    GLuint getFramebufferId();

};

#endif

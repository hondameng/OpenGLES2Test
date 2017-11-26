//
// Created by mhd on 2017/8/25.
//
#include <jni.h>
#include <android/log.h>
#include "openglesrgb-jni.h"
#include "GLEngine.h"

static const std::string className = "cn/hongda/opengl/opengles/MyGLView";

struct fields_t {
    jfieldID context;
};

static struct fields_t gFields;

static int cn_hongda_opengl_opengles_MyGLView_init(JNIEnv *env, jobject obj)
{
    jclass clazz = env->FindClass(className.c_str());

    if (clazz == nullptr)
    {
        LOGE("can't find class %s", className.c_str());
        return -1;
    }

    gFields.context = env->GetFieldID(clazz, "mNativeContext", "J");
    if (nullptr == gFields.context)
    {
        LOGE("can't find field mNativeContext.");
        return 0;
    }
}

static GLEngine *getGLEngine(JNIEnv *env, jobject obj)
{
    return (GLEngine *)env->GetLongField(obj, gFields.context);
}

static int cn_hongda_opengl_opengles_MyGLView_changeLayout(JNIEnv *env, jobject obj ,jint width, jint height)
{
    GLEngine * glengine = new GLEngine();
    GLEngine *oldGLEngine = (GLEngine*) env->GetLongField(obj, gFields.context);

    if (oldGLEngine != nullptr)
    {
        delete oldGLEngine;
    }
    glengine->initGlContext(width, height);
    env->SetLongField(obj, gFields.context, (jlong) glengine);

    return 0;
}


//创建固定位置子view
static jlong cn_hongda_opengl_opengles_MyGLView_createStaticView(JNIEnv *env, jobject obj,
                                                  jint posX, jint posY,
                                                  jint realWidth, jint realHeight,
                                                  jint drawWidth, jint drawHeight)
{
    GLEngine *pGLEngine = getGLEngine(env,obj);
    if (pGLEngine != nullptr)
    {
        GLBaseView *pStaticView = pGLEngine->createStaticView(posX, posY, realWidth, realHeight,drawWidth, drawHeight);
        return (jlong)(pStaticView);
    } else
    {
        LOGE_EU("no this GLEngine instance");
        return -1;
    }
}

//创建滚动子view
static jlong cn_hongda_opengl_opengles_MyGLView_createScrollView(JNIEnv *env, jobject obj,
                                                jint posX, jint posY,
                                                jint realWidth, jint realHeight,
                                                jint drawWidth, jint drawHeight)
{
    GLEngine *pGLEngine = getGLEngine(env,obj);
    if (pGLEngine != nullptr)
    {
        GLBaseView *pScrollView = pGLEngine->createScrollView(posX, posY, realWidth, realHeight, drawWidth, drawHeight);
        return (jlong)(pScrollView);
    } else
    {
        LOGE("no this instance !");
        return -1;
    }
}

//绘制子view，包括固定位置的和滚动的
static int cn_hongda_opengl_opengles_MyGLView_drawSubFrame(JNIEnv *env, jobject obj,
                                                         jlong sHandle,
                                                         jbyteArray rgbDatas)
{
    GLEngine *pGLEngine = getGLEngine(env,obj);
    GLBaseView *pGLBaseView = (GLBaseView *) sHandle;
    if (pGLEngine == nullptr )
    {
        LOGE("no this GLEngine instance !");
        return -1;
    }
    if (pGLBaseView == nullptr )
    {
        LOGE("no this sub view instance !");
        return -1;
    }

    if(rgbDatas == NULL)
    {
        pGLEngine->drawGlView(pGLBaseView, false);
    } else
    {
        jbyte *srcp = env->GetByteArrayElements(rgbDatas, 0);
        memcpy(pGLBaseView->rgbBuffer, srcp, pGLBaseView->rgbBufferSize);
        pGLEngine->drawGlView(pGLBaseView,true);
        env->ReleaseByteArrayElements(rgbDatas, srcp, JNI_ABORT);
    }

    return 0;
}

//绘制FBO
static int cn_hongda_opengl_opengles_MyGLView_drawFBO(JNIEnv *env, jobject obj)
{

    GLEngine *pGLEngine = getGLEngine(env,obj);
    pGLEngine->drawFBOView();
    return 0;
}



//清空GL界面上的绘制结果
static int cn_hongda_opengl_opengles_MyGLView_clearView(JNIEnv *env, jobject obj)
{
    GLEngine *pGLEngine = getGLEngine(env,obj);
    pGLEngine->clearView();
    return 0;
}

//获取当前GL view上面的图像
static jbyteArray cn_hongda_opengl_opengles_MyGLView_getScreenFrame(JNIEnv *env, jobject obj)
{
    GLEngine *pGLEngine = getGLEngine(env,obj);
    if (pGLEngine == nullptr)
    {
        LOGE("no this instance!");
        return NULL;
    }
    signed char *respone_byte = pGLEngine->getScreenFrame();

    if (!respone_byte)
    {
        LOGE_EU("rgb respone_byte is null");
        return NULL;
    }
    jbyteArray byteArray = env->NewByteArray(pGLEngine->pGLContext->colorBufferSize);
    env->SetByteArrayRegion(byteArray, 0, pGLEngine->pGLContext->colorBufferSize, respone_byte);
    free(respone_byte);
    return byteArray;
}

//释放全部GL资源
static void cn_hongda_opengl_opengles_MyGLView_release(JNIEnv *env, jobject obj)
{
    GLEngine *pGLEngine = getGLEngine(env,obj);
    if (pGLEngine == nullptr)
    {
        LOGE("no this instance!");
        return;
    }
    delete pGLEngine;
    pGLEngine = NULL;
}

static const JNINativeMethod methods[] =
        {
                {"init", "()I", (void *) cn_hongda_opengl_opengles_MyGLView_init},
                {"changeLayout", "(II)I", (void *) cn_hongda_opengl_opengles_MyGLView_changeLayout},
                {"createStaticView", "(IIIIII)J", (void *) cn_hongda_opengl_opengles_MyGLView_createStaticView},
                {"createScrollView", "(IIIIII)J", (void *) cn_hongda_opengl_opengles_MyGLView_createScrollView},
                {"drawSubFrame", "(J[B)I", (void *) cn_hongda_opengl_opengles_MyGLView_drawSubFrame},
                {"drawFBO", "()I", (void *) cn_hongda_opengl_opengles_MyGLView_drawFBO},
                {"clearView", "()I", (void *) cn_hongda_opengl_opengles_MyGLView_clearView},
                {"release", "()V", (void *) cn_hongda_opengl_opengles_MyGLView_release},
                {"getScreenFrame", "()[B", (void *) cn_hongda_opengl_opengles_MyGLView_getScreenFrame},
        };

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env = NULL;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("GetEnv failed!");
        return JNI_VERSION_1_4;
    }

    jclass clazz;

    if ((clazz = env->FindClass(className.c_str())) == NULL)
    {
        LOGE("can't find class");
    }

    if (env->RegisterNatives(clazz, methods, sizeof(methods)/sizeof(methods[0])) != JNI_OK)
    {
        LOGE("can't register methods");
    }

    return JNI_VERSION_1_4;
}


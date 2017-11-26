LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := OpenGLES
LOCAL_SRC_FILES := \
                   opengles_fbo/gl_utils.cpp \
                   opengles_fbo/GLProgram.cpp \
                   opengles_fbo/FBOProgram.cpp \
                   opengles_fbo/GLTexture.cpp \
                   opengles_fbo/matrix.cpp \
                   opengles_fbo/GLContext.cpp \
                   opengles_fbo/GLBaseView.cpp \
                   opengles_fbo/GLStaticView.cpp \
                   opengles_fbo/GLScrollView.cpp \
                   opengles_fbo/GLEngine.cpp \
                   opengles_fbo/openglesrgb-jni.cpp

LOCAL_LDLIBS += -lGLESv2  -llog
LOCAL_STATIC_LIBRARIES += -lGLESv2
LOCAL_CFLAGS += -DGL_GLEXT_PROTOTYPES -std=c++11
include $(BUILD_SHARED_LIBRARY)

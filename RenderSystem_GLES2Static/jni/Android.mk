LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= RenderSystem_GLES2Static
LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/include
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../OgreMainStatic/jni/include
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/include/Android
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/src/GLSLES/include

LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES		:= 	compile_RenderSystem_GLES2_0.cpp
LOCAL_LDLIBS := -L$(LOCAL_PATH)/../lib 
LOCAL_LDLIBS += -ldl -llog -lgcc
include $(BUILD_STATIC_LIBRARY)

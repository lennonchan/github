LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= Plugin_ParticleFXStatic
LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/include
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../OgreMainStatic/jni/include

LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES		:= 	compile_Plugin_ParticleFX_0.cpp
LOCAL_LDLIBS := -L$(LOCAL_PATH)/../lib 
LOCAL_LDLIBS += -ldl -llog -lgcc
include $(BUILD_STATIC_LIBRARY)

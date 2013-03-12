LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= bfBlend
LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/include

LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES		:= 	fbtBlend.cpp Generated/bfBlender.cpp
LOCAL_LDLIBS := -L$(LOCAL_PATH)/../lib 
LOCAL_LDLIBS += -ldl -llog -lgcc
include $(BUILD_STATIC_LIBRARY)

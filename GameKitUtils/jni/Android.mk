LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= GameKitUtils
LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/
LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES		:= 	utRandom.cpp utScript.cpp utStreams.cpp utString.cpp
 LOCAL_LDLIBS		:= -L$(LOCAL_PATH)/../lib 
include $(BUILD_STATIC_LIBRARY)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= OgreMainStatic
LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/include
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/include/freetype
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../FreeImage/jni
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/src/nedmalloc
LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES		:= 	src/OgreAlignedAllocator.cpp compile_OgreMain_0.cpp compile_OgreMain_1.cpp compile_OgreMain_2.cpp compile_OgreMain_3.cpp compile_OgreMain_4.cpp
LOCAL_LDLIBS := -L$(LOCAL_PATH)/../lib 
LOCAL_LDLIBS += -ldl -llog -lgcc
include $(BUILD_STATIC_LIBRARY)

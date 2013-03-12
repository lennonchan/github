LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= AnimKit
LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/../../GameKitUtils/jni $(LOCAL_PATH)/../../OgreMainStatic/jni/include
LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES		:= 	akAnimationBlender.cpp akAnimationChannel.cpp akAnimationPlayer.cpp akAnimationSequence.cpp akBezierSpline.cpp akKeyedAnimation.cpp
 LOCAL_LDLIBS := -L$(LOCAL_PATH)/../lib 
 LOCAL_LDLIBS += -ldl -llog -lgcc
include $(BUILD_STATIC_LIBRARY)

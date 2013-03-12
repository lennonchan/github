LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= OIS
LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/include
LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES		:= 	src/OISEffect.cpp src/OISException.cpp src/OISForceFeedback.cpp src/OISInputManager.cpp src/OISJoyStick.cpp src/OISKeyboard.cpp src/OISObject.cpp src/android/AndroidInputManager.cpp
 LOCAL_LDLIBS := -L$(LOCAL_PATH)/../lib 
 LOCAL_LDLIBS += -ldl -llog -lgcc
include $(BUILD_STATIC_LIBRARY)

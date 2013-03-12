LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LUA = lapi.c lauxlib.c lbaselib.c lcode.c ldblib.c ldebug.c ldo.c ldump.c lfunc.c lgc.c linit.c liolib.c llex.c lmathlib.c lmem.c loadlib.c lobject.c lopcodes.c loslib.c lparser.c lstate.c lstring.c lstrlib.c ltable.c ltablib.c ltm.c lua.c luac.c lundump.c lvm.c lzio.c print.c

LOCAL_MODULE := lua

LOCAL_ARM_MODE   := arm
LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES := $(LUA)

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/


LOCAL_LDLIBS += -L$(LOCAL_PATH)/libs 
LOCAL_LDLIBS += -ldl -llog -lgcc

include $(BUILD_SHARED_LIBRARY)

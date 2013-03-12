LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= ZLib
LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/
LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES		:= 	adler32.c compress.c crc32.c deflate.c gzio.c infback.c inffast.c inflate.c inftrees.c trees.c uncompr.c zutil.c
 LOCAL_LDLIBS := -L$(LOCAL_PATH)/../lib 
 LOCAL_LDLIBS += -ldl -llog -lgcc
include $(BUILD_STATIC_LIBRARY)

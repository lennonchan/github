LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE		:= OgreKitCore
LOCAL_C_INCLUDES	:= $(LOCAL_PATH)/
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../OgreMainStatic/jni/include
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../GameKitUtils/jni
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../bullet/jni
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../AnimKit/jni
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../OIS/jni/include
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../OgreRTShaderSystemStatic/jni/include
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../RenderSystem_GLES2Static/jni/include
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../Plugin_ParticleFXStatic/jni/include
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../bfBlend/jni/include
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../bfBlend/jni/
#LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/../../lua/jni/include
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/Android
#LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/Physics
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/LogicBricks
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/Loaders/Blender2
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/Animation
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/Logic
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/Particles
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/Graphics
LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/Constraints
#LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/AI
#LOCAL_C_INCLUDES	+= $(LOCAL_PATH)/Script/Api

LOCAL_CFLAGS := -O3 -DANDROID_NDK -DOut_API

LOCAL_SRC_FILES		:= 	gkWindowSystem.cpp Thread/gkSyncObj.cpp compile_OgreKitCore_0.cpp compile_OgreKitCore_1.cpp compile_OgreKitCore_2.cpp compile_OgreKitCore_3.cpp compile_OgreKitCore_4.cpp 
LOCAL_LDLIBS := -L$(LOCAL_PATH)/../lib 
LOCAL_LDLIBS += -ldl -llog -lgcc
include $(BUILD_STATIC_LIBRARY)

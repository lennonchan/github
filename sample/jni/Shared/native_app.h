#ifndef NATIVE_APP_H
#define NATIVE_APP_H

#include <jni.h>
#define UNUSED  __attribute__((unused))

JavaVM* vmPointer;
jboolean native_start(JNIEnv *env, jclass clazz, jstring jPackageName, jint w, jint h);
jboolean native_gl_resize(JNIEnv *env, jclass clazz, jint w, jint h);
jboolean native_gl_render(JNIEnv *env, jclass clazz);

jboolean keyEvent(JNIEnv* env, jobject thiz, jint action, jint unicodeChar, jint keyCode, jobject keyEvent);
jboolean inputEvent(JNIEnv* env, jobject thiz, jint action, jfloat mx, jfloat my);
void native_destroy(JNIEnv *env, jclass clazz);
void sendMessage(JNIEnv *env, jclass thiz, jstring jfrom, jstring jto, jstring jsubject, jstring jbody);

void sendSensor(JNIEnv *env, jclass thiz, jint type, jfloat x, jfloat y, jfloat z);
void setOffsets(JNIEnv* env, jobject thiz, jint x, jint y);


void cleanup(JNIEnv* env);


#endif

#define LOG_TAG    "OgreKit"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOG_FOOT   LOGI("%s %s %d", __FILE__, __FUNCTION__, __LINE__)


jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
//	EXPORT_JNI_OnLoad(vm,reserved);

	JNIEnv *env;

	vmPointer = vm;

    LOGI("JNI_OnLoad called");
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
    {
    	LOGE("Failed to get the environment using GetEnv()");
        return -1;
    }
    JNINativeMethod methods[] =
    {
		{
            "native_start",
            "(Ljava/lang/String;II)Z",
            (void *) native_start
        },
        {
        	"native_gl_resize",
			"(II)Z",
			(void *) native_gl_resize
        },
        {
        	"native_gl_render",
			"()Z",
			(void *) native_gl_render
        },
        {
			"inputEvent",
			"(IFFLandroid/view/MotionEvent;)Z",
			(void *) inputEvent

        },
        {
            "keyEvent",
            "(IIILandroid/view/KeyEvent;)Z",
            (void *) keyEvent
        },
        {
            "cleanup",
            "()V",
            (void *) cleanup
        },
		{
			"setOffsets",
			"(II)V",
			(void *) setOffsets
		},
		{
			"sendSensor",
			"(IFFF)V",
			(void *) sendSensor
		},
		{
			"sendMessage",
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V",
			(void *) sendMessage
		}

    };
    jclass k;
    //k = (env)->FindClass ("com/tcl/UIEngine/MainView");
	k = (env)->FindClass ("com/tcl/UIEngine/GL2JNILib");
    (env)->RegisterNatives(k, methods, 9);

    return JNI_VERSION_1_4;
}

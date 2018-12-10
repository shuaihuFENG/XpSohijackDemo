//
// Created by i-fengshuaihu on 2018/12/7.
//

#include <jni.h>
#include <string>
#include "inlineHook/include/log.h"

extern "C"
jstring getString(JNIEnv *env,jobject jobject,jstring preString){
    std::string hello = "Hello from C++";
    int preLen = env->GetStringLength(preString);
    int length = preLen + hello.length();
    const char *preStr = env->GetStringUTFChars(preString,0);
    char resultString[128] = {0};
    sprintf(resultString,"%s%s",preStr,hello.c_str());
    return env->NewStringUTF(resultString);
}

static JNINativeMethod gMethod[] = {
        {"stringFromJNI","(Ljava/lang/String;)Ljava/lang/String;",(void *)getString},
};

extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("enter tarSo : JNI_OnLoad");
    JNIEnv * env = NULL;
    if(vm->GetEnv((void **)&env,JNI_VERSION_1_6)!=JNI_OK){
        return -1;
    }
    assert(env!=NULL);
    const char *clazzName = "com/chcd/xpsohijackdemo/MainActivity";
    jclass clazz = env->FindClass(clazzName);
    if(env->RegisterNatives(clazz,gMethod, sizeof(gMethod)/ sizeof(JNINativeMethod))<0){
        return -1;
    }
    return JNI_VERSION_1_6;
}




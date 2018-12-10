//
// Created by i-fengshuaihu on 2018/12/7.
//

#include <jni.h>
#include <string>
#include <sys/stat.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/log.h"
#include "include/inlineHook.h"

char* tarSoPath = "/data/data/com.chcd.xpsohijackdemo/lib/libaddHello.so";

void* old_getString = NULL;
jstring (*FUN_getString)(JNIEnv *env,jobject jobject,jstring preString);

jstring new_getString(JNIEnv *env,jobject jobject,jstring preString)
{
    LOGD("enter new_getString");
    preString = env->NewStringUTF("after hook:");
    return FUN_getString(env,jobject,preString);
}


int hook();

jint hookAndLoadTarSo(char *soFilePath,JavaVM* vm, void* reserved){
    jint ret;
    void *pHandle = NULL;
    pHandle = dlopen(soFilePath,RTLD_LAZY);
    if(pHandle == NULL){
        LOGD("dlopen %s error",soFilePath);
        return NULL;
    }
    typedef jint (*FUN_JniOnLoad)(JavaVM *vm,void* reserved);
    FUN_JniOnLoad old_jniOnLoad = (FUN_JniOnLoad) dlsym(pHandle, "JNI_OnLoad");
    if(old_jniOnLoad == NULL){
        LOGD("tarSo：JNI_OnLoad is null");
        return -1;
    }
    old_getString = dlsym(pHandle,"getString");
    if(old_getString == NULL){
        LOGD("tarSo：getString is null");
        return -1;
    }
    int success = hook();
    if(success != 0){
        LOGD("Hook getString failed");
    }
    LOGD("old_JNI_OnLoad address = %X",old_jniOnLoad);
    ret = old_jniOnLoad(vm,reserved);
    LOGD("old_JNI_OnLoad end -> %d",ret);
    return ret;
}

int hook(){
    if (registerInlineHook((uint32_t) old_getString, (uint32_t)new_getString , (uint32_t **) &FUN_getString) != ELE7EN_OK) {
        return -1;
    }
    if (inlineHook((uint32_t) old_getString) != ELE7EN_OK) {
        return -1;
    }
    return 0;
}

extern "C"
JNIIMPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *pvt){
    LOGD("enter hookSo : JNI_OnLoad ");
    JNIEnv * env = NULL;
    LOGD("before enter getenv : JNI_OnLoad ");
    if(vm->GetEnv((void **) &env, JNI_VERSION_1_6)!=JNI_OK){
        LOGD("ERROR:GETENV failed");
        return -1;
    }
    LOGD("env:%X",env);
    hookAndLoadTarSo(tarSoPath, vm, pvt);
    LOGD("hookSo:JNI_OnLoad will be end");
    return JNI_VERSION_1_6;
}
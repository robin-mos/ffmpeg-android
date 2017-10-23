#include <jni.h>

#ifndef _INCLUDED_UTILS_H_
#define _INCLUDED_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

char* jstring2string(JNIEnv *env, jstring jpath){
	char *path = 0;
	//find class
	jclass classString = (*env)->FindClass(env,"java/lang/String");
	jstring jtmp = (*env)->NewStringUTF(env,"utf-8");
	//get method id
	jmethodID jmid = (*env)->GetMethodID(env,classString,"getBytes","(Ljava/lang/String;)[B");
	//call getbytes() method
	jbyteArray byteArray = (*env)->CallObjectMethod(env,jpath,jmid,jtmp);
	jsize strlen = (*env)->GetArrayLength(env,byteArray);
	jbyte *jBuf = (*env)->GetByteArrayElements(env,byteArray,JNI_FALSE);
	if(0 < jBuf){
		path = (char*)malloc(strlen + 1);
		if(!path){
			return 0;
		}
		memcpy(path,jBuf,strlen);
		path[strlen] = 0;
	}
	(*env)->ReleaseByteArrayElements(env,byteArray,jBuf,0);
	return path;
}


jstring char2jstring(JNIEnv *env,const char *str){
	jclass clazz = (*env)->FindClass(env,"Ljava/lang/String");
	jmethodID mid =(*env)->GetMethodID(env,clazz,"<init>","([BLjava/lang/String;)V");
	jbyteArray byteArray = (*env)->NewByteArray(env,strlen(str));
	(*env)->SetByteArrayRegion(env,byteArray,0,strlen(str),str);
      return (jstring)((*env)->NewObject(env,clazz ,mid,byteArray,(*env)->NewStringUTF(env,"utf-8")));
}

#ifdef __cplusplus
}
#endif
#endif


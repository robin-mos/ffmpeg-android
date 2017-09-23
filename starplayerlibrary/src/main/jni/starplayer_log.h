#include <android/log.h>

#ifndef _INCLUDED_STAR_PLAYER_LOG_H_
#define _INCLUDED_STAR_PLAYER_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TAG "==Start Player=="
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__);
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__);
#define LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,TAG,__VA_ARGS__);
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);



#ifdef __cplusplus
}
#endif
#endif




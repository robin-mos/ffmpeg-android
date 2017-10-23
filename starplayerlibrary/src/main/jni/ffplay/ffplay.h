#ifndef __FFPLAY_H__
#define __FFPLAY_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "starplayer_log.h"

typedef void (*timeStampCallBack)(int,int ,int,int);

timeStampCallBack mTimeStampCallBack;

int android_main(int argc, char **argv);

void setTimeStamp(timeStampCallBack callback);

#ifdef __cplusplus
}
#endif

#endif
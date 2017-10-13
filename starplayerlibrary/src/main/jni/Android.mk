LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := avcodec
LOCAL_SRC_FILES := ffmpeg/lib/libavcodec-57.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avdevice
LOCAL_SRC_FILES :=ffmpeg/lib/libavdevice-57.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avfilter
LOCAL_SRC_FILES :=ffmpeg/lib/libavfilter-6.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avformat
LOCAL_SRC_FILES := ffmpeg/lib/libavformat-57.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE  := avutil
LOCAL_SRC_FILES := ffmpeg/lib/libavutil-55.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := postproc
LOCAL_SRC_FILES :=ffmpeg/lib/libpostproc-54.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := swresample
LOCAL_SRC_FILES := ffmpeg/lib/libswresample-2.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avresample
LOCAL_SRC_FILES := ffmpeg/lib/libavresample-3.so
include $(PREBUILT_SHARED_LIBRARY)
include $(CLEAR_VARS)
LOCAL_MODULE := swscale
LOCAL_SRC_FILES := ffmpeg/lib/libswscale-4.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := SDL2
LOCAL_SRC_FILES := sdl/lib/libSDL2.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := starplayer
LOCAL_INCLUDE += $(LOCAL_PATH)/ffmpeg/include  \
				$(LOCAL_PATH)/ffmpeg/cmdutils.h  \
                $(LOCAL_PATH)/ffmpeg/compat  \
                 $(LOCAL_PATH)/sdl/include
LOCAL_SRC_FILES := StarPlayer.c  \
					ffplay/ffplay.c \
                    ffmpeg/cmdutils.c
LOCAL_LDLIBS += -llog -lm -lz -landroid
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/ffmpeg/include
LOCAL_SHARED_LIBRARIES := avformat \
                        avcodec \
                        avdevice \
                        avfilter \
                        avutil \
                        postproc \
                        swresample \
                        avresample  \
                        swscale \
						avresample  \
                        SDL2

include $(BUILD_SHARED_LIBRARY)


#
# ffplay shared library
#
#include $(CLEAR_VARS)
#LOCAL_MODULE    := ffplay
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/ffmpeg/cmdutils.h  \
 #               $(LOCAL_PATH)/ffmpeg/include \
  #              $(LOCAL_PATH)/ffmpeg/compat  \
   #              $(LOCAL_PATH)/sdl/include
#
#LOCAL_SRC_FILES := ffplay/ffplay.c \
 #                   ffmpeg/cmdutils.c
#LOCAL_LDLIBS += -llog -lm -lz -landroid
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/ffmpeg/include
#LOCAL_SHARED_LIBRARIES := avformat \
 #                       avcodec \
  #                      avdevice \
   #                     avfilter \
    #                    avutil \
     #                   postproc \
      #                  swresample \
       #                 swscale  \
        #                avresample  \
         #               SDL2
#
#include $(BUILD_SHARED_LIBRARY)





#include <string.h>
#include <stdio.h>
#include "com_robin_starplayer_media_StarPlayerSystem.h"
#include "ffmpeg/include/libavcodec/avcodec.h"
#include "ffmpeg/include/libavformat/avformat.h"
#include "ffmpeg/include/libswscale/swscale.h"
#include "ffmpeg/include/libavutil/error.h"
#include "starplayer_log.h"
#include "utils.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>

char *path;

/*
 * Class:     com_robin_starplayer_media_StarPlayerSystem
 * Method:    onStart
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_robin_starplayer_media_StarPlayerSystem_onStart
  (JNIEnv *env, jclass jClass){

         return 0;
    }

/*
 * Class:     com_robin_starplayer_media_StarPlayerSystem
 * Method:    onPause
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_robin_starplayer_media_StarPlayerSystem_onPause
  (JNIEnv *env, jclass jClass){
      return 0;
  }

/*
 * Class:     com_robin_starplayer_media_StarPlayerSystem
 * Method:    onStop
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_robin_starplayer_media_StarPlayerSystem_onStop
  (JNIEnv *env, jclass jClass){

  return 0;
  }

  /*
   * Class: 	com_robin_starplayer_media_StarPlayerSystem
   * Method:	configuration
   * Signature: ()I
   */

  JNIEXPORT jstring JNICALL Java_com_robin_starplayer_media_StarPlayerSystem_cofiguration(JNIEnv *env, jclass jClass){
    char info[1000] = {0};
    LOGE("ffmpeg configuration");
    sprintf(info,"%s\n",avcodec_configuration());
   // sprintf(info,"%s\n",avcodec_version());
    return (*env)->NewStringUTF(env, info);
  }

  /*
   * Class: 	com_robin_starplayer_media_StarPlayerSystem
   * Method:	version
   * Signature: ()I
   */
  JNIEXPORT jint JNICALL Java_com_robin_starplayer_media_StarPlayerSystem_version(JNIEnv *env, jclass jclass){
     LOGE("ffmpeg version");
    return avcodec_version();
  }

  
  JNIEXPORT jint JNICALL Java_com_robin_starplayer_media_StarPlayerSystem_setPath(JNIEnv *env, jclass jclass,jstring jpath){
	path = jstring2string(env ,jpath);
	LOGE("路径设置:%s",path);
	return 0;
  }

  /*
   * Class: 	com_robin_starplayer_media_StarPlayerSystem
   * Method:	prepare
   * Signature: ()I
   * return 
   */
  JNIEXPORT jint JNICALL Java_com_robin_starplayer_media_StarPlayerSystem_prepare(JNIEnv *env, jclass jclass,jobject surface){
	LOGE("prepare : %s\n",path);

	if(!path){
		return -1;
    	}
    av_register_all();
	avcodec_register_all();
	AVFormatContext *pFormatContext = avformat_alloc_context();

    LOGE("step avformat_open_input");
      //open video file
      int ret = avformat_open_input(&pFormatContext,path,0,0);
	  LOGE("avformat_open_input:%d\n",ret);
      if(0 != ret){
	  	char buf[] = "";
		av_strerror(ret,buf,1024);
		LOGE("open file error:%s\n",buf);
		return -1;
	}
    LOGE("avformat_find_stream_info");
       //find video stream information
	  if(0 != avformat_find_stream_info(pFormatContext,0)){
		LOGE("find stream format error\n");
		return -1;
	  }

	  int videoStream = -1;
	  int i;
	  for(i =0;i < pFormatContext->nb_streams;i++){
		if(pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO
			&& videoStream < 0) {
			videoStream = i;
		}
	  }

	  if(-1 == videoStream){
		LOGE("don't find video stream\n");
		return -1;
	  }

	  AVCodecContext *pCodecContext = pFormatContext->streams[videoStream]->codec;
	  AVCodec *pCodec = avcodec_find_decoder(pCodecContext->codec_id);
	  if(0 == pCodec){
		LOGE("cann't found codec\n");
		return -1;
	  }

	  if(avcodec_open2(pCodecContext,pCodec,0) < 0){
		LOGE("cann't open codec\n");
		return -1;
	  }

	  

    //native window
    ANativeWindow *nativeWindow = ANativeWindow_fromSurface(env,surface);

    int videoWidth = pCodecContext->width;
    int videoHeight = pCodecContext->height;
	//set buffer size
    ANativeWindow_setBuffersGeometry(nativeWindow,videoWidth,videoHeight,WINDOW_FORMAT_RGBA_8888);
    ANativeWindow_Buffer nativeWindowBuffer;

    if(avcodec_open2(pCodecContext,pCodec,0) < 0){
	LOGE("cann't find codec\n");
	return -1;
	}

	//video frame
	AVFrame * pFrame = av_frame_alloc();
       //
	AVFrame *pFrameRgb = av_frame_alloc();
	if(0==pFrame || 0 == pFrameRgb){
		LOGE("cann't alloc video frame");
		return -1;
	}

	int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGBA,
		pCodecContext->width,pCodecContext->height,1);
	uint8_t *buffer = (uint8_t*)av_malloc(numBytes*sizeof(uint8_t));
	av_image_fill_arrays(pFrameRgb->data,pFrameRgb->linesize,buffer,
		AV_PIX_FMT_RGBA,pCodecContext->width,pCodecContext->height,1);

	struct SwsContext *pSwsContext = sws_getContext(pCodecContext->width,
		pCodecContext->height,pCodecContext->pix_fmt,
		pCodecContext->width,pCodecContext->height,
		AV_PIX_FMT_RGBA,SWS_BILINEAR,
		0,0,0);

	int frameFinish;
	AVPacket packet;
	LOGE("av_read_frame videoStream:%d",videoStream);
	
	while(0 == (ret =av_read_frame(pFormatContext,&packet))){
		LOGE("av_read_frame ret =%d",ret);
		if(packet.stream_index == videoStream){
			//decode video frame
			LOGE("avcodec_decode_video2");
			avcodec_decode_video2(pCodecContext,pFrame,&frameFinish,&packet);
			LOGE("frame finish %d",frameFinish);
			
			if(frameFinish){
			     ret = ANativeWindow_lock(nativeWindow,&nativeWindowBuffer,0);
				 LOGE("ANativeWindow_lock ret=%d",ret);
				 if(0 == ret){
			      sws_scale(pSwsContext,(const uint8_t *)pFrame->data,pFrame->linesize,0,pCodecContext->height,pFrameRgb->data,pFrameRgb->linesize);
				uint8_t * dst =nativeWindowBuffer.bits;
				int dstStride = nativeWindowBuffer.stride*4;
				uint8_t *src = (uint8_t*)(pFrameRgb->data[0]);
				int srcStride = pFrameRgb->linesize[0];

				//
				int h;
				for(h =0;h < videoHeight;h++){
					memcpy(dst+h*dstStride,src+srcStride*h,srcStride);
				}
				ANativeWindow_unlockAndPost(nativeWindow);
				}else{
					break;
				}
			}
		}
		av_packet_unref(&packet);
	}
	LOGE("av_read_frame end ret =%d",ret);

	LOGE("free close");
	free(buffer);
	free(pFrameRgb);
	free(pFrame);
	avcodec_close(pCodecContext);
	avformat_close_input(&pFormatContext);

	return 0;
  }




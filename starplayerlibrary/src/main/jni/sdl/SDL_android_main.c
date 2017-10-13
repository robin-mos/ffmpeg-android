/*
    SDL_android_main.c, placed in the public domain by Sam Lantinga  3/13/14

    As of SDL 2.0.6 this file is no longer necessary.
*/

/* vi: set ts=4 sw=4 expandtab: */
#include <stdio.h>
#include <android/log.h>

int main(int argc, char *argv[]){
	__android_log_print(ANDROID_LOG_ERROR,"sdl_android_main","main");

	return 0;
}

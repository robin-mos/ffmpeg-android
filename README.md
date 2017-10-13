# ffmpeg-android
ffmpeg源码编译so库请参考 https://github.com/lixiangpingzml/ffmpeg-android-lib

ffmpeg编解码学习,android平台

视频资源路径：Environment.getExternalStorageDirectory().getAbsolutePath()+"/ftest"。 在手机内置存储目录下面新建文件夹ftest，里面存放视频文件，目前只过滤mp4、mkv、264后缀的格式

1.验证编解码一帧帧图片在android ANativeWindow上面绘制，目前没有时间戳

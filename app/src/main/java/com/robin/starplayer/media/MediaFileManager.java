package com.robin.starplayer.media;

import android.content.ContentResolver;
import android.content.Context;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Environment;
import android.provider.MediaStore;

import com.robin.starplayer.debug.LogUtils;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

/**
 * Created by robin on 2017/9/20.
 */

public class MediaFileManager {
    private static final String regex = "^/.{1,}.(mp4|264|mkv|flv)$";

    public static ArrayList<String> getVideoInfo(Context context){
        Pattern mVideoPattern = Pattern.compile(regex);
        String path = Environment.getExternalStorageDirectory().getAbsolutePath()+"/ftest";
        File f = new File(path);
        ArrayList<String> videoList = new ArrayList<String>();
        if(null == f || !f.exists()){
            f.mkdirs();
        }else{
            File[] files =  f.listFiles();
            if(null != files && 0 < files.length){
                for(File ff:files){
                    LogUtils.e(ff.getAbsolutePath());
                    if(mVideoPattern.matcher(ff.getAbsolutePath()).matches()){
                        videoList.add(ff.toString());
                    }
                }
            }
        }

        return videoList;
    }

    public static ArrayList<String> getVideoPath(Context context){
        String[] thumbColumns = new String[]{
                MediaStore.Video.Thumbnails.DATA,
                MediaStore.Video.Thumbnails.VIDEO_ID
        };

        String[] mediaColumns = new String[]{
                MediaStore.Video.Media.DATA,
                MediaStore.Video.Media._ID,
                MediaStore.Video.Media.TITLE,
                MediaStore.Video.Media.MIME_TYPE
        };

        //首先检索SDcard上所有的video
        Cursor cursor = context.getContentResolver().query(MediaStore.Video.Media.EXTERNAL_CONTENT_URI, mediaColumns, null, null, null);

        ArrayList<String> videoList = new ArrayList<String>();

        if(cursor.moveToFirst()){
            do{
                VideoInfo info = new VideoInfo();

                info.filePath = cursor.getString(cursor.getColumnIndexOrThrow(MediaStore.Video.Media.DATA));
                info.mimeType = cursor.getString(cursor.getColumnIndexOrThrow(MediaStore.Video.Media.MIME_TYPE));
                info.title = cursor.getString(cursor.getColumnIndexOrThrow(MediaStore.Video.Media.TITLE));

                //获取当前Video对应的Id，然后根据该ID获取其Thumb
                int id = cursor.getInt(cursor.getColumnIndexOrThrow(MediaStore.Video.Media._ID));
                String selection = MediaStore.Video.Thumbnails.VIDEO_ID +"=?";
                String[] selectionArgs = new String[]{
                        id+""
                };
                Cursor thumbCursor = context.getContentResolver().query(MediaStore.Video.Thumbnails.EXTERNAL_CONTENT_URI, thumbColumns, selection, selectionArgs, null);

                if(thumbCursor.moveToFirst()){
                    info.thumbPath = cursor.getString(cursor.getColumnIndexOrThrow(MediaStore.Video.Thumbnails.DATA));

                }
                LogUtils.e("文件路径:"+info.filePath+",title:"+info.title);
                //然后将其加入到videoList
                videoList.add(info.filePath);

            }while(cursor.moveToNext());
        }
        return videoList;
    }

   public static class VideoInfo{
        String filePath;
        String mimeType;
        String thumbPath;
        String title;
    }
}


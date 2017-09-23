package com.robin.starplayer.ui.activity;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.text.TextUtils;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.robin.starplayer.R;
import com.robin.starplayer.debug.LogUtils;
import com.robin.starplayer.media.StarPlayerSystem;

/**
 * Created by robin on 2017/9/20.
 */

public class PlayerActivity extends Activity implements SurfaceHolder.Callback {
    private SurfaceView mPlayerSurfaceView;

    private String mPath;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_player);
        mPath = getIntent().getStringExtra(StarPlayerSystem.EXTERN_PATH);
        LogUtils.e("播放界面,视频路径:" + mPath);
        init();

    }

    private void init() {
        mPlayerSurfaceView = (SurfaceView) findViewById(R.id.player_surfaceview);
            SurfaceHolder holder = mPlayerSurfaceView.getHolder();
            if (null != holder) {
                holder.addCallback(this);
            }
    }


    @Override
    public void surfaceCreated(final SurfaceHolder holder) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                if (!TextUtils.isEmpty(mPath)) {
                    StarPlayerSystem.setPath(mPath);
                    StarPlayerSystem.prepare(holder.getSurface());
                }
            }
        }).start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }
}

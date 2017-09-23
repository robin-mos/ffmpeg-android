package com.robin.starplayer.ui.activity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.support.constraint.solver.ArrayLinkedVariables;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import com.robin.starplayer.R;
import com.robin.starplayer.debug.LogUtils;
import com.robin.starplayer.media.MediaFileManager;
import com.robin.starplayer.media.StarPlayerSystem;

import java.util.ArrayList;
import java.util.Objects;

public class MainActivity extends Activity {
    private ListView mMediaListView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ((TextView)findViewById(R.id.version)).setText("\n version:"+StarPlayerSystem.version());
        mMediaListView = (ListView) findViewById(R.id.media_list);
        mediaScan();
    }

    private void startPlayer(String path){
        Intent intent = new Intent();
        intent.setClass(this,PlayerActivity.class);
        intent.putExtra(StarPlayerSystem.EXTERN_PATH,path);
        startActivity(intent);
    }

    private void mediaScan(){
        new Thread(new Runnable() {
            @Override
            public void run() {
                 ArrayList<String> paths = MediaFileManager.getVideoInfo(MainActivity.this);
                final String[] pathStrs = new String[paths.size()];
                for(int i=0;i<paths.size();i++){
                    pathStrs[i] = paths.get(i);
                }
                mMediaListView.setAdapter(new ArrayAdapter<String>(MainActivity.this,android.R.layout.simple_list_item_1,pathStrs));
                mMediaListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
                    @Override
                    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                        LogUtils.e("选择的视频文件:"+pathStrs[position]);
                        startPlayer(pathStrs[position]);
                    }
                });
            }
        }).start();
    }
}

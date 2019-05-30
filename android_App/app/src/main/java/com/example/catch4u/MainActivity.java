package com.example.catch4u;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.net.Uri;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.MediaController;
import android.widget.Toast;
import android.widget.VideoView;

import static android.app.PendingIntent.FLAG_UPDATE_CURRENT;

public class MainActivity extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {
    DrawerLayout drawerLayout;
    NavigationView navigationView;
    ActionBarDrawerToggle drawerToggle;
    Toolbar toolbar;



    @Override

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initLayout();

       SharedPreferences pref = getSharedPreferences("pref", 0); //저장된거 불러오기
        final String ip = pref.getString("stream", null); //저장된 문자
//        String ip = "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov";
 //       Log.e("test!", ip);


        final VideoView v = (VideoView) findViewById( R.id.videoView );
        v.setVideoURI( Uri.parse(ip) );
        Toast.makeText(this, ip, Toast.LENGTH_LONG).show();
        v.setMediaController( new MediaController( this ) );
        v.requestFocus();
        v.start();

        SharedPreferences preferences = getSharedPreferences("msg", 0); //저장된거 불러오기
        final String sms = preferences.getString("sent", null); //저장된 문자
        final String phonenum = "01091726892";
        Button call = (Button) findViewById(R.id.button1); //버튼
        call.setOnClickListener(new View.OnClickListener() { //버튼 누르면
            @Override
            public void onClick(View view) {
                Uri uri = Uri.parse("smsto:112");
                Intent sendintent = new Intent(Intent.ACTION_SENDTO, uri);
                sendintent.putExtra("sms_body", sms);
                startActivity(sendintent); //
               /*try {
                    //전송
                    SmsManager smsManager = SmsManager.getDefault();
                    smsManager.sendTextMessage(phonenum, null, sms, null, null);
                    Toast.makeText(getApplicationContext(), "전송 완료!", Toast.LENGTH_LONG).show();
                } catch (Exception e) {
                    Toast.makeText(getApplicationContext(), "SMS failed, please try again later!", Toast.LENGTH_LONG).show();
                    e.printStackTrace();
                }
                // if(ContextCompat.checkSelfPermission(this,Manifest.permission.READ_PHONE_STATE)==)
            }*/
            }
        });


        NotificationManager notificationManager = (NotificationManager) MainActivity.this.getSystemService(MainActivity.this.NOTIFICATION_SERVICE);
        Intent intent1 = new Intent(MainActivity.this.getApplicationContext(), MainActivity.class); //인텐트 생성.

        Notification.Builder builder = new Notification.Builder(getApplicationContext());
        intent1.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP | Intent.FLAG_ACTIVITY_CLEAR_TOP); // 현재 액티비티를 최상으로 올리고, 최상의 액티비티를 제외한 모든 액티비티를 없앤다.
        PendingIntent pendingNotificationIntent = PendingIntent.getActivity(MainActivity.this, 0, intent1, FLAG_UPDATE_CURRENT);
        // PendingIntent는 일회용 인텐트 같은 개념입니다.


        builder.setSmallIcon(R.drawable.ss).setTicker("HETT").setWhen(System.currentTimeMillis())
                .setNumber(1).setContentTitle("위험감지!").setContentText("지금 당장 영상을 확인 해보세요")
                .setDefaults(Notification.DEFAULT_SOUND | Notification.DEFAULT_VIBRATE).setContentIntent(pendingNotificationIntent).setAutoCancel(true).setOngoing(true);
          /* FLAG_UPDATE_CURRENT - > 만일 이미 생성된 PendingIntent가 존재 한다면, 해당 Intent의 내용을 변경함.
                FLAG_CANCEL_CURRENT - .이전에 생성한 PendingIntent를 취소하고 새롭게 하나 만든다.
                FLAG_NO_CREATE -> 현재 생성된 PendingIntent를 반환합니다.
                FLAG_ONE_SHOT - >이 플래그를 사용해 생성된 PendingIntent는 단 한번밖에 사용할 수 없습니다*/

        //해당 부분은 API 4.1버전부터 작동합니다.
        //setSmallIcon - > 작은 아이콘 이미지
        //setTicker - > 알람이 출력될 때 상단에 나오는 문구.
        //setWhen -> 알림 출력 시간.
        //setContentTitle-> 알림 제목
        //setConentText->푸쉬내용

        notificationManager.notify(1, builder.build()); // Notification send


    }


             //   @Override
                public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                    switch(item.getItemId()) {
                        case R.id.gallery:
                            Intent gaIntent = new Intent(this, GalleryActivity.class);
                            startActivity(gaIntent);
                          //  Toast.makeText(this, "item1 clicked..", Toast.LENGTH_SHORT).show();
                            break;
                        case R.id.setting:
                            Intent settingIntent = new Intent(this, SettingActivity.class);
                            startActivity(settingIntent);
                            //Toast.makeText(this, "item2 clicked..", Toast.LENGTH_SHORT).show();
                            break;
                        case R.id.send:
                            Intent sending = new Intent(this, SendMessageActivity.class);
                            startActivity(sending);
                           // Toast.makeText(this, "item3 clicked..", Toast.LENGTH_SHORT).show();
                            break;
                    }


                    drawerLayout.closeDrawer(GravityCompat.START);
                    return false;
                }

    @Override
    protected void onPostCreate(Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);
        // Sync the toggle state after onRestoreInstanceState has occurred.
        drawerToggle.syncState();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        drawerToggle.onConfigurationChanged(newConfig);
    }
   /* @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.gallery:
                // Toast.makeText(this, "버튼을 눌렀습니다.", Toast.LENGTH_SHORT).show();
                //Intent sending = new Intent(this, SendMessageActivity.class);
                //startActivity();
                break;
            case R.id.setting:
                Intent settingIntent = new Intent(this, SettingActivity.class);
                startActivity(settingIntent);
                //Toast.makeText(this, "버튼1을 눌렀습니다.", Toast.LENGTH_SHORT).show();
                break;
            case R.id.send:
                // Toast.makeText(this, "버튼을 눌렀습니다.", Toast.LENGTH_SHORT).show();
                Intent sending = new Intent(this, SendMessageActivity.class);
                startActivity(sending);
                break;
            default:
                break;
        }
        return true;
    }*/

   public boolean onOptionsItemSelected(MenuItem item) {
       // Pass the event to ActionBarDrawerToggle, if it returns
       // true, then it has handled the app icon touch event
       if (drawerToggle.onOptionsItemSelected(item)) {
           return true;
       }
       // Handle your other action bar items...

       return super.onOptionsItemSelected(item);
   }

    private void initLayout() {
        toolbar = (Toolbar) findViewById(R.id.my_toolbar);
        setSupportActionBar(toolbar);
        getSupportActionBar().setTitle("");
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setHomeAsUpIndicator(R.mipmap.ic_launcher_round);

        drawerLayout = (DrawerLayout) findViewById(R.id.dl_main_drawer_root);
        navigationView = (NavigationView) findViewById(R.id.nv_main_navigation_root);
        navigationView.bringToFront();

        drawerToggle = new ActionBarDrawerToggle(
                this,
                drawerLayout,
                toolbar,
                R.string.drawer_open,
                R.string.drawer_close
                //call.settVisibility(View.INVISIBLE); // 화면에 안보임


        );
        drawerLayout.addDrawerListener(drawerToggle);
        navigationView.bringToFront();
        navigationView.setNavigationItemSelectedListener(this);
    }

    @Override
    public void onBackPressed() {
        if(drawerLayout.isDrawerOpen(GravityCompat.START)) {
            drawerLayout.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }
}


















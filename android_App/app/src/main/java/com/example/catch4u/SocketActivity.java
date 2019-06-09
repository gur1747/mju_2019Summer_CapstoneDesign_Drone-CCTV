package com.example.catch4u;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.PowerManager;
import android.support.v4.app.NotificationCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

import static android.app.Notification.DEFAULT_SOUND;
import static android.app.Notification.DEFAULT_VIBRATE;

public class SocketActivity extends AppCompatActivity implements View.OnClickListener {

    Button connect_btn;                 // ip 받아오는 버튼

    EditText ip_edit;               // ip 에디트
    TextView show_text;             // 서버에서온거 보여주는 에디트
    // 소켓통신에 필요한것
    private String html = "";
    private Handler mHandler;

    private Socket socket;

    private BufferedReader networkReader;
    private PrintWriter networkWriter;

 //   private DataOutputStream dos;
    private DataInputStream dis;

    private String ip = "192.168.0.20";            // IP 번호
    private int port =8886 ;                          // port 번호
    PowerManager powerManager;

    PowerManager.WakeLock wakeLock;
    private String channelId;
    private String channelName;
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.socket);

        connect_btn = (Button)findViewById(R.id.connect_btn);
        connect_btn.setOnClickListener(this);

        ip_edit = (EditText)findViewById(R.id.ipedit);
        show_text = (TextView)findViewById(R.id.show_text);
        powerManager = (PowerManager)getSystemService(Context.POWER_SERVICE);

        wakeLock = powerManager.newWakeLock(PowerManager.SCREEN_BRIGHT_WAKE_LOCK | PowerManager.ACQUIRE_CAUSES_WAKEUP | PowerManager.ON_AFTER_RELEASE, "Catch4U:WAKELOCK");
        getWindow().addFlags((WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED | WindowManager.LayoutParams.FLAG_DISMISS_KEYGUARD | WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON | WindowManager.LayoutParams.FLAG_TURN_SCREEN_ON));

    }

    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.connect_btn:     // ip 받아오는 버튼
                connect();

        }
    }

    // 로그인 정보 db에 넣어주고 연결시켜야 함.
    void connect(){
        final NotificationManager notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        Intent intent = new Intent(this, MainActivity.class);
        final PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
        final Notification.Builder builder = new Notification.Builder(this);
        // getWindow().addFlags((WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED | WindowManager.LayoutParams.FLAG_DISMISS_KEYGUARD | WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON | WindowManager.LayoutParams.FLAG_TURN_SCREEN_ON));

        mHandler = new Handler();
        wakeLock.acquire(10000);
        //  wakeLock.release();
        Log.w("connect","연결 하는중");

        Thread checkUpdate = new Thread() {
            public void run() {

                // ip받기
                String newip = String.valueOf(ip_edit.getText());

                // 서버 접속
                try {
                    socket = new Socket(newip, port);
                    Log.w("서버 접속됨", "서버 접속됨");
                    //  dos.flush();

                } catch (IOException e1) {
                    Log.w("서버접속못함", "서버접속못함");
                    e1.printStackTrace();
                }


                Log.w("edit 넘어가야 할 값 : ","안드로이드에서 서버로 연결요청");

                // Buffered가 잘못된듯.
                try {
                    //  dos = new DataOutputStream(socket.getOutputStream());   // output에 보낼꺼 넣음
                    dis = new DataInputStream(socket.getInputStream());     // input에 받을꺼 넣어짐
                    //                  dos.writeUTF("안드로이드에서 서버로 연결요청");

                } catch (IOException e) {
                    e.printStackTrace();
                    Log.w("버퍼", "버퍼생성 잘못됨");
                }
                Log.w("버퍼","버퍼생성 잘됨");

                while(true) {
                    // 서버에서 받아옴
                    try {
                        String line = "";
                        int line2;
                        while (true) {
                            //  line = (String) dis.readUTF();
                            line2 = (int) dis.read();
                            Log.w("서버에서 받아온 값 ", "" + line);
                            Log.w("서버에서 받아온 값 ", "" + line2);
                            wakeLock.acquire(); // WakeLock 깨우기
                            wakeLock.release(); // WakeLock 해제

                            if(line2 ==49 ) {
                                Log.w("------서버에서 받아온 값 ", "" + line2);
                                //  dos.writeUTF("하나 받았습니다. : " + line2);
                                sendNotification("현관에서 위험감지가 발생했습니다", "지금 당장 영상을 확인해보세요", createID());

                                wakeLock.acquire(); // WakeLock 깨우기
                                wakeLock.release(); // WakeLock 해제
                            }
                            if(line2 == 50) {
                                Log.w("------서버에서 받아온 값 ", "" + line2);
                                sendNotification("테라스에서 위험감지가 발생했습니다", "지금 당장 영상을 확인해보세요", createID());
                                wakeLock.acquire(); // WakeLock 깨우기
                                wakeLock.release(); // WakeLock 해제

                            } if(line2 == 51) {
                                Log.w("------서버에서 받아온 값 ", "" + line2);
                                sendNotification("침대 옆 창문 에서 위험감지가 발생했습니다", "지금 당장 영상을 확인해보세요", createID());
                                wakeLock.acquire(); // WakeLock 깨우기
                                wakeLock.release(); // WakeLock 해제

                            }if(line2 == 52) {
                                Log.w("------서버에서 받아온 값 ", "" + line2);
                                sendNotification("주방에서 위험감지가 발생했습니다", "지금 당장 영상을 확인해보세요", createID());
                                wakeLock.acquire(); // WakeLock 깨우기
                                wakeLock.release(); // WakeLock 해제
                            }
                        }
                    } catch (Exception e) {

                    }
                }

            }
        };
        // 소켓 접속 시도, 버퍼생성
        checkUpdate.start();
    }
    private void sendNotification(String title, String body, int notifyId){
        NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
            int importance = NotificationManager.IMPORTANCE_HIGH;
            NotificationChannel mChannel = new NotificationChannel(channelId, channelName, importance);
            manager.createNotificationChannel(mChannel);
        }
        Intent intent;
        intent = new Intent(this, MainActivity.class);
        Bundle bundle = new Bundle();
        bundle.putString("title", title);
        bundle.putString("body", body);
        intent.putExtras(bundle);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);

        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, intent, PendingIntent.FLAG_ONE_SHOT);
        Uri defaultSoundUri = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);

        NotificationCompat.Builder notificationBuilder = new NotificationCompat.Builder(this, channelId)
                .setFullScreenIntent(pendingIntent, true) // *** head up 노티
                .setPriority(Notification.PRIORITY_MAX) // *** head up 노티
                .setDefaults(DEFAULT_SOUND | DEFAULT_VIBRATE | DEFAULT_SOUND | DEFAULT_VIBRATE) // *** head up 노티
                .setSmallIcon(R.drawable.danger)
                .setContentTitle(title)
                .setContentText(body)
                .setAutoCancel(true)
                .setSound(defaultSoundUri)
                .setVibrate(new long[]{1000, 1000})
                .setLights(Color.BLUE, 1, 1)
                .setContentIntent(pendingIntent);
        manager.notify(notifyId, notificationBuilder.build());
    }

    public int createID(){
        Date now = new Date();
        int id = Integer.parseInt(new SimpleDateFormat("ddHHmmss", Locale.US).format(now));
        return id;
    }


}
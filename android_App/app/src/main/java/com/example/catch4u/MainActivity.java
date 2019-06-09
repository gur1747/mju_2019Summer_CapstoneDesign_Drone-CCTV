package com.example.catch4u;

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
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;

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


        SharedPreferences preferences = getSharedPreferences("msg", 0); //저장된거 불러오기
        final String sms = preferences.getString("sent", null); //저장된 문자
        Button call = (Button) findViewById(R.id.button2); //버튼
        call.setOnClickListener(new View.OnClickListener() { //버튼 누르면
            @Override
            public void onClick(View view) {
                Uri uri = Uri.parse("smsto:112");
                Intent sendintent = new Intent(Intent.ACTION_SENDTO, uri);
                sendintent.putExtra("sms_body", sms);
                startActivity(sendintent); //

            }
        });

        WebView webView = (WebView)findViewById(R.id.webview);
        webView.setWebViewClient(new WebViewClient());
        webView.setBackgroundColor(255);

        WebSettings webSettings = webView.getSettings();
        webSettings.setJavaScriptEnabled(true);

        // 자신이 실행시킨 스트리밍의 주소를 넣어주세요.
        webView.loadUrl(ip);

    }


             //   @Override
                public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                    switch(item.getItemId()) {
                        case R.id.gallery:
                            String url ="https://mail.google.com/mail/u/0/#";
                            Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
                            startActivity(intent);
                            break;

                        case R.id.setting:
                            Intent settingIntent = new Intent(this, SettingActivity.class);
                            startActivity(settingIntent);
                            //Toast.makeText(this, "item2 clicked..", Toast.LENGTH_SHORT).show();
                            break;
                        case R.id.socket:
                            Intent soIntent = new Intent(this, SocketActivity.class);
                            startActivity(soIntent);
                            //  Toast.makeText(this, "item1 clicked..", Toast.LENGTH_SHORT).show();
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


















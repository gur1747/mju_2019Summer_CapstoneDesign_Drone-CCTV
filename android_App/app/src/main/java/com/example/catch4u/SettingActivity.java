package com.example.catch4u;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import static android.content.SharedPreferences.*;

public class SettingActivity extends AppCompatActivity {
    EditText editText;
    Button bt_save;
    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        editText = findViewById(R.id.ipedit);
        bt_save = findViewById(R.id.bt_save);

        //저장되어 있는 값을 가져와서 editText에 표시한다.
      getPreferences();

        //저장 버튼을 클릭시 현재 입력되어 있는 값을 저장한다.
       bt_save.setOnClickListener(new View.OnClickListener() {
          @Override
            public void onClick(View view) {
                savePreferences(editText.getText().toString());
            }
        });
    }
    //load
   private void getPreferences(){
        SharedPreferences pref = getSharedPreferences("pref", MODE_PRIVATE);
        String sUrl = pref.getString("stream", "");
        editText.setText(sUrl);
    }
    //save
      private void savePreferences(String s){
        SharedPreferences pref = getSharedPreferences("pref", MODE_PRIVATE);
        Editor editor = pref.edit();
        editor.putString("stream", s);
        editor.commit();
        finish();
    }
}






package com.example.catch4u;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import static com.example.catch4u.R.layout.activity_message;

public class SendMessageActivity extends AppCompatActivity {
    EditText editText2;
    Button bt_save2;
    @Override
    public void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(activity_message);
        editText2 = findViewById(R.id.sending);
        bt_save2 = findViewById(R.id.bt_save2);

        //저장되어 있는 값을 가져와서 editText에 표시한다.
        getPreferences();

        //저장 버튼을 클릭시 현재 입력되어 있는 값을 저장한다.
        bt_save2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                savePreferences(editText2.getText().toString());
            }
        });
        //final String TEXT = editText2.getText().toString();
        //Intent intent = new Intent(this,MainActivity.class);
        //intent.putExtra("TEXT", TEXT);
        //startActivity(intent);
    }
    //load
    public void getPreferences(){
        SharedPreferences test = getSharedPreferences("msg", MODE_PRIVATE);
        String message = test.getString("sent", "");
        editText2.setText(message);
    }

    //save
    public  void savePreferences(String s){
        SharedPreferences test = getSharedPreferences("msg", MODE_PRIVATE);
        SharedPreferences.Editor editor = test.edit();
        editor.putString("sent", s);
        editor.commit();
        finish();
    }





}

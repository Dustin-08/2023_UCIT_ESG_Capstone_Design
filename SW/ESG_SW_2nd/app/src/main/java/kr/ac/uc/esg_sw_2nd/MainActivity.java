package kr.ac.uc.esg_sw_2nd;

import androidx.appcompat.app.AppCompatActivity;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.BatteryManager;
import android.os.Bundle;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private TextView battery;
    ImageView face;

    TextView value,result;
    Button airState,btnBlue;

    private BroadcastReceiver batterylevelReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            int level = intent.getIntExtra(BatteryManager.EXTRA_LEVEL,0);
            battery.setText(String.valueOf(level)+"%");
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button turnOn,turnOff;
        Switch swUv;

        turnOn = findViewById(R.id.turnOn);
        turnOff = findViewById(R.id.turnOff);
        swUv = findViewById(R.id.swUv);
        face = findViewById(R.id.face);
        value = findViewById(R.id.value);
        result = findViewById(R.id.result);
        airState = findViewById(R.id.airState);
        btnBlue =findViewById(R.id.btnBlue);


        //value 값을 받으면 value 값에 따라 face와 result값이 변하도록
//            int numValue = Integer.parseInt(String.valueOf(value));
        int numVal = 30;
        airClear(numVal);


        battery = (TextView)findViewById(R.id.batteryLevel);
        this.registerReceiver(this.batterylevelReceiver,new IntentFilter(Intent.ACTION_BATTERY_CHANGED));

        turnOn.setOnClickListener(v -> {
            //아두이노에 문자열 1을 보내서 받으면 공기청정기 켜기
            airState.setText("Air Purifier Running");
            //버튼 색깔 바꾸고 싶은데 backgroindTint 색 바꾸는 명령어 모르겠어요

        });

        turnOff.setOnClickListener(v -> {
            //아두이노에서 문자열 0을 보내서 받으면 공기청정기 끄기
            airState.setText("Air Purifier Turned Off");
            //버튼 색깔 바꾸고 싶은데 backgroindTint 색 바꾸는 명령어 모르겠어요
        });


        swUv.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked){
                    //led 켜기
                }else {
                    //led 끄기
                }
            }
        });

        btnBlue.setOnClickListener(view -> {
            Intent intent = new Intent(MainActivity.this,BlueToothActivity.class);
            startActivity(intent);
        });

    }

    private void airClear(int numValue) {
        if(numValue<=30 && numValue>=0){
            result.setText(getString(R.string.angel));
            face.setImageResource(R.drawable.angel);
        }else if(numValue<=80 && numValue>=31){
            result.setText(getString(R.string.smile));
            face.setImageResource(R.drawable.smile);
        }else if(numValue<=150 && numValue>=81){
            result.setText(getString(R.string.sad));
            face.setImageResource(R.drawable.sad);
        }else if(numValue>=151){
            result.setText(getString(R.string.angry));
            face.setImageResource(R.drawable.angry);
        }
    }




}
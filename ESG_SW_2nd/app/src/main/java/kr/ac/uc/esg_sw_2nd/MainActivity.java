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
import android.widget.Switch;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private TextView battery;

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

        battery = (TextView)findViewById(R.id.batteryLevel);
        this.registerReceiver(this.batterylevelReceiver,new IntentFilter(Intent.ACTION_BATTERY_CHANGED));

        turnOn.setOnClickListener(v -> {
            //아두이노에 문자열 1을 보내서 받으면 공기청정기 켜기
        });

        turnOff.setOnClickListener(v -> {
            //아두이노에서 문자열 0을 보내서 받으면 공기청정기 끄기
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


    }
}
package com.example.bluetooth;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import java.util.Set;

public class MainActivity extends AppCompatActivity {
    private BluetoothAdapter bluetoothAdapter;
    private ListView deviceListView;
    private ArrayAdapter<String> deviceListAdapter;
    private Button btn_bluetooth_onoff;
    private BluetoothManager bluetoothManager;
    private static final int REQUEST_ENABLE_BT = 1; // 블루투스 활성화 요청 코드
    private static final int REQUEST_PERMISSION = 2; // 위치 권한 요청 코드
    private static final int REQUEST_PERMISSION_BLUETOOTH_CONNECT = 3; // 블루투스 연결 권한 요청 코드

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        deviceListView = findViewById(R.id.deviceListView);
        deviceListAdapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1);
        deviceListView.setAdapter(deviceListAdapter);
        bluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
        bluetoothAdapter = bluetoothManager.getAdapter();
        btn_bluetooth_onoff = findViewById(R.id.btn_bluetooth_onoff);
        btn_bluetooth_onoff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toggleBluetooth();
            }

            private void toggleBluetooth() {
                if (bluetoothAdapter.isEnabled()) {
                    if (ActivityCompat.checkSelfPermission(MainActivity.this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                        ActivityCompat.requestPermissions(MainActivity.this, new String[]{Manifest.permission.BLUETOOTH_CONNECT}, REQUEST_PERMISSION_BLUETOOTH_CONNECT);
                        return;
                    } else {
                        bluetoothAdapter.disable();
                    }
                } else {
                    if (ActivityCompat.checkSelfPermission(MainActivity.this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                        ActivityCompat.requestPermissions(MainActivity.this, new String[]{Manifest.permission.BLUETOOTH_CONNECT}, REQUEST_PERMISSION_BLUETOOTH_CONNECT);
                        return;
                    } else {
                        bluetoothAdapter.enable();
                    }
                }
                updateToggleButtonText();
            }

            private void updateToggleButtonText() {
                Button toggleBluetoothButton = findViewById(R.id.btn_bluetooth_onoff);
                if (bluetoothAdapter.isEnabled()) {
                    toggleBluetoothButton.setText("Bluetooth Off");
                } else {
                    toggleBluetoothButton.setText("Bluetooth On");
                }
            }
        });

        // 블루투스 활성화 확인
        if (!bluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
            Toast.makeText(this, "블루투스 활성화 확인", Toast.LENGTH_SHORT).show();
        }

        // 블루투스 어댑터 초기화
        if (bluetoothAdapter == null) {
            Toast.makeText(this, "블루투스를 지원하지 않습니다.", Toast.LENGTH_SHORT).show();
            finish();
        }

        // 블루투스 장치 검색 버튼
        Button searchButton = findViewById(R.id.searchButton);
        searchButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                checkPermissionsAndStartDiscovery();
            }
        });
    }

    private void checkPermissionsAndStartDiscovery() {
        // 위치 권한 확인
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION)
                != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.ACCESS_FINE_LOCATION},
                    REQUEST_PERMISSION);
        } else {
            startDiscovery();
        }
    }

    private void startDiscovery() {
        deviceListAdapter.clear();
        // 페어링된 장치 목록 가져오기
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_SCAN) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.BLUETOOTH_SCAN}, REQUEST_PERMISSION_BLUETOOTH_CONNECT);
            return;
        }

        Set<BluetoothDevice> pairedDevices = bluetoothAdapter.getBondedDevices();
        for (BluetoothDevice device : pairedDevices) {
            deviceListAdapter.add(device.getName() + "\n" + device.getAddress());
        }
        // 장치 검색 시작
        bluetoothAdapter.startDiscovery();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (bluetoothAdapter != null) {
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_SCAN) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.BLUETOOTH_SCAN}, REQUEST_PERMISSION_BLUETOOTH_CONNECT);
            } else {
                bluetoothAdapter.cancelDiscovery();
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                           @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == REQUEST_PERMISSION) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                startDiscovery();
            } else {
                Toast.makeText(this, "위치 권한이 필요합니다.", Toast.LENGTH_SHORT).show();
            }
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == REQUEST_ENABLE_BT) {
            if (resultCode == RESULT_OK) {
                checkPermissionsAndStartDiscovery();
            } else if (resultCode == RESULT_CANCELED) {
                Toast.makeText(this, "블루투스를 활성화해야 합니다.", Toast.LENGTH_SHORT).show();
            }
        }
    }
}

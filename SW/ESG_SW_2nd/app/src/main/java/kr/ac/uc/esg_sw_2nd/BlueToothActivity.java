package kr.ac.uc.esg_sw_2nd;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import java.io.IOException;
import java.util.Set;
import java.util.UUID;


public class BlueToothActivity extends AppCompatActivity {

    private BluetoothAdapter bluetoothAdapter;
    private ListView deviceListView;
    private ArrayAdapter<String> deviceListAdapter;
    private BluetoothDevice selectedDevice;
    private Button btn_bluetooth_onoff, connectButton, disconnectButton;
    private BluetoothManager bluetoothManager;
    private BluetoothSocket bluetoothSocket;
    private static final int REQUEST_ENABLE_BT = 1; // 블루투스 활성화 요청 코드
    private static final int REQUEST_PERMISSION = 2; // 위치 권한 요청 코드
    private static final int REQUEST_PERMISSION_BLUETOOTH_CONNECT = 3; // 블루투스 연결 권한 요청 코드
    private static final int REQUEST_PERMISSION_BLUETOOTH_ADMIN = 4;
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); // SPP UUID

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_blue_tooth);
        deviceListView = findViewById(R.id.deviceListView);
        deviceListAdapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1);
        deviceListView.setAdapter(deviceListAdapter);
        bluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
        bluetoothAdapter = bluetoothManager.getAdapter();
        btn_bluetooth_onoff = findViewById(R.id.btn_bluetooth_onoff);
        connectButton = findViewById(R.id.connectButton);
        disconnectButton = findViewById(R.id.disconnectButton);
        btn_bluetooth_onoff.setVisibility(View.INVISIBLE); // On/Off 버튼을 invisible로 설정

        deviceListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                String deviceInfo = (String) parent.getItemAtPosition(position);
                String deviceName = deviceInfo.split("\n")[0]; // 디바이스 이름 추출
                String deviceAddress = deviceInfo.split("\n")[1]; // 디바이스 주소 추출

                // 선택한 디바이스를 찾아서 페어링 및 연결 시도
                if (ActivityCompat.checkSelfPermission(BlueToothActivity.this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                    // BLUETOOTH_CONNECT 권한이 없는 경우 권한 요청
                    ActivityCompat.requestPermissions(BlueToothActivity.this,
                            new String[]{Manifest.permission.BLUETOOTH_CONNECT},
                            REQUEST_PERMISSION_BLUETOOTH_CONNECT);
                    return;
                }
                Set<BluetoothDevice> pairedDevices = bluetoothAdapter.getBondedDevices();
                for (BluetoothDevice device : pairedDevices) {
                    if (device.getAddress().equals(deviceAddress)) {
                        selectedDevice = device;
                        // 이제 페어링 및 연결을 시도할 수 있습니다.
                        // selectedDevice를 사용하여 필요한 작업을 수행하세요.
                        // 예: BluetoothSocket을 열어 데이터를 주고받는 작업 등
                        break;
                    }
                }

                if (selectedDevice != null) {
                    // 디바이스가 선택되었으므로 추가 작업을 수행하세요.
                    // 예: 연결 시도, 데이터 통신 등
                    Toast.makeText(BlueToothActivity.this, "디바이스가 선택되었습니다: " + deviceName, Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(BlueToothActivity.this, "디바이스를 찾을 수 없습니다.", Toast.LENGTH_SHORT).show();
                }
            }
        });

        btn_bluetooth_onoff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toggleBluetooth();
                Toast.makeText(BlueToothActivity.this, "ON/OFF 버튼 클릭", Toast.LENGTH_SHORT).show();
            }

            private void toggleBluetooth() {
                if (bluetoothAdapter == null) {
                    // 블루투스를 지원하지 않는 기기임을 사용자에게 알림
                    Toast.makeText(BlueToothActivity.this, "블루투스를 지원하지 않는 기기입니다.", Toast.LENGTH_SHORT).show();
                    return;
                }

                if (bluetoothAdapter.isEnabled()) {
                    // 블루투스가 이미 활성화되어 있는 경우
                    if (ActivityCompat.checkSelfPermission(BlueToothActivity.this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                        // 블루투스 상태 변경 권한이 없는 경우 권한 요청
                        ActivityCompat.requestPermissions(BlueToothActivity.this, new String[]{Manifest.permission.BLUETOOTH_ADMIN}, REQUEST_PERMISSION_BLUETOOTH_ADMIN);
                    } else {
                        // 권한이 이미 부여되어 있는 경우
                        bluetoothAdapter.disable();
                        Toast.makeText(BlueToothActivity.this, "블루투스가 비활성화되었습니다", Toast.LENGTH_SHORT).show();
                        btn_bluetooth_onoff.setVisibility(View.INVISIBLE); // On/Off 버튼을 invisible로 설정
                    }
                } else {
                    // 블루투스가 비활성화된 경우
                    Toast.makeText(BlueToothActivity.this, "블루투스가 활성화되어있지 않습니다", Toast.LENGTH_SHORT).show();
                    // 블루투스 상태 변경 권한 요청
                    ActivityCompat.requestPermissions(BlueToothActivity.this, new String[]{Manifest.permission.BLUETOOTH_ADMIN}, REQUEST_PERMISSION_BLUETOOTH_ADMIN);
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

        // 블루투스 연결 버튼
        connectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                onConnectToDeviceClicked();
            }
            //다시 메인으로 돌아가기
        });

        // 블루투스 연결 해제 버튼
        disconnectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                onDisconnectDeviceClicked();
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

    private void connectToDevice(BluetoothDevice device) {
        try {
            // BluetoothSocket 생성
            bluetoothSocket = device.createRfcommSocketToServiceRecord(MY_UUID);

            // 연결 시도 시작
            bluetoothSocket.connect();

            // 연결이 성공적으로 완료되었을 때 여기에 추가 작업을 수행하세요.
            // 예: 데이터 통신을 위한 스트림 열기, 데이터 수신 및 송신 등

            Toast.makeText(this, "디바이스에 연결되었습니다.", Toast.LENGTH_SHORT).show();
        } catch (IOException e) {
            // 연결 오류 처리
            e.printStackTrace();
            try {
                bluetoothSocket.close();
            } catch (IOException e2) {
                e2.printStackTrace();
            }
            Toast.makeText(this, "디바이스 연결에 실패했습니다.", Toast.LENGTH_SHORT).show();
        }
    }

    private void disconnectDevice() {
        if (bluetoothSocket != null) {
            try {
                bluetoothSocket.close();
                // 연결이 닫혔을 때 수행해야 할 작업을 여기에 추가하세요.
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void onConnectToDeviceClicked() {
        if (selectedDevice != null) {
            connectToDevice(selectedDevice);
        } else {
            Toast.makeText(this, "디바이스를 먼저 선택하세요.", Toast.LENGTH_SHORT).show();
        }
    }

    private void onDisconnectDeviceClicked() {
        disconnectDevice();
        // 연결 해제 후 수행해야 할 작업을 여기에 추가하세요.
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
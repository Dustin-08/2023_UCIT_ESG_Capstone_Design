#include <SoftwareSerial.h>

#define BTtx       8 // 블루투스 모듈의 tx를 D7으로 설정
#define BTrx       9 // 블루투스 모듈의 rx를 D8로 설정

SoftwareSerial BT(BTtx, BTrx); // tx, rx

char data = 0; /* 앱을 통해 0 또는 1이라는 문자열을 받을건데 0이 꺼지는 default 값이므로 0으로 설정 */

// 미세먼지 값 범위 제한
float min = 0; // 최소
float max = 100.0; // 최대

//RGBLED
int rgb_red = 7; // RGB 핀 설정
int rgb_green = 6; // RGB 핀 설정
int rgb_blue = 5; // RGB 핀 설정


//소독용 UV LED
int led = 10;

//미세먼지 센서
int dust_sensor = A0; // 미세먼지 센서 핀 설정
float dust_value = 0; // 실수형 미세먼지 값
float dustDensityug = 0; // 계산된 미세먼지 값
int sensor_led = 2; // 미세먼지 모듈의 led 핀 설정
int sampling = 280;
int waiting = 40;
float stop_time = 9680;

//DC모터
int IN1 = 13; // IN1을 11 핀으로 설정, 정방향 회전을 결정하는 핀
int IN2 = 12; // IN2을 123 핀으로 설정, 역방향 회전을 결정하는 핀
int ENA = 11; // 무조건 PWM 핀으로 설정하기, 속력 결정하는 핀

void setup(){

  BT.begin(9600); // BT를 보드레이트 9600으로 설정
  
  
  Serial.begin(9600); // 시리얼 모니터 보드레이트 설정
  pinMode(sensor_led,OUTPUT); // 미세먼지 모듈의 led 핀 출력
  pinMode(4, OUTPUT); // 

  pinMode(rgb_red, OUTPUT); // RGB 핀 출력
  pinMode(rgb_green, OUTPUT); // RGB 핀 출력
  pinMode(rgb_blue, OUTPUT); // RGB 핀 출력

  pinMode(IN1, OUTPUT); // 모터 드라이버 모듈 출력 설정
  pinMode(IN2, OUTPUT); // 모터 드라이버 모듈 출력 설정
  pinMode(ENA, OUTPUT); // 모터 드라이버 모듈 출력 설정
}

void loop(){
        // 5. 블루투스 모듈 수신 확인용----------------------------------------------------------
  if(BT.available() > 0) { // 블루투스가 연결되면
    data = BT.read(); // 데이터를 수신 받아서 읽음
  }
  // 6. 실제 문자열에 따라 작동하는 구문-------------------------------------------------
  if(data == '0') { // data라는 문자열이 0이라면
    Serial.println("Turn OFF"); // 시리얼 모니터에 Turn OFF라는 문구 출력
    analogWrite(rgb_red, 0); // RGB Led Off
    analogWrite(rgb_green, 0); // RGB Led Off
    analogWrite(rgb_blue, 0); // RGB Led Off
    digitalWrite(IN1, HIGH); // 회전 멈춤
    digitalWrite(IN2, LOW); // 회전 멈춤
    digitalWrite(ENA, 0); // 팬 속도 없음
  }
  else if(data == '1') { // data라는 문자열이 1이라면
    Serial.println("Turn ON"); // 시리얼 모니터에 Turn ON라는 문구 출력
    if(dustDensityug <= 35.0){ // 미세먼지 농도가 35 이하일 때
      analogWrite(rgb_red, 0); // B를 키기 위해 R을 0으로
      analogWrite(rgb_green, 0); // B를 키기 위해 G를 0으로
      analogWrite(rgb_blue, 255); // RGB 파란불이 들어옴
      Serial.print("    "); 
      Serial.println("blue"); // 파란불이 켜졌음을 시리얼 모니터로 보여주기
      digitalWrite(IN1, HIGH); 
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 50); // 팬 속도를 약하게 돌림
    }
    else if(35.0 < dustDensityug && dustDensityug <= 75.0){ // 미세먼지 농도가 36 이상 75 이하일 때
      analogWrite(rgb_red, 0);
      analogWrite(rgb_green, 255); // RGB 초록불이 들어옴
      analogWrite(rgb_blue, 0);
      Serial.print("    ");
      Serial.println("green");
      digitalWrite(IN1, HIGH); 
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 180); // 팬 속도를 중간 정도로 돌림
    }
    else if(dustDensityug > 75.0){ // 미세먼지 농도가 76 이상일 때
      analogWrite(rgb_red, 255);
      analogWrite(rgb_green, 0); // RGB 빨간불과 초록불이 같이 들어옴
      analogWrite(rgb_blue, 0);
      Serial.print("    ");
      Serial.println("red");
      digitalWrite(IN1, HIGH); 
      digitalWrite(IN2, LOW); 
      analogWrite(ENA, 255); // 팬 속도를 강하게 돌림
    }
  }
  else if(data == '2'){
    Serial.println("필터를 소독합니다.");
    digitalWrite(led,HIGH);
    delay(3000);
    digitalWrite(led,LOW);
  }

  // 7. 문자열 초기화----------------------------------------------------------------------------
  //data = 0; // data라는 문자열을 초기화

  digitalWrite(sensor_led, LOW);
  delayMicroseconds(sampling);

  dust_value = analogRead(dust_sensor); // 미세먼지 센서에서 값을 받아옴

  delayMicroseconds(waiting);

  digitalWrite(sensor_led, HIGH);
  delayMicroseconds(stop_time);

  dustDensityug = (0.17*(dust_value * (5.0 / 1024))-0.1)*1000; // 미세먼지 센서에서 받아온 값을 ug/m^3로 변환
  if(dustDensityug < min){
    Serial.print("Dust Density [ug/m3]:");
    Serial.println("0");
    BT.print("0");
  }
  else if(dustDensityug > min && dustDensityug <= 35.0){
    Serial.print("Dust Density [ug/m3]:");
    Serial.println(dustDensityug);
    BT.print(dustDensityug);
  }
  else if(dustDensityug > 35.0 && dustDensityug < 75){
     Serial.print("Dust Density [ug/m3]:");
    Serial.println(dustDensityug);
    BT.print(dustDensityug);
  }
  else if(dustDensityug >= max){
    Serial.print("Dust Density [ug/m3]:");
    Serial.println("100");
    BT.print("100");
  }

  delay(3000);
// ------------------------------ 여기까지 필터 관련 ---------------------------------------------------
  
}
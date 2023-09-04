#include<SoftwareSerial.h>

#define BTtx       9 // 블루투스 모듈의 tx를 D7으로 설정
#define BTrx       10 // 블루투스 모듈의 rx를 D8로 설정

SoftwareSerial BT(BTtx, BTrx); // tx, rx

char data = 0; /* 앱을 통해 0 또는 1이라는 문자열을 받을건데 0이 꺼지는 default 값이므로 0으로 설정 */

//RGBLED
int rgb_red = 13;
int rgb_green = 12;
int rgb_blue = 11;

//초음파 센서
int trig = 7;
int echo = 6;

//소독용 UV LED
int led = 2;

//미세먼지 센서
int dust_sensor = A0;
float dust_value = 0;
float dustDensityug = 0;
int sensor_led = 8;
int sampling = 280;
int waiting = 40;
float stop_time = 9680;

//DC모터
int IN1 = 3; // IN1을 11 핀으로 설정, 정방향 회전을 결정하는 핀
int IN2 = 4; // IN2을 123 핀으로 설정, 역방향 회전을 결정하는 핀
int ENA = 5; // 무조건 PWM 핀으로 설정하기, 속력 결정하는 핀

void setup(){

  BT.begin(9600); // BT를 보드레이트 9600으로 설정
  
  
  Serial.begin(9600);
  pinMode(sensor_led,OUTPUT);
  pinMode(4, OUTPUT);

  pinMode(rgb_red, OUTPUT);
  pinMode(rgb_green, OUTPUT);
  pinMode(rgb_blue, OUTPUT);

  pinMode (echo, INPUT); //  echoPin 입력 
  pinMode (trig, OUTPUT); // trigPin 출력 
  pinMode(5, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void loop(){
  digitalWrite(sensor_led, LOW);
  delayMicroseconds(sampling);

  dust_value = analogRead(dust_sensor);

  delayMicroseconds(waiting);

  digitalWrite(sensor_led, HIGH);
  delayMicroseconds(stop_time);

  dustDensityug = (0.17*(dust_value * (5.0 / 1024))-0.1)*1000;
  Serial.print("Dust Density [ug/m3]:");
  Serial.print(dustDensityug);

  if(dustDensityug <= 30.0){
    analogWrite(rgb_red, 0);
    analogWrite(rgb_green, 0);
    analogWrite(rgb_blue, 255);
    Serial.print("    ");
    Serial.println("blue");
  }else if(30.0 < dustDensityug && dustDensityug <= 80.0){
    analogWrite(rgb_red, 0);
    analogWrite(rgb_green, 255);
    analogWrite(rgb_blue, 0);
    Serial.print("    ");
    Serial.println("green");
  }else if(80.0 < dustDensityug && dustDensityug <= 150.0){
    analogWrite(rgb_red, 255);
    analogWrite(rgb_green, 155);
    analogWrite(rgb_blue, 0);
    Serial.print("    ");
    Serial.println("yellow");
  }else{
     analogWrite(rgb_red, 255);
    analogWrite(rgb_green, 0);
    analogWrite(rgb_blue, 0);
    Serial.print("    ");
    Serial.println("red");
  }

  delay(20);

  long duration, distance; 
  digitalWrite (trig, HIGH); // trigPin에서 초음파 발생 (echoPin도 HIGH) 
  delayMicroseconds (10); 
  digitalWrite (trig, LOW); 
  duration = pulseIn (echo, HIGH); // echoPin 이 HIGH를 유지한 시간을 저장 한다. 
  distance = (duration/2)*0.034; 

   // Serial.print("Duration:"); //시리얼모니터에 Echo가 HIGH인 시간을 표시 
   // Serial.print(duration); 
  Serial.print ("\nDIstance:"); // 물체와 초음파 센서간 거리를 표시
  Serial.print (distance); 
  Serial.println ("mm\n"); 
  if (distance < 100){          
    digitalWrite(led, HIGH);
     }
  else{          
    digitalWrite(led, LOW); 
    }

      // 5. 블루투스 모듈 수신 확인용----------------------------------------------------------
  if(BT.available() > 0) { // 블루투스가 연결되면
    data = BT.read(); // 데이터를 수신 받아서 읽음
  }
  // 6. 실제 문자열에 따라 작동하는 구문-------------------------------------------------
  if(data == '0') { // data라는 문자열이 0이라면
    digitalWrite(led, LOW); // led가 꺼짐
    Serial.println("Turn OFF"); // 시리얼 모니터에 Turn OFF라는 문구 출력
    digitalWrite(IN1, HIGH); // IN1이 HIGH이면 정방향 회전
    digitalWrite(IN2, LOW); // 대신 IN2가 LOW 상태여야함
    digitalWrite(ENA, LOW); // 최저 속력 회전

  }
  else if(data == '1') { // data라는 문자열이 1이라면
    digitalWrite(led, HIGH); // led가 켜짐
    Serial.println("Turn on"); // 시리얼 모니터에 Turn OFF라는 문구 출력
    digitalWrite(IN1, HIGH); // IN1이 HIGH이면 정방향 회전
    digitalWrite(IN2, LOW); // 대신 IN2가 LOW 상태여야함
    digitalWrite(ENA, HIGH); // 최고 속력 회전
  }
  // 7. 문자열 초기화----------------------------------------------------------------------------
  data = 0; // data라는 문자열을 초기화

  delay(1000);
  
}
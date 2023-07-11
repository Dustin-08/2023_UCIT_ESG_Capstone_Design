#include<DHT11.h>
DHT11 dht11(2);
int A = 8; // D8번 핀을 INA 핀으로 설정
int B = 9; // D9번 핀을 INB 핀으로 설정

void setup() {
  pinMode(A,OUTPUT); // A 핀을 출력으로 변경
  pinMode(B,OUTPUT);  // B 핀을 출력으로 변경 
  Serial.begin(115200); // 통신 초기화
}

void loop() {
  float temperature = dht11.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C - Fan On");
  if (temperature >=26){
    digitalWrite(A,LOW);
    digitalWrite(B,HIGH);
  }
  else {
    digitalWrite(A,HIGH); // 전체 정지
    digitalWrite(B,HIGH);
  }
  delay(2000);
}

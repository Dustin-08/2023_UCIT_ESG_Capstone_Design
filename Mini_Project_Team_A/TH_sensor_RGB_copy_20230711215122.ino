#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>

#define LED_PIN 13  // LED가 연결된 핀 번호

Adafruit_BMP085 bmp;  // BMP180 센서 객체

void setup() {
  pinMode(LED_PIN, OUTPUT);  // LED 핀을 출력으로 설정
  Serial.begin(9600);  // 시리얼 통신 시작

  if (!bmp.begin()) {
    Serial.println("BMP180 센서를 찾을 수 없습니다. 연결을 확인하세요.");
    while (1)
  }
}

void loop() {
  // 온도 값을 읽어옴
  float temperature = bmp.readTemperature();

  // 온도가 26도 이상인 경우 LED를 켜고, 26도 이하인 경우 깜박임
  if (temperature >= 26.0) {
    digitalWrite(LED_PIN, HIGH);  // LED를 켬
  } else {
    digitalWrite(LED_PIN, LOW);  // LED를 끔
    delay(500);  // 0.5초 동안 대기
    digitalWrite(LED_PIN, HIGH);  // LED를 켬
    delay(500);  // 0.5초 동안 대기
  }

  Serial.print("현재 온도: ");
  Serial.print(temperature);
  Serial.println("도");

  delay(1000);  // 1초 동안 대기
}

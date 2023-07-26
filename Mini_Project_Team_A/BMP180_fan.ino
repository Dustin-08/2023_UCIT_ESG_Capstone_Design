#include <Adafruit_BMP085.h> // bmp180 라이브러리 선언

int fan = 8; // fan 디지털 8번 포트 연결 선언
Adafruit_BMP085 bmp; // bmp180 변수 이름 설정
  
void setup() {
  Serial.begin(9600); //시리얼 모니터 설정
  if (!bmp.begin()) { // bmp180 동작 여부 확인
	Serial.println("Could not find a valid BMP085 sensor, check wiring!"); // 동작이 안되면 출력
	while (1) {}
  }
  pinMode(fan, OUTPUT); // 디지털 8번 포트를 fan OUTPUT으로 설정
}
  
void loop() {
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature()); // bmp180이 읽은 온도값 출력
    Serial.println(" *C");
    float temperature = bmp.readTemperature(); // bmp180이 읽은 온도값을 실수형 변수 temperature에 저장
    if(temperature >= 26.0){ // temperature의 값이 26.0이 넘으면
    digitalWrite(fan, HIGH); // 정방향으로 회전
    digitalWrite(fan, LOW);
    }
    Serial.println();
    delay(500);
}

#include <Adafruit_BMP085.h> // bmp180 라이브러리 선언

int LED = 8; // LED 핀 번호 설정
Adafruit_BMP085 bmp; // bmp180 변수 이름 설정
  
void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
  pinMode(LED, OUTPUT);
}
  
void loop() {
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    float temperature = bmp.readTemperature();
    if(temperature >= 26.0){
    digitalWrite(LED, HIGH);
    }
    else{
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
    }
    Serial.println();
    delay(500);
}
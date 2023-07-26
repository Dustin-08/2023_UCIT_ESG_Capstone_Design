#include "DHT.h" //아두이노 온습도센서 DHT11을 사용하기위해 위에서 설치해두었던 라이브러리를 불러옵니다.
#define DHTPIN 2     // D2번 핀을 DHT핀으로 설정

#define DHTTYPE DHT11   // 여러 DHT 종류 중 DHT11을 사용한다고 선언
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // 시리얼 보드레이트를 9600으로 설정
  Serial.println("temp, Humi"); // 시리얼 모니터에 temp, Humi 출력

  dht.begin(); // dht 시작
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000); // 측정을 위해 2초 대기

  
  float temp = dht.readTemperature(); // dht11에서 읽어온 온도값을 실수형 변수인 temp에 저장
  float humi = dht.readHumidity(); // dht11에서 읽어온 습도값을 실수형 변수인 humi에 저장

  
  Serial.print("Temp: ");
  Serial.print(temp); // 시리얼 모니터에 온도 출력
  Serial.println("*C");
  
  Serial.print("Humi: ");
  Serial.println(humi); // 시리얼 모니터에 습도 출력
  Serial.println("h");
 
}

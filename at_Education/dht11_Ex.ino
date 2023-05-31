#include <DHT11.h>  //아두이노 온습도센서 DHT11을 사용하기위해 위에서 설치해두었던 라이브러리를 불러옵니다.

int pin=A0;
DHT11 dht11(pin);  /* 불러온 라이브러리 안에 몇번 PIN에서 데이터값이 나오는지
                          설정해줘야 합니다. 아날로그 0번 PIN인 A0으로 설정했습니다. */

void setup() {
  Serial.begin(9600); // 온습도값을 PC모니터로 확인하기위해 시리얼 통신을 설정해 줍니다.
  Serial.println("DHT11 test Start!");
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // 센서의 온도와 습도를 읽어온다.
  float h = dht11.readHumidity();
  float t = dht11.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    //값 읽기 실패시 시리얼 모니터 출력
    Serial.println("Failed to read from DHT");
  } else {
    //온도, 습도 표시 시리얼 모니터 출력
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }
}

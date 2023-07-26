int fan = 3; // 팬 디지털 3번 포트 연결 선언
int analogPin = 0; // 워터센서 analog prot 0 연결 선언
int val = 0; // 전류 변화값 변수 선언

void setup() {
    pinMode(fan, OUTPUT); // 디지털 3번 포트를 fan OUTPUT 으로 설정
    Serial.begin(9600); // 시리얼 모니터 설정
}

void loop() {
  val = analogRead(analogPin); // analogPin의 전류값(변화값)을 읽음

  if(val >= 100){ //val 값이 100이 넘으면 (전류가 100이 넘으면)
    digitalWrite(fan, HIGH); // fan ON
  }
  else{
    digitalWrite(fan, LOW);
  }

  Serial.println(val); // val의 값 시리얼 모니터에 출력
  delay(500);
}
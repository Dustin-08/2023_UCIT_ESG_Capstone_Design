int measurePin = 0;          // measurePin을 0으로 설정합니다.
int ledPower = 2;             // ledPower를 2로 설정합니다.
  
int samplingTime = 280;    // samplingTime을 280으로 설정합니다.
int deltaTime = 40;           // deltaTime을 40으로 설정합니다.
int sleepTime = 9680;       // sleepTime을 9690으로 설정합니다.
  
float voMeasured = 0;      // voMeasured를 0으로 설정합니다.
float calcVoltage = 0;       // calcVoltage를 0으로 설정합니다.
float dustDensity = 0;       // dustDensity를 0으로 설정합니다.
  
void setup(){
  Serial.begin(9600);                   // 시리얼 통신을 사용하기 위해 보드레이트를 9600으로 설정합니다.
  pinMode(ledPower,OUTPUT);   // ledPower를 출력 단자로 설정합니다.
}
  
void loop(){
  digitalWrite(ledPower,LOW);                               // ledPower를 LOW로 설정합니다.
  delayMicroseconds(samplingTime);                    // samplingTime(280) 마이크로초만큼 지연합니다. 
  
  voMeasured = analogRead(measurePin);             //  measurePin의 아날로그 값을 받아 voMeasured에 저장합니다.
  
  delayMicroseconds(deltaTime);                          // deltaTime(40) 마이크로초만큼 지연합니다. 
  digitalWrite(ledPower,HIGH);                              // ledPower를 HIGH로 설정합니다.
  delayMicroseconds(sleepTime);                        // sleepTime(9680) 마이크로초만큼 지연합니다.
  
  calcVoltage = voMeasured * (5.0 / 1024.0);         // voMeasured의 값을 5.0/1024.0을 곱하여 calcVoltage에 저장합니다.
  
  dustDensity = (0.17 * calcVoltage - 0.1) * 1000;   // calcVoltage 값에 0.17을 곱하고 -0.1을 더합니다. (mg/m3)
                                                   // 값을 ug/m3 단위로 표현하기 위해 1000을 곱하여 dustDensity에 저장하여줍니다.
  
  if (dustDensity > 30){                                      // dustDensity 30미만이면(잡음을 막기 위함)
    Serial.print(dustDensity);                              // dustDensity을 시리얼 통신으로 출력합니다.
    Serial.println(" ug/m3");                               // " ug/m3"를 시리얼 통신으로 출력하고 줄을 바꿉니다.
  }
  delay(1000);                                                 // 1초동안 지연합니다.
}
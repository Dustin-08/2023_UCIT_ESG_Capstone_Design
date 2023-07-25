#include "LedControl.h" // 도트매트릭스 제어용 라이브러리

// 도트매트릭스 사용 준비
LedControl lc = LedControl(8, 10, 9, 1); // (DIN,CLK,CS,number)


byte fgh[] =
{
  B11000011,
  B11000011,
  B11000011,
  B11111111,
  B11111111,
  B11000011,
  B11000011,
  B11000011,


};
// LED 도트매트릭스 제어용 함수
void showLED(byte arr[], int a)
{
  if (a == 1) {
    for (int i = 0; i < 8; i++)
    {
      lc.setRow(0, i, arr[i]);
    }
  } else {
    for (int i = 0; i < 8; i++)
    {
      lc.setRow(0, i, B00000000);
    }
  }
}

int rainPin = A0;

int thresholdValue = 500;

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 5); // LED 도트매트릭스 밝기
  lc.clearDisplay(0); // LED 도트매트릭스 모두 지우기

  Serial.begin(9600); // 주의 주의 //
  pinMode(rainPin, INPUT);

}

void loop() {

  // read the input on analog pin 0:

  int sensorValue = analogRead(rainPin);

  Serial.print(sensorValue);

  if(sensorValue < thresholdValue){

    Serial.println(" - It's wet"); //물 있을 떄//
    delay(500);
    showLED(fgh, 1); 
    delay(1000); 
   

  }

  else {

    Serial.println(" - It's dry"); //물 없을 떄//
    showLED(fgh, 0); // 모두 지우기
    delay(1000);  

  }
delay(1000); 
  
}


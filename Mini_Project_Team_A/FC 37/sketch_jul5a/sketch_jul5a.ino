int rainPin = A0;

int thresholdValue = 500; /* 우적 민감도 클수록 감도 심해짐 */


void setup() {

  Serial.begin(9600); // 주의 주의 //

  pinMode(rainPin, INPUT);

}


void loop() {



  int sensorValue = analogRead(rainPin);

  Serial.print(sensorValue);

  if(sensorValue < thresholdValue){

    Serial.println(" - It's wet"); //물 있을 떄//

  }

  else {

    Serial.println(" - It's dry"); //물 없을 떄//

  }

  delay(500);

}

//https://blog.naver.com/youngseok159/222941422488//
//https://eduino.kr/product/detail.html?product_no=122//
int rainPin = A0;
int thresholdValue = 500;
void setup() {
  Serial.begin(9600); // 주의 주의 //
  pinMode(rainPin, INPUT);
}
void loop() {

  // read the input on analog pin 0:

  int sensorValue = analogRead(rainPin);

  Serial.print(sensorValue);
  if(sensorValue < thresholdValue){
    Serial.println(" - It's wet"); //물 있을 떄//
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  else {
    Serial.println(" - It's dry"); //물 없을 떄//
	  digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }
   delay(500);
}

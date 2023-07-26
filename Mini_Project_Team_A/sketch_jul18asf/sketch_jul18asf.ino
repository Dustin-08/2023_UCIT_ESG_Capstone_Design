const int dc=11; /*dc모터 핀 설정*/
int speed = 0; /*초기 모터 속력*/

int rainPin = A0; /*우적센서 핀 설정*/
int thresholdValue = 500; /* 우적 민감도 클수록 감도 심해짐 */

void setup(){
  Serial.begin(9600);
  pinMode(dc,OUTPUT);
  pinMode(rainPin, INPUT);
}

void loop(){
  
  analogWrite(dc,speed);            
  Serial.print("speed = ");
  Serial.println(speed);
  
int sensorValue = analogRead(rainPin); /*우적*/

  Serial.print(sensorValue); /*우적*/

  if(sensorValue < thresholdValue){
    Serial.println(" - It's wet"); //물 있을 때//
    
  }

  else {
    Serial.println(" - It's dry"); //물 없을 때//
    speed=100;
  } 

  
    if ( sensorValue > 1000 ) {
      speed=10;
      Serial.println("!10!");
    }
    else if  ( sensorValue < 1000 && sensorValue >500){
      speed=50;
      Serial.println("!50!");
    }
    else{
      speed=100;
      Serial.println("!100!");
    }
      

  
  delay(1000);
}

 


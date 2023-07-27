#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
hd44780_I2Cexp lcd;

int echo=8;
int trig=9;
int sensorPin = A0;

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;

void setup() {
  Serial.begin(9600);
	lcd.begin(16,2);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);

  
}

void loop() {
  float time;
  float dis;
  
  digitalWrite(trig,HIGH);
  delay(10);
  digitalWrite(trig,LOW);

  time=pulseIn(echo,HIGH);
  dis=((340*time)/10000)/2;
  int lightLevel = digitalRead(sensorPin);

  lcd.clear();
  if(dis<=20){
    Serial.println(dis);
    lcd.setCursor (8,0); //첫번째 입력 위치
		lcd.print("CLOSE"); //입력
  }else{
    lcd.setCursor (8,0);
    lcd.print("...");
  }
  
  if(lightLevel){
     lcd.setCursor (0,0); //첫번째 입력 위치
		 lcd.print("LIGHT"); //입력
   }else{
     //빛의 밝기가 50보다 크면 밝아요 출력
     lcd.setCursor (0,0);
     lcd.print("...");
   }
  
  
  Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);
 
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
 
//Serial.print("AngleX= ");
//Serial.println(x);
 
lcd.setCursor(0,1);
lcd.print("X");
lcd.setCursor(1,1);
lcd.print(x);

//Serial.print("AngleY= ");
//Serial.println(y);
 
lcd.setCursor(8,1);
lcd.print("Y");
lcd.setCursor(9,1);
lcd.print(y);

Serial.println("-----------------------------------------");
delay(1000);

}
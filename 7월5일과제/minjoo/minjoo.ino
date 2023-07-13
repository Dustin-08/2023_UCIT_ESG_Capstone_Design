#include <DHT11.h> 
DHT11 dht11(A0);

void setup() {
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);

}

void loop() {
  float temp,humi;
  int result = dht11.read(humi,temp);

   if (result == 0) 
  {

    Serial.print("temperature:"); 

    Serial.print(temp); 

    Serial.println();
    if(temp>=30.0){
      digitalWrite(9,LOW);
      digitalWrite(8,HIGH);
    }else{
      digitalWrite(9,LOW);
      digitalWrite(8,LOW);
    }


  }

  else

  {
    Serial.println();
    Serial.print("Error No :"); 
    Serial.print(result);
    Serial.println();

  }
  delay(DHT11_RETRY_DELAY);

}

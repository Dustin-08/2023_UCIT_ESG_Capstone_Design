#include <DHT11.h>

#define DHTTYPE DHT11
#define DHTPIN 2

DHT dht(DHTPIN, DHTTYPE);

int A 8;
int B 9;
 
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
}
 
void loop() {
  float temp = dht.readTemperature();
  Serial.print("Temp : ");
  Serial.print(temp);
  Serial.printin("'C");
  
  if(temp > 26.0)
  {
    digtalWrite(A, LOW);
    digtalWrite(B, HIGH);
  }
  else
  {
    digtalWrite(A, HIGH);
    digtalWrite(B, HIGH);
  }
}
// C++ code
int led = 8;
void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(115200); // 보드레이트 설정부분
}

void loop()
{
  digitalWrite(led, HIGH);
  Serial.println("LED 켜짐");
  delay(2000); // Wait for 2000 millisecond(s)
  digitalWrite(led, LOW);
  Serial.println("LED 꺼짐");
  delay(2000); // Wait for 2000 millisecond(s)
}

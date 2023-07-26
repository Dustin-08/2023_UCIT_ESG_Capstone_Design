void setup() // 초기 설정을 해주는 곳
{
  Serial.begin(9600); // 보드레이트를 9600으로 설정하는 부분
}

void loop() // 반복하는 부분
{
  Serial.println("Hello World!");
  delay(1000);
  Serial.print("줄넘김을 할 수 있는 ln을 붙이지 않는다면");
  Serial.println("이렇게 붙어서 출력됩니다.");
  delay(1000);
}

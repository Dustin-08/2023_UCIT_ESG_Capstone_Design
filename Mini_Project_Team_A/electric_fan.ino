/*
 * L9110의 방향 관련:
                                INA    | INB   | 결과
                                HIGH   | LOW   | 반시계 방향 회전
                                LOW    | HIGH  | 시계 방향 회전
                                HIGH   | HIGH  | 회전 X
                                LOW    | LOW   | 회전 X 
*/

int A = 8; // D8번 핀을 INA 핀으로 설정
int B = 9; // D9번 핀을 INB 핀으로 설정
 
void setup() {
  pinMode(A,OUTPUT); // A 핀을 출력으로 변경
  pinMode(B,OUTPUT);  // B 핀을 출력으로 변경 
}
 
void loop() {
  digitalWrite(A,LOW); //팬모터가 A방향으로 회전 (시계 방향 회전)
  digitalWrite(B,HIGH);
  delay(2000); //2초 후
 
  digitalWrite(A,HIGH); // 전체 정지
  digitalWrite(B,HIGH);
  delay(5000); //5초 후
}
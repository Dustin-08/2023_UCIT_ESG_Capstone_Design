// gitpull test

#include<Servo.h> //Servo 라이브러리를 추가
Servo servo;      //Servo 클래스로 servo객체 생성
int value = 0;    // 각도를 조절할 변수 value

void setup() { // 초기 설정을 해주는 곳
  servo.attach(9);     //servo 서보모터 9번 핀에 연결
                       // 이때 ~ 표시가 있는 PWM을 지원하는 디지털 핀에 연결
}

void loop() { // 반복하는 부분
    value = 0; // 0도 회전
    servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
    delay(500);

    value = 45; // 45도 회전
    servo.write(value);
    delay(500);

    value = 90; // 90도 회전
    servo.write(value);
    delay(500);

    value = 135; // 135도 회전
    servo.write(value);
    delay(500);

    value = 179; // 179도 회전 <- 서보모터의 경우 360도 서보모터가 아니라면 180도가 최대
    servo.write(value);
    delay(500);
}

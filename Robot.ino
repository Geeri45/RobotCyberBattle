#define MLF 5 // пин для левого мотора вперед
#define MLB 4 // пин для левого мотора назад
#define MRF 3 // пин для правого мотора вперед
#define MRB 2 // пин для правого мотора назад
#define IRP 8 // пин для инфрокрасного датчика

#define seg_1 9  // пин для первого сегмента клешни
#define seg_2 10 // пин для второго сегмента клешни
#define seg_3 11  // пин для третьего сегмента клешни
#define seg_4 12  // пин для четвертого сегмента клешни
#define cl 13 // пин для захвата клешни

#define button_forward 4049 // код для пульта вперед
#define button_left 4052 // код для пульта влево
#define button_right 4051   // код для пульта вправо
#define button_back 4050    // код для пульта назад
#define button_a 4010       // код для пульта A
#define button_b 4011       // код для пульта B
#define button_c 4012      // код для пульта C
#define button_d 4013       // код для пульта D

#include <IRremote.h>
#include <Servo.h>

Servo myservo;

IRrecv irrecv(IRP);
decode_results results;
unsigned long Key;

void rotate(int pin, int deg) {
  myservo.attach(pin);
  myservo.write(deg);
  delay(100);
  myservo.detach();
}

void fold() {           // складывание и взятие
  rotate(seg_1, 135);
  rotate(seg_2, 125);
  rotate(seg_3, 125);
  rotate(seg_4, 90);
  rotate(cl, 110);
}

void lift() {
  rotate(seg_1, 125);
  rotate(seg_2, 115);
  rotate(seg_3, 115);
  rotate(seg_4, 90);
  rotate(cl, 110);
}

void drop() { rotate(cl, -110); }   // выкинуть

void stop() {           // остановка
  digitalWrite(MLB, 0);
  digitalWrite(MRB, 0);
  digitalWrite(MLF, 0);
  digitalWrite(MRF, 0);
}

void forward() {        // движение вперед
  digitalWrite(MLB, 0);
  digitalWrite(MRB, 0);
  digitalWrite(MLF, 1);
  digitalWrite(MRF, 1);
}

void back() {           // движение назад
  digitalWrite(MLF, 0);
  digitalWrite(MRF, 0);
  digitalWrite(MLB, 1);
  digitalWrite(MRB, 1);
}

void right() {          // поворот вправо
  digitalWrite(MLB, 0);
  digitalWrite(MRF, 0);
  digitalWrite(MLF, 1);
  digitalWrite(MRB, 1);
}

void left() {           // поворот влево
  digitalWrite(MRB, 0);
  digitalWrite(MLF, 0);
  digitalWrite(MRF, 1);
  digitalWrite(MLB, 1);
}

void start() {
  back();
  delay(40);
  stop();
  fold();
  lift();
  forward();
  delay(395);
  right();
  delay(40);
  forward();
  delay(20);
  right();
  delay(60);
  forward();
  delay(60);
  right();
  delay(70);
  stop();
}

void setup() {
  pinMode(MLF, OUTPUT); // инициализация пинов ↓
  pinMode(MLB, OUTPUT);
  pinMode(MRF, OUTPUT);
  pinMode(MRB, OUTPUT);
  irrecv.enableIRIn(); // запускаем прием
  start();
}

void loop() {
  if (irrecv.decode(&results))  { // проверка данных
      Key = results.value;
      switch (Key)  {
        case button_forward:
          forward();  // вперед
          delay(20);
          stop();
          break;
        case button_right:
          right();   // вправо
          delay(20);
          stop();
          break;
        case button_left: 
          left();  // налево
          delay(20);
          stop();
          break;
        case button_back: 
          back(); // назад
          delay(20);
          stop();
          break;
        case button_a:
          fold(); // поднятие
          break;
        case button_b: // сделать клешню выше
          lift();
          break;
        case button_c: // выкинуть
          drop();
          break;
        case button_d:
          forward();  // вперед дальше
          delay(200);
          stop();
          break;
      }
      irrecv.resume(); // ожидаем следующей передачи
    }
}
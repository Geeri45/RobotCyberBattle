#define MLF 1 // пин для левого мотора вперед
#define MLB 1 // пин для левого мотора назад
#define MRF 1 // пин для правого мотора вперед
#define MRB 1 // пин для правого мотора назад
#define IRP 2 // пин для инфрокрасного датчика

#define button_forward 0x000 // код для пульта вперед
#define button_left 0x001    // код для пульта влево
#define button_right 0x002   // код для пульта вправо
#define button_back 0x003    // код для пульта назад
#define button_a 0x004       // код для пульта A
#define button_b 0x005       // код для пульта B
#define button_c 0x006       // код для пульта C
#define button_d 0x007       // код для пульта D

#include "IRremote.h"

IRrecv irrecv(IRP);
decode_results results;
unsigned long Key;

void setup() {
  pinMode(MLF, OUTPUT); // инициализация пинов ↓
  pinMode(MLB, OUTPUT);
  pinMode(MRF, OUTPUT);
  pinMode(MRB, OUTPUT);
  irrecv.enableIRIn(); // запускаем прием
}

void stop() {           // остановка
  digitalWrite(MLB, 0);
  digitalWrite(MRB, 0);
  digitalWrite(MLF, 0);
  digitalWrite(MRF, 0);
}

void forward() {        // движение вперед
  digitalWrite(MLF, 1);
  digitalWrite(MRF, 1);
}

void back() {           // движение назад
  digitalWrite(MLB, 1);
  digitalWrite(MRB, 1);
}

void right() {          // поворот вправо
  digitalWrite(MLF, 1);
  digitalWrite(MRB, 1);
}

void left() {           // поворот влево
  digitalWrite(MRF, 1);
  digitalWrite(MLB, 1);
}

void loop() {
  if (irrecv.decode(&results))  { // проверка данных
      Key = results.value;
      switch (Key)  {
        case button_forward:
          forward();  // вперед
          break;
        case button_right:
          back();   // назад
          break;
        case button_left: 
          left();  // налево
          break;
        case button_back: 
          right(); // направо
          break;
        default:
          break;
      }
      irrecv.resume(); // ожидаем следующей передачи
    } else {
      stop();
      irrecv.resume();
    }
}

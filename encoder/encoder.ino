#define CLK 10
#define DT 0
#include "GyverEncoder.h"


Encoder enc1(CLK, DT);
int value = 0;
void setup() {
Serial.begin(115200);
enc1.setType(TYPE1);
}
void loop() {

enc1.tick();

if (enc1.isRight()) value++;
if (enc1.isLeft()) value--;
if (value == 20 || value == -20) {
  value = 0;
  }
if (enc1.isTurn()) { 
Serial.println(value);
}
}

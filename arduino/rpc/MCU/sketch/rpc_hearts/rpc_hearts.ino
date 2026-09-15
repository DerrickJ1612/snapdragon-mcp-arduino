#include <Arduino_LED_Matrix.h>
#include "Arduino_RouterBridge.h"
#include "heart_frames.h"

const int STATUS_LED = LED_BUILTIN;
Arduino_LED_Matrix matrix;

int flash_heart() {
  digitalWrite(STATUS_LED, HIGH);

  matrix.loadSequence(HeartAnim);
  matrix.playSequence();
  delay(1000);
  matrix.loadFrame(HeartStatic);

  digitalWrite(STATUS_LED, LOW);
  return 1;
}

const char* mcu_ping() {
  for (int count = 0; count < 3; count++) {
    digitalWrite(STATUS_LED, HIGH);
    delay(100);
    digitalWrite(STATUS_LED, LOW);
    delay(100);
  }
  return "pong";
}

void setup() {
  pinMode(STATUS_LED, OUTPUT);
  digitalWrite(STATUS_LED, LOW);

  matrix.begin();
  matrix.clear();
  matrix.loadFrame(HeartStatic);

  if (!Bridge.begin()) {
    while (true) {
      digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
      delay(100);
    }
  }

  Bridge.provide("flash_heart", flash_heart);
  Bridge.provide("mcu_ping", mcu_ping);
}

void loop() {
  delay(1);
}

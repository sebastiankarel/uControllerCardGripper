#include <Servo.h>

#define PWM_PIN 9
#define VALVE_CLOSED 80
#define VALVE_OPEN 100

Servo servo;
byte val;

void setup() {
  Serial.begin(9600);
  servo.attach(PWM_PIN);
  val = VALVE_CLOSED;
}

void loop() {
  if (val == VALVE_CLOSED) {
    val = VALVE_OPEN;
    Serial.print("Open");
  } else {
    val = VALVE_CLOSED;
    Serial.print("Closed");
  }
  servo.write(val);
  delay(5000);
}

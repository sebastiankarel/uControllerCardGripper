#include <Servo.h>

#define COMMAND_ATTACH 'a'
#define COMMAND_DETACH 'd'

#define PWM_PIN 3
#define VALVE_CLOSED 80
#define VALVE_OPEN 100

Servo servo;

byte received_command;
byte current_state;

void setup() {
  //RX: Pin 7, TX: Pin 8 on Teensy 3.2
  Serial3.begin(9600);
  Serial.begin(9600);
  servo.attach(PWM_PIN);
}

void loop() {
  if (Serial3.available()) {
    received_command = Serial3.read();
    if (received_command == COMMAND_ATTACH) {
      servo.write(VALVE_CLOSED);
    } else if (received_command == COMMAND_DETACH) {
      servo.write(VALVE_OPEN);
    }
  }
}

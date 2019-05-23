#include <Servo.h>

#define COMMAND_ATTACH 'a'
#define COMMAND_DETACH 'd'

#define HEART_BEAT_1 'O'
#define HEART_BEAT_2 'K'
#define HEART_BEAT_3 '\n'
#define HEART_BEAT_INTERVAL 1000

#define PWM_PIN 9
#define VALVE_CLOSED 80
#define VALVE_OPEN 100

Servo servo;

long t_diff;
long t_last;

byte received_command;
byte current_state;

void setup() {
  t_diff = 0;
  t_last = 0;
  Serial3.begin(9600);
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
  t_diff += millis() - t_last;
  if (t_diff >= HEART_BEAT_INTERVAL) {
    Serial3.write(HEART_BEAT_1);
    Serial3.write(HEART_BEAT_2);
    Serial3.write(HEART_BEAT_3);
    t_diff = 0;
  }
  t_last = millis();
}

/**
 * Initializes the bluetooth module
 * Only needed once since the module
 * has flash memory to save settings
 */
void init_bt_connection(){  
  Serial3.print("AT");
  delay(400); 
  Serial3.print("AT+DEFAULT");
  delay(2000); 
  Serial3.print("AT+ROLES");
  delay(400); 
  Serial3.print("AT+NAMEGripper");
  delay(400);
  Serial3.print("AT+PIN1234");
  delay(400);
  Serial3.print("AT+AUTH1");
  delay(400);    
  Serial3.flush();
}

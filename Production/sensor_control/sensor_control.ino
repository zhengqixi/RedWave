#include <Wire.h>
#include <NewPing.h>

/*
 * LED Wirings
 * Left A0
 * Left_Up A1
 * Center A2
 * Right_Up A3
 */

#define SONAR_NUM 5 // Number or sensors.
#define MAX_DISTANCE 300 // Max distance in cm.
#define PING_INTERVAL 100 // Milliseconds between pings.
#define wire_port 0x20 //Slave address

unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int cm[SONAR_NUM]; // Store ping distances.
unsigned int ir[4]; // Store IR readings
uint8_t currentSensor = 0; // Which sensor is active.
char command = 'F'; //Always move foward...
     
NewPing sonar[SONAR_NUM] = { // Sensor object array. Trigger,Echo (PWM)
  NewPing(13, 11, MAX_DISTANCE),
  NewPing(13, 10, MAX_DISTANCE),
  NewPing(13, 9, MAX_DISTANCE),
  NewPing(13, 6, MAX_DISTANCE),
  NewPing(13, 5, MAX_DISTANCE),
};

void echo_check();
void react();
void send_command();
void check_ir();

void setup() {
  Wire.begin(wire_port); // join i2c bus (address optional for master)
  Wire.onRequest(send_command);
  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < SONAR_NUM; i++){
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
  }
  Serial.begin(9600);
}



void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;
      if (i == 0 && currentSensor == SONAR_NUM - 1){
        check_ir();
        react();
      }
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      cm[currentSensor] = 0;
      sonar[currentSensor].ping_timer(echo_check);
        }
      }
      // The rest of your code would go here.
    }

void echo_check() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void react(){
  /*
   * This is the code where logic for the next move is based. To determine the bot's next move, simply alter global variable 
   * 'command'
   * Don't ask me how this will work
   * the ir array stores ir sensor readings
   * cm stores sonar sensor readings
   * heh
   * enjoy
   * Here are the commands:
   * F - forward
   * B - backward
   * L - left
   * R - right
   * S - brake
   * X - fire
   */
}

void check_ir(){
  ir[0] = analogRead(0);
  ir[1] = analogRead(1);
  ir[2] = analogRead(2);
  ir[3] = analogRead(3);
}

void send_command(){
  Wire.write(command);
}


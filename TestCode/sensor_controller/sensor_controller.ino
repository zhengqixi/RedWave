#include <Wire.h>
#include <NewPing.h>

/*
 * LED Wirings
 * Left A0
 * Left_Up A1
 * Center A2
 * Right_Up A3
 */

#define SONAR_NUM     5 // Number or sensors.
#define MAX_DISTANCE 500 // Max distance in cm.
#define PING_INTERVAL 100 // Milliseconds between pings.

unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int cm[SONAR_NUM]; // Store ping distances.
uint8_t currentSensor = 0; // Which sensor is active.
     
NewPing sonar[SONAR_NUM] = { // Sensor object array. Trigger,Echo (PWM)
  NewPing(13, 11, MAX_DISTANCE),
  NewPing(13, 10, MAX_DISTANCE),
  NewPing(13, 9, MAX_DISTANCE),
  NewPing(13, 6, MAX_DISTANCE),
  NewPing(13, 5, MAX_DISTANCE),
};

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < SONAR_NUM; i++){
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
  }
  Serial.begin(9600);
}

void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void react() {
  int duration = 1500;
  char direct = 'F';
  if (cm[2] < 10){
    direct = 'B';
  }
  if (cm[1] < 20){
    direct = 'R';
  } else if (cm[3] < 20){
    direct = 'L';
  }
  Serial.print(cm[0]);Serial.print(" ");
  Serial.print(cm[1]);Serial.print(" ");
  Serial.print(cm[2]);Serial.print(" ");
  Serial.print(cm[3]);Serial.print(" ");
  Serial.print(cm[4]);Serial.print(" ");
  Wire.beginTransmission(8); // transmit to motor driver
  Wire.write(direct);        // sends direction
  Wire.write(duration);      // sends duration
  Wire.endTransmission();    // stop transmitting
}


void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;
      if (i == 0 && currentSensor == SONAR_NUM - 1)
        react(); // Do something with results.
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      cm[currentSensor] = 0;
      sonar[currentSensor].ping_timer(echoCheck);
        }
      }
      // The rest of your code would go here.
    }

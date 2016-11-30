// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include<AFMotor.h>
#include <Wire.h>
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor3(3, MOTOR34_64KHZ); // create motor #3, 64KHz pwm

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  motor2.setSpeed(255);
  motor3.setSpeed(255);
}

void loop() {
}

void forward(int duration){
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  delay(duration);
}

void backward(int duration){
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  delay(duration);
}

void right(int duration){
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  delay(duration);
}

void left(int duration){
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  delay(duration);
}
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  char direct = Wire.read();
  int duration = Wire.read();
  Serial.print(direct);
  switch(direct){
    case 'F':
      forward(duration);
      break;
    case 'B':
      backward(duration);
      break;
    case 'L':
      left(duration);
      break;
    case 'R':
      right(duration);
      break;  
  }
  
}

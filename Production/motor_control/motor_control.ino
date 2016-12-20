#include<Adafruit_MotorShield.h>
#include<Wire.h>
#define motor_front_port 3
#define motor_back_port 1
#define wire_port 0x20
#define default_speed 255
#define fire_pin 6

Adafruit_MotorShield shield = Adafruit_MotorShield(0x60);
Adafruit_DCMotor* motor_front = shield.getMotor(motor_front_port);
Adafruit_DCMotor* motor_back = shield.getMotor(motor_back_port);

void forward();
void backward();
void right();
void left();
void brake();
void fire();

void setup() {
  shield.begin();

  motor_front->setSpeed(default_speed);
  motor_front->run(FORWARD);
  motor_front->run(RELEASE);

  motor_back->setSpeed(default_speed);
  motor_back->run(FORWARD);
  motor_back->run(RELEASE);

  Wire.begin();
  pinMode(fire_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(wire_port, 1);
  char command = Wire.read();
  switch(command) {
    case 'F':
      forward(); 
      break;
    case 'B':
      backward();
      break;
    case 'L':
      right();
      break;
    case 'R':
      left();
      break;
    case 'S':
      brake();
      break;
    case 'X':
      fire();
      break;
  }
  Serial.println(command);
  delay(100); // we want to give time for the sonars to get a full cycle or something
}

void forward(){
  motor_front->run(FORWARD);
  motor_back->run(FORWARD);
}
void backward(){
  motor_front->run(BACKWARD);
  motor_back->run(BACKWARD);
}
void right(){
  motor_front->run(FORWARD);
  motor_back->run(BACKWARD);
}
void left(){
  motor_front->run(BACKWARD);
  motor_back->run(FORWARD);
}
void brake(){
  motor_front->run(RELEASE);
  motor_back->run(RELEASE);
}
void fire(){
  digitalWrite(fire_pin, HIGH);
  delay(100);
  digitalWrite(fire_pin, LOW);
}


#include<Adafruit_MotorShield.h>
#include<Wire.h>
#define motor_front_port 1
#define motor_back_port 2
#define wire_port 8
#define default_speed 255

Adafruit_MotorShield shield = Adafruit_MotorShield();
Adafruit_DCMotor* motor_front = shield.getMotor(motor_front_port);
Adafruit_DCMotor* motor_back = shield.getMotor(motor_back_port);

void forward(int duration);
void backward(int duration);
void right(int duration);
void left(int duration);

void setup() {
  shield.begin();

  motor_front->setSpeed(default_speed);
  motor_front->run(FORWARD);
  motor_front->run(RELEASE);

  motor_back->setSpeed(default_speed);
  motor_back->run(FORWARD);
  motor_back->run(RELEASE);

  Wire.begin(wire_port);
  Wire.onReceive(execute_command);
}

void loop() {
}

void execute_command(int howMany) {
  char command = Wire.read();
  int duration = Wire.read();
  switch(command) {
    case 'F':
      forward(duration); 
      break;
    case 'B':
      backward(duration);
      break;
    case 'L':
      right(duration);
      break;
    case 'R':
      left(duration);
      break;
  }
}

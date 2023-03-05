/******************************************************************************
  TestRun.ino
  TB6612FNG H-Bridge Motor Driver Example code
  Michelle @ SparkFun Electronics
  8/20/16
  https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library

  Uses 2 motors to show examples of the functions in the library.  This causes
  a robot to do a little 'jig'.  Each movement has an equal and opposite movement
  so assuming your motors are balanced the bot should end up at the same place it
  started.

  Resources:
  TB6612 SparkFun Library

  Development environment specifics:
  Developed on Arduino 1.6.4
  Developed with ROB-9457
******************************************************************************/

// This is the library for the TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define BIN1 8
#define BIN2 7
#define PWMB 11
#define STBY 9
String command;
// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1

const int offsetB = -1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {
  Serial.begin(9600);
  pinMode(13, INPUT);
}

void loop()
{
  if(Serial.available()){
  if (digitalRead(13) == HIGH) {
    motor.drive(-120, 500);
    motor.drive(120, 500);
    motor.brake();
   
    delay(1000);
  }
  else {
    motor.drive(0, 1000);
  }
  delay(2000);
  exit(0);
}
}

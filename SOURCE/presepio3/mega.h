#include <new.h>
#include <Servo.h>
#include "servo_controller.h"

#define SERVOS_NUMBER 12

ServoParameters servo2 = {
   2,         // servo_pin
   22,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo3 = {
   3,         // servo_pin
   23,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo4 = {
   4,         // servo_pin
   24,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo5 = {
   5,         // servo_pin
   25,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo6 = {
   6,         // servo_pin
   26,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo7 = {
   7,         // servo_pin
   27,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo8 = {
   8,         // servo_pin
   28,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo9 = {
   9,         // servo_pin
   29,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo10 = {
   10,      // servo_pin
   30,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo11 = {
   11,      // servo_pin
   31,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo12 = {
   12,      // servo_pin
   32,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo13 = {
   13,       // servo_pin
   33,       // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters *parameters_array[] = {
  &servo2,
  &servo3,
  &servo4,
  &servo5,
  &servo6,
  &servo7,
  &servo8,
  &servo9,
  &servo10,
  &servo11,
  &servo12,
  &servo13,
};

ServoController *servo_array[SERVOS_NUMBER];

#include <new.h>
#include <Servo.h>
#include "servo_controller.h"

#define SERVOS_NUMBER 6

ServoParameters servo3 = {
   3,        // servo_pin
   2,        // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo5 = {
   5,        // servo_pin
   4,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo6 = {
   6,        // servo_pin
   7,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo9 = {
   9,        // servo_pin
   8,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo10 = {
   10,      // servo_pin
   12,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters servo11 = {
   11,      // servo_pin
   13,      // input_pin
   0,        // initial_position
   180,   // final_position
   10      // expected_delay
};

ServoParameters *parameters_array[] = {
  &servo3,
  &servo5,
  &servo6,
  &servo9,
  &servo10,
  &servo11
};

ServoController *servo_array[SERVOS_NUMBER];

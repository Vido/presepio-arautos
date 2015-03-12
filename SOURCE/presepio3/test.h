#include <new.h>
#include <Servo.h>
#include "servo_controller.h"

#define SERVOS_NUMBER 1

ServoParameters servo3 = {
   3,             // servo_pin
   8,             // input_pin
   0,             // initial_position
   180,        // final_position
   10           // expected_delay
};

ServoParameters *parameters_array[] = {
  &servo3
};

ServoController *servo_array[SERVOS_NUMBER];

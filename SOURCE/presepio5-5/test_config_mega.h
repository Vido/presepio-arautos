#include <new.h>
#include <Servo.h>
#include "servo_controller.h"

#define SERVOS_NUMBER 1

ServoParameters servo2 = {
   11,         // servo_pin
   5,      // input_pin
   150,        // initial_position
   10,   // final_position
   30      // expected_delay
};

ServoParameters *parameters_array[] = {
  &servo2,
};

ServoController *servo_array[SERVOS_NUMBER];

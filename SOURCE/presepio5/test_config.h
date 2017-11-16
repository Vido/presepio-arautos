#include "servo_controller.h"

// Numero total de enderecos de servo
#define SERVOS_NUMBER 1

ServoParameters servo0 = {
   2,        // servo_address (nao mudar !!!)
   24,        // input_pin
   103,   // min_12bits_pwm 
   510,   // max_12bits_pwm
   0,        // initial_position
   100,   // final_position
   30         // expected_delay
};

ServoParameters *parameters_array[] = {
  &servo0,
};

ServoController *servo_array[SERVOS_NUMBER];

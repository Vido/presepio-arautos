#include "adafruit_controller.h"

AdafruitParameters servo0 = {
   2,        // servo_address (nao mudar !!!)
   24,        // input_pin
   103,   // min_12bits_pwm 
   510,   // max_12bits_pwm
   0,        // initial_position
   100,   // final_position
   30         // expected_delay
};

AdafruitParameters *param_adafruit_array[] = {
  &servo0,
};

#define ADAFRUIT_CHANNELS_NUMBER 1
AdafruitController *adafruit_array[SERVOS_NUMBER];

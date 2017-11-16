#include "stepper_controller.h"

// Numero total de enderecos de servo
#define STEPPER_NUMBER 1

StepperParameters stepper0 = {
    6,       // input_pin (Fio da LightORama)
    10,       // enable_pin (Fio Verde, sempre ligado)
    9,       // direction_pin (Fio Laranja, controlado pelo firmware)
    HORARIO, // spin_direction (HORARIO ou ANTIHORARIO)
    8,       // step_pin (Fio Amarelo, controlado pelo firmware)
    400,     // step_number (de 0 a 400)
    20       // expected_delay
};

StepperParameters *param_stepper_array[] = {
  &stepper0,
};

StepperController *stepper_array[STEPPER_NUMBER];

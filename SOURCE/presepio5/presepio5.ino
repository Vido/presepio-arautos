#include <Wire.h>
#define DEBUG

//#define ENABLE_SERVO
#ifdef ENABLE_SERVO
  #include <Servo.h>
  #include "servo_config_mega.h"
  //#include "test_config_mega.h"
#endif

// #define ENABLE_ADAFRUIT
#ifdef ENABLE_ADAFRUIT
  #include <Adafruit_PWMServoDriver.h>
  #include "adafruit_config.h"
  //#include "test_config_adafruit.h"
#endif

#define ENABLE_STEPPER
#ifdef ENABLE_STEPPER
  #include "config_stepper.h"
  //#include "test_stepper.h"
#endif

void setup(){
    #ifdef DEBUG
        Serial.begin(115200);
        Serial.println("SERIAL DEBUG [ON]");
    #endif

    #ifdef ENABLE_SERVO    
        for(int i=0; i < SERVOS_NUMBER; i++){
            servo_array[i] = new ServoController(parameters_array[i]->servo_pin, *parameters_array[i]);
            pinMode(servo_array[i]->get_servo_pin(), OUTPUT);
            pinMode(servo_array[i]->input_pin, INPUT);
            servo_array[i]->attach();
            #ifdef DEBUG
                Serial.print("Starting SERVO: ");
                Serial.println(i);
            #endif
    }
    #endif

    #ifdef ENABLE_ADAFRUIT
      servo_driver.begin();
      servo_driver.setPWMFreq(PWM_FREQUENCY);
    
      for(unsigned int i=0; i < ADAFRUIT_CHANNELS_NUMBER; i++){
          pinMode(param_adafruit_array[i]->input_pin, INPUT);
          adafruit_array[i] = new AdafruitController(
          param_adafruit_array[i]->servo_address, *param_adafruit_array[i]);
          #ifdef DEBUG
            Serial.print("Starting SERVO Adafruit: ");
            Serial.println(i);
          #endif
      }
    #endif

    #ifdef ENABLE_STEPPER
    for(unsigned int i=0; i < STEPPER_NUMBER; i++){
        pinMode(param_stepper_array[i]->input_pin, INPUT);
        pinMode(param_stepper_array[i]->enable_pin, OUTPUT);
        pinMode(param_stepper_array[i]->direction_pin, OUTPUT);
        pinMode(param_stepper_array[i]->step_pin, OUTPUT);
        //
        digitalWrite(param_stepper_array[i]->step_pin, LOW);
        digitalWrite(param_stepper_array[i]->direction_pin, HIGH);
        digitalWrite(param_stepper_array[i]->enable_pin, LOW);

        stepper_array[i] = new StepperController(
          *param_stepper_array[i]);

        #ifdef DEBUG
            Serial.print("Starting STEPPER: ");
            Serial.println(i);
        #endif

        // ESPECIAL - MAQUINA ESTADOS
        pinMode(stepper_special_params.input_pin, INPUT);
        pinMode(stepper_special_params.reset_pin, INPUT);
        pinMode(stepper_special_params.enable_pin, OUTPUT);
        pinMode(stepper_special_params.direction_pin, OUTPUT);
        pinMode(stepper_special_params.step_pin, OUTPUT);
        //
        digitalWrite(stepper_special_params.step_pin, LOW);
        digitalWrite(stepper_special_params.direction_pin, HIGH);
        digitalWrite(stepper_special_params.enable_pin, LOW);

        special_stepper = new StateMachineStepperController(stepper_special_params);

        #ifdef DEBUG
            Serial.print("Starting Special STEPPER : ");
        #endif
    }
    #endif
};

void loop(){

   #ifdef ENABLE_SERVO
  // Servo
  for(int i=0; i < SERVOS_NUMBER; i++){
        #ifdef DEBUG
            // Serial.print("Servo: ");
        #endif
        servo_array[i]->next();
  }
  #endif
  
   #ifdef ENABLE_ADAFRUIT
  // Adafruit
  for(int i=0; i < ADAFRUIT_CHANNELS_NUMBER; i++){
        #ifdef DEBUG
            Serial.print("Servo: ");
            Serial.println(adafruit_array[i]->get_servo_address());
        #endif
        adafruit_array[i]->next();
  }
  #endif

  #ifdef ENABLE_STEPPER
  // Stepper
  for(int i=0; i < STEPPER_NUMBER; i++){
        #ifdef DEBUG
            Serial.print("Stepper: ");
            Serial.println(i);
        #endif
        stepper_array[i]->next();
  }
  // Stepper State Machine:
  special_stepper->next_sm();
  #endif

};

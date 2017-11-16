#include <Wire.h>
//#define DEBUG

//#define ENABLE_SERVO
#ifndef ENABLE_SERVO
  #include <Adafruit_PWMServoDriver.h>
  #include "config_servo.h"
  //#include "test_config.h"
#endif

#define ENABLE_STEPPER
#ifdef ENABLE_STEPPER
  //#include "config_stepper.h"
  #include "test_stepper.h"
#endif

void setup(){
    #ifdef DEBUG
        Serial.begin(9600);
        Serial.println("SERIAL DEBUG [ON]");
    #endif

    #ifdef ENABLE_SERVO
      servo_driver.begin();
      servo_driver.setPWMFreq(PWM_FREQUENCY);
    
      for(unsigned int i=0; i < SERVOS_NUMBER; i++){
          pinMode(parameters_array[i]->input_pin, INPUT);
          servo_array[i] = new ServoController(
          parameters_array[i]->servo_address, *parameters_array[i]);
          #ifdef DEBUG
            Serial.print("Starting SERVO: ");
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
        digitalWrite(param_stepper_array[i]->enable_pin, HIGH);
           
        stepper_array[i] = new StepperController(
          *param_stepper_array[i]);
        
        #ifdef DEBUG
            Serial.print("Starting SERVO: ");
            Serial.println(i);
        #endif      
    }
    #endif
};

void loop(){

   #ifdef ENABLE_SERVO
  // Servo
  for(int i=0; i < SERVOS_NUMBER; i++){
        #ifdef DEBUG
            Serial.print("Servo: ");
            Serial.println(servo_array[i]->get_servo_address());
        #endif
        servo_array[i]->next();
  }
  #endif
  
  #ifdef ENABLE_STEPPER
  // Stepper
  for(int i=0; i < STEPPER_NUMBER; i++){
        #ifdef DEBUG
            //Serial.print("Stepper: ");
            //Serial.println(i);
        #endif
        stepper_array[i]->next();
  }
  #endif

};

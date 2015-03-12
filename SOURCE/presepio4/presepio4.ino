//#define DEBUG

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "config.h"
//#include "test_config.h"

void setup(){
    #ifdef DEBUG
        Serial.begin(9600);
    #endif

    servo_driver.begin();
    servo_driver.setPWMFreq(PWM_FREQUENCY);
  
    for(unsigned int i=0; i < SERVOS_NUMBER; i++){
        pinMode(parameters_array[i]->input_pin, INPUT);
        servo_array[i] = new ServoController(
        parameters_array[i]->servo_address, *parameters_array[i]);
    }
};

void loop(){
    for(int i=0; i < SERVOS_NUMBER; i++){
        #ifdef DEBUG
            Serial.print("Servo: ");
            Serial.println(servo_array[i]->get_servo_address());
        #endif
        servo_array[i]->next();
  }
};

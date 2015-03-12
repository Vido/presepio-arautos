#include <Servo.h>
#include "mega.h"

//#include "uno.h"
//#include "test.h"

//#define DEBUG

void setup(){
  #ifdef DEBUG
    Serial.begin(9600);
  #endif

  for(int i=0; i < SERVOS_NUMBER; i++){
    servo_array[i] = new ServoController(parameters_array[i]->servo_pin, *parameters_array[i]);
    pinMode(servo_array[i]->get_servo_pin(), OUTPUT);
    pinMode(servo_array[i]->input_pin, INPUT);
    servo_array[i]->attach();
  }
};

void loop(){
  for(int i=0; i < SERVOS_NUMBER; i++){
    #ifdef DEBUG
      Serial.print("Servo: ");
      Serial.println(servo_array[i]->get_servo_pin());
    #endif
    servo_array[i]->next();
  }
};

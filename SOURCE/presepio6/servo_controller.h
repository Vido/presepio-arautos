#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

//#define SERVO_DEBUG

// #include <Servo.h> Must be imported outside.
#include <Arduino.h> 

struct servo_parameters{
  int servo_pin;  
  int input_pin;
  int initial_position;
  int final_position;
  long expected_delay;
};

typedef struct servo_parameters ServoParameters;

class ServoController{
  public:
    ServoController(int servo_pin);
    ServoController(int servo_pin, int input_pin, int initial_position, int final_position, long expected_delay);
    ServoController(int servo_pin, ServoParameters parameters);
    void next();
    void attach();
    int get_servo_pin();
    //
    int input_pin;
    int initial_position;
    int final_position;
    long expected_delay;
    
  private:
    void move_forward(int sweep_direction);
    void move_back(int sweep_direction);
    //
    Servo my_servo;
    int servo_pin;
    int current_position;
    long current_delay;
};

ServoController::ServoController(int servo_pin){
  this->servo_pin=servo_pin;
  //this->my_servo.attach(servo_pin);
  this->current_delay=millis();
};

ServoController::ServoController(int servo_pin, int input_pin, int initial_position, int final_position, long expected_delay){
  this->servo_pin=servo_pin;
  //this->my_servo.attach(servo_pin);
  this->current_delay=millis();
  this->input_pin = input_pin;
  this->initial_position = initial_position;
  this->final_position = final_position;
  this->expected_delay = expected_delay;
};

ServoController::ServoController(int servo_pin, ServoParameters parameters){
  this->servo_pin=servo_pin;
  //this->my_servo.attach(servo_pin);
  this->current_delay=millis();
  this->input_pin = parameters.input_pin;
  this->initial_position = parameters.initial_position;
  this->final_position = parameters.final_position;
  this->expected_delay = parameters.expected_delay;
};

void ServoController::attach(){
  my_servo.attach(servo_pin);
  current_position = initial_position;
  my_servo.write(current_position);
}

int ServoController::get_servo_pin(){
  return this->servo_pin;
}

void ServoController::move_back(int sweep_direction){
  int sig = sweep_direction;  
  if((sig * initial_position) < (sig * current_position)){
      current_position -= sweep_direction;
      my_servo.write(current_position);
    }
};

void ServoController::move_forward(int sweep_direction){
    int sig = sweep_direction;
    if((sig * final_position) > (sig * current_position)){
      current_position += sweep_direction;
      my_servo.write(current_position);
    }
};

void ServoController::next(){
  boolean reading = false;
  int sweep_direction = 0;
  reading = digitalRead(input_pin);
  if (final_position > initial_position) sweep_direction++;
  else  sweep_direction--;

  #ifdef SERVO_DEBUG
  Serial.print("Reading:\t");
  Serial.print(reading);
  Serial.print("\tPosition:\t");
  Serial.print(current_position);
  Serial.print("\tsweep_direction:\t");
  Serial.print(sweep_direction);
  Serial.print("\tDelay:\t");
  Serial.println(millis() - current_delay);
  #endif
  
  if ((millis() - current_delay) >  expected_delay){
    if(reading){ 
      move_forward(sweep_direction);
    }else{
      move_back(sweep_direction);
    }
    current_delay = millis();
  } 
};

#endif

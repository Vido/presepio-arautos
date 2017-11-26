#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#define PWM_FREQUENCY 50

#ifdef DEBUG
    #define SERVO_DEBUG
#endif

#include <math.h>
#include <Arduino.h>
// #include <Servo.h> Must be imported outside.
// #include <Wire.h> Must be imported outside.
// #include <Adafruit_PWMServoDriver.h> Must be imported outside.

Adafruit_PWMServoDriver servo_driver = Adafruit_PWMServoDriver(0x40);

struct adafruit_parameters{
    unsigned int servo_address;
    unsigned int input_pin;
    unsigned int min_12bits_pwm;
    unsigned int max_12bits_pwm;
    int initial_position;
    int final_position;
    unsigned long expected_delay;
};

typedef struct adafruit_parameters AdafruitParameters;

class AdafruitController{
    public:
        AdafruitController(unsigned int servo_address);
        AdafruitController(unsigned int servo_address, AdafruitParameters parameters);
        AdafruitController(unsigned int servo_address,
                                     unsigned int input_pin,
                                     unsigned int min_12bits_pwm,
                                     unsigned int max_12bits_pwm,
                                     int initial_position,
                                     int final_position,
                                     unsigned long expected_delay);
        
        void next();
        unsigned int get_servo_address();
        int get_servo_position();
        //
        unsigned int input_pin;
        unsigned int min_12bits_pwm;
        unsigned int max_12bits_pwm;
        int initial_position;
        int final_position;
        unsigned long expected_delay;
 
    private:
        void move_forward(int sweep_direction);
        void move_back(int sweep_direction);
        //
        unsigned int servo_address;
        unsigned int current_position;
        unsigned long current_delay;
};

AdafruitController::AdafruitController(unsigned int servo_address){
    int pwm_bus = 1 << 12;
    double period_ms = 1000.0 / PWM_FREQUENCY;
    //
    this->servo_address=servo_address;
    this->input_pin = 0;
    this->initial_position = 90;
    this->final_position = 90;
    //
    this->current_delay=millis();
    this->min_12bits_pwm = ceil(pwm_bus / (period_ms / 0.5));
    this->max_12bits_pwm = floor(pwm_bus / (period_ms / 2.5));
    this->expected_delay = (1<<32)-1;
};

AdafruitController::AdafruitController(unsigned int servo_address,
                                                                 unsigned int input_pin,
                                                                 unsigned int min_12bits_pwm,
                                                                 unsigned int max_12bits_pwm,
                                                                 int initial_position,
                                                                 int final_position,
                                                                 unsigned long expected_delay){
    this->input_pin = input_pin;
    this->min_12bits_pwm = min_12bits_pwm;
    this->max_12bits_pwm = max_12bits_pwm;
    //
    this->initial_position = initial_position;
    this->final_position = final_position;
    this->expected_delay = expected_delay;
    //
    this->servo_address=servo_address;
    this->current_delay=millis();
    this->current_position = this->initial_position;
};

AdafruitController::AdafruitController(unsigned int servo_address,
                                                                 AdafruitParameters parameters){
    this->input_pin = parameters.input_pin;
    this->min_12bits_pwm = parameters.min_12bits_pwm;
    this->max_12bits_pwm = parameters.max_12bits_pwm;
    //
    this->initial_position = parameters.initial_position;
    this->final_position = parameters.final_position;
    this->expected_delay = parameters.expected_delay;
    //
    this->servo_address=servo_address;
    this->current_delay=millis();
    this->current_position = this->initial_position;
};

unsigned int AdafruitController::get_servo_address(){
    return this->servo_address;
};

int AdafruitController::get_servo_position(){
    return this->current_position;
};

void AdafruitController::move_back(int sweep_direction){
    boolean end_stop = true;   
    int pos = map(current_position, 0, 180, min_12bits_pwm, max_12bits_pwm);

    if(sweep_direction>0){
      if((initial_position) < (current_position)) end_stop = false;
    }else{
      if((initial_position) > (current_position)) end_stop = false;
    }
    
    if(!end_stop){
        current_position -= sweep_direction;
        servo_driver.setPWM(servo_address, 0, pos);

        #ifdef SERVO_DEBUG
            Serial.print("\tNorm.Pos:\t");
            Serial.print(pos);
        #endif
    }
};

void AdafruitController::move_forward(int sweep_direction){
  boolean end_stop = true;   
  int pos = map(current_position, 0, 180, min_12bits_pwm, max_12bits_pwm);
    
    if(sweep_direction>0){
      if((final_position) > (current_position)) end_stop = false;
    }else{
      if((final_position) < (current_position)) end_stop = false;
    }
    
    if(!end_stop){
        current_position += sweep_direction;
        servo_driver.setPWM(servo_address, 0, pos);
      
        #ifdef SERVO_DEBUG
            Serial.print("\tNorm.Pos:\t");
            Serial.print(pos);
        #endif
    }
};

void AdafruitController::next(){
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
        Serial.print(millis() - current_delay);
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

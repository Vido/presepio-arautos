#ifndef STEPPER_CONTROLLER_H
#define STEPPER_CONTROLLER_H

#define PWM_FREQUENCY 50

#ifdef DEBUG
    #define STEPPER_DEBUG
#endif

#define ANTIHORARIO 0
#define HORARIO 1

#include <math.h>
#include <Arduino.h>
// #include <Wire.h> Must be imported outside.

inline void pulseOut(int pin, int us)
{
   us = max(us - 20, 1);
   digitalWrite(pin, LOW);
   delayMicroseconds(us);   
   digitalWrite(pin, HIGH); 
   delayMicroseconds(us);
   digitalWrite(pin, LOW);
}

struct stepper_parameters{
    unsigned int input_pin;
    unsigned int enable_pin;
    unsigned int direction_pin;
    unsigned int spin_direction;
    unsigned int step_pin;
    unsigned int step_number;
    unsigned long expected_delay;
};

typedef struct stepper_parameters StepperParameters;

class StepperController{
    public:
        StepperController(StepperParameters parameters);
        StepperController(unsigned int input_pin,
                          unsigned int enable_pin,
                          unsigned int direction_pin,
                          unsigned int spin_direction,
                          unsigned int step_pin,
                          unsigned int step_number,
                          unsigned long expected_delay);
        
        void next();
        unsigned int get_servo_address();
        //int get_servo_position();
        //
        unsigned int input_pin;
        unsigned int enable_pin;
        unsigned int direction_pin;
        unsigned int spin_direction;
        unsigned int step_pin;
        unsigned int step_number;
        unsigned long expected_delay;
 
    private:
        void move_forward();
        void move_back();
        //
        unsigned int current_position;
        bool state_step_pin;
        unsigned long current_delay;
};

/*
StepperController::StepperController(unsigned int servo_address){
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
*/

StepperController::StepperController(unsigned int input_pin,
                                     unsigned int enable_pin,
                                     unsigned int direction_pin,
                                     unsigned int spin_direction,
                                     unsigned int step_pin,
                                     unsigned int step_number,
                                     unsigned long expected_delay){
    this->enable_pin = enable_pin;
    this->direction_pin = direction_pin;
    this->step_pin = step_pin;
    //
    this->spin_direction = spin_direction;
    this->step_number = step_number;
    this->expected_delay = expected_delay;
    //
    this->current_delay=millis();
    this->current_position = 0;
};

StepperController::StepperController(StepperParameters parameters){

    this->input_pin = parameters.input_pin;
    //
    this->enable_pin = parameters.enable_pin;
    this->direction_pin = parameters.direction_pin;
    this->step_pin = parameters.step_pin;
    //
    
    this->spin_direction = parameters.spin_direction;
    this->step_number = parameters.step_number;
    this->expected_delay = parameters.expected_delay;
    //
    this->current_delay=millis();
    this->current_position = 0;
};

/*
int StepperController::get_servo_position(){
    return this->current_position;
};
*/

void StepperController::move_back(){

    boolean end_stop = false;
    if(abs(current_position) <= 0) end_stop = true;
    
    if(!end_stop){
        current_position--;
        digitalWrite(direction_pin, bool(!spin_direction));
        pulseOut(step_pin, 20);
    }
};

void StepperController::move_forward(){

    boolean end_stop = false;
    if(abs(current_position) >= step_number) end_stop = true;
    
    if(!end_stop){        
        current_position++;
        digitalWrite(direction_pin, bool(spin_direction));
        pulseOut(step_pin, 20);
    }
};

void StepperController::next(){

    boolean reading = false;
    int sweep_direction = 0;
    reading = digitalRead(input_pin);
    
    if ((millis() - current_delay) >  expected_delay){
       
          #ifndef SERVO_DEBUG
              Serial.print("Reading:\t");
              Serial.print(reading);
              Serial.print("Step State:\t");
              Serial.print(state_step_pin);
              Serial.print("\tPosition:\t");
              Serial.print(current_position);
              Serial.print("\tsweep_direction:\t");
              Serial.print(sweep_direction);
              Serial.print("\tDelay:\t");
              Serial.println(millis() - current_delay);
        #endif

        if(reading){ 
            move_forward();
        }else{
            move_back();
        }
        current_delay = millis();
    } 
};

#endif

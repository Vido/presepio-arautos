#ifndef STEPPER_CONTROLLER_H
#define STEPPER_CONTROLLER_H

#define PWM_FREQUENCY 50

#ifdef DEBUG
    #define STEPPER_DEBUG
#endif

#define ANTIHORARIO 0
#define HORARIO 1
#define DESLIGADO -1

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
    int initial_limit_pin;
    int final_limit_pin;
    //
    unsigned int enable_pin;
    unsigned int direction_pin;
    unsigned int spin_direction;
    unsigned int step_pin;
    unsigned int step_number;
    unsigned long expected_delay;
};

struct state_machine_parameters{

    // reset pin
    unsigned int input_pin;
    unsigned int reset_pin;
    unsigned int initial_limit_pin;
    unsigned int final_limit_pin;
    //
    unsigned int enable_pin;
    unsigned int direction_pin;
    unsigned int spin_direction;
    unsigned int step_pin;
    //
    unsigned int step_number1;
    unsigned int step_number2;
    unsigned int step_number3;
    unsigned int step_number4;
    //
    unsigned long expected_delay;
};

typedef struct stepper_parameters StepperParameters;
typedef struct state_machine_parameters StateMachineParameters;

/* ************************************************************* */

class StepperController{
    public:
        StepperController(StepperParameters parameters);
        StepperController(unsigned int input_pin,
                          int initial_limit_pin,
                          int final_limit_pin,
                          unsigned int enable_pin,
                          unsigned int direction_pin,
                          unsigned int spin_direction,
                          unsigned int step_pin,
                          unsigned int step_number,
                          unsigned long expected_delay);
        
        void next();
        //
        unsigned int input_pin;
        unsigned int enable_pin;
        unsigned int direction_pin;
        unsigned int spin_direction;
        unsigned int step_pin;
        unsigned int step_number;

        // Limit Swtich
        int initial_limit_pin;
        int final_limit_pin;

        //
        unsigned long expected_delay;
 
    private:
        void move_forward();
        void move_back();
        //
        long current_position;
        bool state_step_pin;
        unsigned long current_delay;
};

StepperController::StepperController(unsigned int input_pin,
                                     int initial_limit_pin,
                                     int final_limit_pin,
                                     unsigned int enable_pin,
                                     unsigned int direction_pin,
                                     unsigned int spin_direction,
                                     unsigned int step_pin,
                                     unsigned int step_number,
                                     unsigned long expected_delay){
    this->enable_pin = input_pin;
    this->initial_limit_pin = initial_limit_pin;
    this->final_limit_pin = final_limit_pin;
    //
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
    this->initial_limit_pin = parameters.initial_limit_pin;
    this->final_limit_pin = parameters.final_limit_pin;
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
    boolean initial_limit = true;
    if(abs(current_position) <= 0) end_stop = true;
    if(initial_limit_pin > 0) initial_limit = digitalRead(initial_limit_pin);
    
    if(!end_stop || !initial_limit){
        current_position--;
        digitalWrite(direction_pin, bool(!spin_direction));
        pulseOut(step_pin, 20);
    }
};

void StepperController::move_forward(){

    boolean end_stop = false;
    boolean final_limit = true;
    if(abs(current_position) >= step_number) end_stop = true;
    if(final_limit_pin > 0) final_limit = digitalRead(final_limit_pin);
    
    if(!end_stop || !final_limit){
        current_position++;
        digitalWrite(direction_pin, bool(spin_direction));
        pulseOut(step_pin, 20);
    }
};

void StepperController::next(){

    boolean reading = false;
    reading = digitalRead(input_pin);
    
    if ((millis() - current_delay) >  expected_delay){
       
          #ifndef STEPPER_DEBUG
              Serial.print("Reading:\t");
              Serial.print(reading);
              Serial.print("Step State:\t");
              Serial.print(state_step_pin);
              Serial.print("\tPosition:\t");
              Serial.print(current_position);
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

/* ************************************************************* */

class StateMachineStepperController{
    public:
        StateMachineStepperController(StateMachineParameters parameters);
        StateMachineStepperController(
                          unsigned int input_pin,
                          unsigned int reset_pin,
                          unsigned int initial_limit_pin,
                          unsigned int final_limit_pin,
                          unsigned int enable_pin,
                          unsigned int direction_pin,
                          unsigned int spin_direction1,
                          unsigned int spin_direction2,
                          unsigned int spin_direction3,
                          unsigned int spin_direction4,
                          unsigned int step_pin,
                          unsigned int step_number,
                          unsigned long expected_delay);

        void next_sm();
        //
        unsigned int input_pin;
        unsigned int reset_pin;

        unsigned int enable_pin;
        unsigned int direction_pin;
        unsigned int spin_direction;
        unsigned int step_pin;

        // SM Param
        unsigned int step_number1;
        unsigned int step_number2;
        unsigned int step_number3;
        unsigned int step_number4;

        // Limit Swtich
        unsigned int initial_limit_pin;
        unsigned int final_limit_pin;

        unsigned long expected_delay;

    private:
        void move_sm(unsigned int total_steps, unsigned char next_state, boolean reading);
        void move_forward();
        void move_back();
        //
        long current_position;
        bool state_step_pin;
        unsigned long current_delay;
        unsigned char state;
};

StateMachineStepperController::StateMachineStepperController(
                                     unsigned int input_pin,
                                     unsigned int reset_pin,
                                     unsigned int initial_limit_pin,
                                     unsigned int final_limit_pin,
                                     unsigned int enable_pin,
                                     unsigned int direction_pin,
                                     unsigned int spin_direction,
                                     unsigned int step_pin,
                                     unsigned int step_number1,
                                     unsigned int step_number2,
                                     unsigned int step_number3,
                                     unsigned int step_number4,
                                     unsigned long expected_delay){
    
    this->enable_pin = enable_pin;
    this->reset_pin = reset_pin;
    this->initial_limit_pin = initial_limit_pin;
    this->final_limit_pin = final_limit_pin;
    //
    this->enable_pin = enable_pin;
    this->direction_pin = direction_pin;
    this->step_pin = step_pin;
    //
    this->spin_direction = spin_direction;
    //
    this->step_number1 = step_number1;
    this->step_number1 = step_number2;
    this->step_number1 = step_number3;
    this->step_number1 = step_number4;

    this->expected_delay = expected_delay;
    //
    this->current_delay=millis();
    this->current_position = 0;
    this->state = 'i';
};

StateMachineStepperController::StateMachineStepperController(StateMachineParameters parameters){

    this->input_pin = parameters.input_pin;
    this->reset_pin = parameters.reset_pin;
    this->initial_limit_pin = parameters.initial_limit_pin;
    this->final_limit_pin = parameters.final_limit_pin;
    //
    this->enable_pin = parameters.enable_pin;
    this->direction_pin = parameters.direction_pin;
    this->step_pin = parameters.step_pin;
    //
    this->step_number1 = parameters.step_number1;
    this->step_number2 = parameters.step_number2;
    this->step_number3 = parameters.step_number3;
    this->step_number3 = parameters.step_number4;

    this->spin_direction = parameters.spin_direction;
    this->expected_delay = parameters.expected_delay;
    //
    this->current_delay=millis();
    this->current_position = 0;
    this->state = 'i';
};

void StateMachineStepperController::move_back(){

    boolean end_stop = false;
    if(abs(current_position) <= 0) end_stop = true;
    boolean initial_limit = false;
    initial_limit = digitalRead(initial_limit_pin);

    if(!end_stop || !initial_limit){
        current_position--;
        digitalWrite(direction_pin, bool(!spin_direction));
        pulseOut(step_pin, 20);
    }else{
      current_position = 0;
      state = 'i';
    }
};

void StateMachineStepperController::move_sm(unsigned int total_steps, unsigned char next_state, boolean reading){
    boolean end_stop = false;
    if(abs(current_position) >= total_steps) end_stop = true;
    boolean final_limit = false;
    final_limit = digitalRead(final_limit_pin);

    if(!end_stop || !final_limit){
        current_position++;
        digitalWrite(direction_pin, bool(spin_direction));
        pulseOut(step_pin, 20);
    }else if(reading){
        state = next_state;
    }
}

void StateMachineStepperController::next_sm(){

    boolean reading_move = false;
    boolean reading_reset = false;
    reading_move = digitalRead(input_pin);
    reading_reset = digitalRead(reset_pin);

    if ((millis() - current_delay) >  expected_delay){
        #ifdef STEPPER_DEBUG
              Serial.print("Reading Move:\t");
              Serial.print(reading_move);
              Serial.print("Reading Reset:\t");
              Serial.print(reading_reset);
              Serial.print("State:\t");
              Serial.print(state);
              Serial.print("\tPosition:\t");
              Serial.print(current_position);
              Serial.print("\tDelay:\t");
              Serial.println(millis() - current_delay);
        #endif
        //
        boolean end_stop = false;
        unsigned long step_number_b = step_number1+step_number2;
        unsigned long step_number_c = step_number_b+step_number3;
        unsigned long step_number_d = step_number_c+step_number4;
        //
        if(reading_reset){
            state = 'y';
        }

        switch(state){
            case 'i':
                if(reading_move) state = 'a';
                break;
            case 'a':
                move_sm(step_number1, 'b', reading_move);
                break;
            case 'b':
                move_sm(step_number_b, 'c', reading_move);
                break;
            case 'c':
                move_sm(step_number_c, 'd', reading_move);
                break;
            case 'f':
                move_sm(step_number_d, 'z', reading_move);
                break;
            case 'y':
                move_back();
                break;
        }
        current_delay = millis();
    }
};
#endif

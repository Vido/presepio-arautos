#ifndef STEPPER_CONTROLLER_H
#define STEPPER_CONTROLLER_H

#define PWM_FREQUENCY 50

#ifdef DEBUG
    //#define STEPPER_DEBUG
    #define STEPPER2_DEBUG
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
    int initial_limit_pin;
    int final_limit_pin;
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

struct romanos_parameters{
    unsigned int input_pin;
    unsigned int reset_pin;
    unsigned int step_number;
    unsigned long expected_delay;
};

typedef struct stepper_parameters StepperParameters;
typedef struct state_machine_parameters StateMachineParameters;
typedef struct romanos_parameters RomanosParameters;

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
        int move_forward();
        int move_back();
        int move_back_fim_curso();
        long set_position(long _position);

        /*
        Retornos:
        0: Motor livra para o proximo passo
        1: Fim de Curso
        2: Limite lógico do motor
        */
        
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

long StepperController::set_position(long _position){
    long p = this->current_position;
    this->current_position = _position;
    return p;
}

int StepperController::move_back(){

    boolean end_stop = false;
    boolean initial_limit = true;
    if(current_position <= 0) end_stop = true;
    if(initial_limit_pin > 0) initial_limit = digitalRead(initial_limit_pin);

    // Condicacao de Parada
    if(!initial_limit) return 1;
    if(end_stop) return 2;

    // Gira o motor para tras 1 passo
    current_position--;
    digitalWrite(direction_pin, bool(!spin_direction));
    pulseOut(step_pin, 20);
    return 0;
};

int StepperController::move_back_fim_curso(){

    boolean end_stop = false;
    boolean initial_limit = true;
    if(initial_limit_pin > 0) initial_limit = digitalRead(initial_limit_pin);

    // Fim de curso
    if(!initial_limit){
      this->current_position = 0;
      return 1;
    }

    // Gira o motor para tras 1 passo
    digitalWrite(direction_pin, bool(!spin_direction));
    pulseOut(step_pin, 20);
    return 0;
};


int StepperController::move_forward(){

    boolean end_stop = false;
    boolean final_limit = true;
    if(current_position >= step_number) end_stop = true;
    if(final_limit_pin > 0) final_limit = digitalRead(final_limit_pin);
    
    // Condicacao de Parada
    if(!final_limit) return 1;
    if(end_stop) return 2;
    
    // Gira o motor para frente 1 passo
    current_position++;
    digitalWrite(direction_pin, bool(spin_direction));
    pulseOut(step_pin, 20);
    return 0;
};

void StepperController::next(){

    boolean reading = false;
    reading = digitalRead(input_pin);
    
    if ((millis() - current_delay) >  expected_delay){
       
          #ifdef STEPPER_DEBUG
              Serial.print("Reading:\t");
              Serial.print(reading);
              Serial.print("\tStep State:\t");
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
        StateMachineStepperController();
        StateMachineStepperController(StateMachineParameters parameters);
        StateMachineStepperController(
                          unsigned int input_pin,
                          unsigned int reset_pin,
                          int initial_limit_pin,
                          int final_limit_pin,
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
        int initial_limit_pin;
        int final_limit_pin;

        unsigned long expected_delay;

    protected:
        void move_sm(unsigned int total_steps, unsigned char next_state, boolean reading);
        void move_forward();
        void move_back();
        void move_back_fim_curso();
        //
        long current_position;
        bool state_step_pin;
        unsigned long current_delay;
        unsigned char state;
};

/*
StateMachineStepperController::StateMachineStepperController(){
    //
    this->current_delay=millis();
    this->current_position = 0;
    this->state = 'i';
};
*/

StateMachineStepperController::StateMachineStepperController(
                                     unsigned int input_pin,
                                     unsigned int reset_pin,
                                     int initial_limit_pin,
                                     int final_limit_pin,
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
    this->step_number2 = step_number2;
    this->step_number3 = step_number3;
    this->step_number4 = step_number4;

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
    this->step_number4 = parameters.step_number4;

    this->spin_direction = parameters.spin_direction;
    this->expected_delay = parameters.expected_delay;
    //
    this->current_delay=millis();
    this->current_position = 0;
    this->state = 'i';
};

void StateMachineStepperController::move_back(){

    boolean end_stop = false;
    if(current_position <= 0) end_stop = true;
    //
    boolean initial_limit = true;
    if(initial_limit_pin > 0) initial_limit = digitalRead(initial_limit_pin);
    if(!initial_limit){
      //current_position = 0;
      state = 'i';
      return;
    }

    if(!end_stop){
        current_position--;
        digitalWrite(direction_pin, bool(!spin_direction));
        pulseOut(step_pin, 20);
    }else{
      //current_position = 0;
      state = 'i';
    }
};

void StateMachineStepperController::move_back_fim_curso(){
    //
    boolean initial_limit = true;
    if(initial_limit_pin > 0) initial_limit = digitalRead(initial_limit_pin);
    if(!initial_limit){
      current_position = 0;
      state = 'i';
      return;
    }
    digitalWrite(direction_pin, bool(!spin_direction));
    pulseOut(step_pin, 20);
};

void StateMachineStepperController::move_sm(unsigned int total_steps, unsigned char next_state, boolean reading){
  
    boolean end_stop = false;
    if(abs(current_position) >= total_steps) end_stop = true;
    //
    boolean final_limit = true;
    if(final_limit_pin > 0) final_limit = digitalRead(final_limit_pin);
    if(!final_limit){
      state = 'z';
      return;
    }

    if(!end_stop){
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
        #ifdef STEPPER2_DEBUG
              Serial.print("Reading Move:\t");
              Serial.print(reading_move);
              Serial.print("\tReading Reset:\t");
              Serial.print(reading_reset);
              Serial.print("\tState:\t");
              Serial.print(state);
              Serial.print("\tPosition:\t");
              Serial.print(current_position);
              if(initial_limit_pin > 0){
                Serial.print("\tinitial_limit_pin:\t");
                Serial.print(digitalRead(initial_limit_pin));
              }
              if(final_limit_pin > 0){
                Serial.print("\tfinal_limit_pin:\t");
                Serial.print(digitalRead(final_limit_pin));
              }
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
            case 'd':
                move_sm(step_number_d, 'z', reading_move);
                break;
            case 'y':
                move_back();
                break;
        }
        current_delay = millis();
    }
};

/* ************************************************************* */

class RomanosStateMachine{
    public:
        RomanosStateMachine(
          RomanosParameters* parameters,
          StepperController* left_parameters,
          StepperController* right_parameters);
        //
        void next_sm();
        unsigned int input_pin;
        unsigned int reset_pin;
        unsigned int step_number;
        unsigned long expected_delay;

    protected:
        //void move_sm(unsigned int total_steps, unsigned char next_state, boolean reading);
        //void move_forward();
        //void move_back();
        //void move_back_fim_curso();
        //
        long current_position;
        unsigned long current_delay;
        unsigned char state;
        StepperController* left_motor;
        StepperController* right_motor;       

};

RomanosStateMachine::RomanosStateMachine(RomanosParameters* parameters,
                                         StepperController* left_controller,
                                         StepperController* right_controller){

    this->input_pin = parameters->input_pin;
    this->reset_pin = parameters->reset_pin;
    this->step_number = parameters->step_number;
    this->expected_delay = parameters->expected_delay;
    //
    left_motor = left_controller;
    right_motor = right_controller;
    //
    this->current_delay=millis();
    this->current_position = 0;
    this->state = 'I';
};

void RomanosStateMachine::next_sm(){

    int left_signal = 0;
    int right_signal = 0;
    boolean reading_move = false;
    boolean reading_reset = false;
    reading_move = digitalRead(left_motor->input_pin) || digitalRead(right_motor->input_pin);
    reading_reset = digitalRead(reset_pin);

    if ((millis() - current_delay) >  expected_delay){
        //
        boolean end_stop = false;
        if(reading_reset) state = 'Y';
        
        switch(state){
            case 'I':
                if(reading_move) state = 'L';
                break;
            case 'L':
                if(reading_move){
                    left_signal = left_motor->move_forward();
                }
                if(left_signal==1) state = 'Z';
                if(left_signal==2){
                    state = 'R';
                    left_motor->set_position(0);
                }
                break;
            case 'R':
                if(reading_move){
                    right_signal = right_motor->move_forward();
                }
                if(right_signal==1) state = 'Z';
                if(right_signal==2){
                    state = 'L';
                    right_motor->set_position(0);
                }
                break;
            case 'Y':
                left_signal = left_motor->move_back_fim_curso();
                right_signal = right_motor->move_back_fim_curso();
                // Fim de curso, volta ao estado inicial
                if(right_signal==1 && right_signal==1) state = 'I';
                break;
        }
        current_delay = millis();
    }
};

#endif

#include <new.h>
#include <Servo.h>
#include "servo_controller.h"

#ifndef SERVO_CONFIG_H
#define SERVO_CONFIG_H


// 18 ORama
ServoParameters Casa1Porta = {
   34,      // servo_pin
   18,      // input_pin
   180,      // initial_position
   110,      // final_position
   25      // expected_delay
};


// 19 ORama
ServoParameters Casa2Porta = {
   35,      // servo_pin
   19,      // input_pin
   180,      // initial_position
   70,      // final_position
   10      // expected_delay
};

// 20 ORama
ServoParameters Casa3Porta = {
   36,      // servo_pin
   20,      // input_pin
   0,      // initial_position
   140,      // final_position
   10      // expected_delay
};


// 21 ORama
ServoParameters ReiOuro = {
   37,      // servo_pin
   21,      // input_pin
   120,      // initial_position
   0,       // final_position
   30       // expected_delay
};


// 22 ORama
ServoParameters ReiIncenso = {
   38,      // servo_pin
   22,      // input_pin
   160,      // initial_position
   30,     // final_position
   20       // expected_delay
};


// 23 ORama
ServoParameters ReiMirra = {
   39,      // servo_pin
   23,      // input_pin
   0,      // initial_position
   120,     // final_position
   30       // expected_delay
};



/*

// 21 ORama
ServoParameters NaSraAnunciacao = {
   37,      // servo_pin
   21,      // input_pin
   160,      // initial_position
   50,      // final_position
   30       // expected_delay
};


// 22 ORama
ServoParameters AnjoPastores = {
   35,      // servo_pin
   34,      // input_pin
   150,      // initial_position
   0,      // final_position
   20      // expected_delay
};

// 23 ORama
ServoParameters Pastor1 = {
   41,      // servo_pin
   40,      // input_pin
   0,      // initial_position
   120,     // final_position
   30       // expected_delay
};


// 24 ORama
ServoParameters Pastor2 = {
   43,      // servo_pin
   42,      // input_pin
   180,     // initial_position
   30,       // final_position
   30       // expected_delay
};




// 19 ORama
ServoParameters CabecaNSr = {
   45,      // servo_pin
   44,      // input_pin
   0,       // initial_position
   110,      // final_position
   60      // expected_delay
};















// 15 ORama
ServoParameters SV_EstrelaBelem = {
   15,      // servo_pin
   14,      // input_pin
   180,      // initial_position
   0,     // final_position
   90       // expected_delay
};

*/




ServoParameters *parameters_array[] = {
  //&AnjoPastores,
  &Casa1Porta,
  &Casa2Porta,
  &Casa3Porta,
  //&NaSraAnunciacao,
  &ReiOuro,
  &ReiIncenso,
  &ReiMirra,
  //&Pastor1,
  //&Pastor2,
  //&CabecaNSr,
  //&SV_EstrelaBelem,
};

#define SERVOS_NUMBER 6
ServoController *servo_array[SERVOS_NUMBER];

#endif



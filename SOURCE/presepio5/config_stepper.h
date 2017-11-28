/*
===========================================
 Parametros para a controlar servos.
 Codigo para o driver Chopper 5A da SerialLink 
 Autor: Lucas Vido ( vidov8@gmail.com )
===========================================

******* Ligacao Eletrica *******
Os drivers de motores de passo geralmente sao controlado com 3 sinais: STEP, CW/CCW e ENABLE.
Isto significa que ele depende tres saidas analogicas.

STEP   -> Avança um passo. Quando recebe um pulso quadro. 
CW/CCW -> Controla a direção do giro
ENABLE -> Ativa o motor em nível lógico

No casos nosso driver estes canais são indicados com as seguintes cores:

STEP   -> Fio Amarelo
CW/CCW -> Fio Laranja
ENABLE -> Fio Verde

STEP e CW/CCW devem ser controlado pelo Arduino
ENABLE pode ser ligado diretamento no 5V.

******* Parametros *******
Os parametros so incializados atravez da estrutura ServoParameters
Esta estrutura aceita os seguintes parametros, NESTA ORDEM:

* input_pin *
Endereco do pino digital do arduino que ira controlar o comportamento
do servo. Se o pino receber um sinal HIGH, o servo ira se mover
ate a sua posicao final (parametro final_position). Se o pino receber um
sinal LOW, ele ira se mover ate a sua posicao inicial (parametro initial_position)

Aceita qualquer numero que represente um pino no Arduino, inclusive A0, ... A5

* enable_pin *
Ativa o motor em nível lógico. Deve ser atribuido o valor de um pino do Arduino. 
Pode ser ligado diretamento no 5V, neste caso todos os canais de stepper
podem apontar para a mesma porta 

* direction_pin *
Controla a direção do giro. Deve ser atribuido o valor de um pino do Arduino.
Não é o parametro de configuração. É um porta de saída para o sinal do driver.

* spin_direction *
Parametro de configuração. Define qual é o sentido do giro do motor.
Controla a direção do giro. Deve ser atribuido o valor de um pino do Arduino.
Recebe os parametros: HORARIO ou ANTIHORARIO

* step_pin *
Quando recebe um pulso quadro, Avança um passo.
ão é o parametro de configuração. É um porta de saída para o sinal do driver.

* step_number *
Parametro de configuração. Define qual é o angulo que o motor irá girar.
O parametro pode receber um valor entre 0 e 400. O valor de 400 representa uma volta completa.

* expected_delay *
Intervalo entre a mudanca de posicao do passo. Basicamente esse parametro
controla a velocidade em que o servo se move. O parametro aceita um numero entre
1ms e 4294967295ms (apx 49 dias). Para um passo que vai de 0 grau para 180
graus, o valor que faz o servo percorrer o curso em 1s seria 5ms.
Devido a natureza concorrente do programa e o baixo clock do Arduino (16Mhz), nao e
possivel garantir que estes intervalos serao obedecidos em tempo real.
*/

#ifndef STEPPER_CONFIG_H
#define STEPPER_CONFIG_H

#include "stepper_controller.h"

// Nao mudar daqui para cima
/* ------------------------------------------------------------*/

StepperParameters stepper0 = {
    8,        // input_pin (Fio da LightORama)
    DESLIGADO,// initial_limit_pin (Sinal da chave-fim-de-curso NF, posição inicial) - Use numero do pino ou DESLIGADO
    DESLIGADO,// final_limit_pin (Sinal da chave-fim-de-curso NF, posição final) - Use numero do pino ou DESLIGADO
    10,       // enable_pin (Fio Verde, sempre ligado)
    9,        // direction_pin (Fio Laranja, controlado pelo firmware)
    HORARIO,  // spin_direction (HORARIO ou ANTIHORARIO)
    8,        // step_pin (Fio Amarelo, controlado pelo firmware)
    400,      // step_number (de 0 a 400)
    20        // expected_delay
};

StepperParameters stepper1 = {
    4,        // input_pin (Fio da LightORama)
    DESLIGADO,// initial_limit_pin (Sinal da chave-fim-de-curso NF, posição inicial) - Use numero do pino ou DESLIGADO
    DESLIGADO,// final_limit_pin (Sinal da chave-fim-de-curso NF, posição final) - Use numero do pino ou DESLIGADO
    14,       // enable_pin (Fio Verde, sempre ligado)
    15,       // direction_pin (Fio Laranja, controlado pelo firmware)
    HORARIO,  // spin_direction (HORARIO ou ANTIHORARIO)
    16,       // step_pin (Fio Amarelo, controlado pelo firmware)
    400,      // step_number (de 0 a 400)
    20        // expected_delay
};

// ESPECIAL PARA as 4 fases
StateMachineParameters stepper_special_params = {
    7,        // input_pin (Sinal da LightORama para andar pra frente)
    6,        // reset_pin (Reset - Sinal da LightORama para voltar para posição inicial)
    33,       // initial_limit_pin (Sinal da chave-fim-de-curso NF, posição inicial)
    34,       // final_limit_pin (Sinal da chave-fim-de-curso NF, posição final)
    23,       // enable_pin (Fio Verde, sempre ligado)
    24,       // direction_pin (Fio Laranja, controlado pelo firmware)
    HORARIO,  // spin_direction (HORARIO ou ANTIHORARIO)
    25,       // step_pin (Fio Amarelo, controlado pelo firmware)
    //
    400,     // step_number1
    400,     // step_number2
    400,     // step_number3
    400,     // step_number4
    //
    20       // expected_delay
};

// Nao mudar daqui para baixo
/* ------------------------------------------------------------*/

// Numero total de motores stepper
#define STEPPER_NUMBER 2

StepperParameters *param_stepper_array[] = {
    &stepper0,
    &stepper1,
};

StepperController *stepper_array[STEPPER_NUMBER];
StateMachineStepperController *special_stepper;

#endif

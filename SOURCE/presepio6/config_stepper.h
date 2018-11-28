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

// 13 lIGHT O RAMA
/*
StepperParameters AnjosGloria = {
    7,        // IN -- input_pin (Fio da LightORama)
    10,       // FIM DE CURSO INI -- initial_limit_pin (Sinal da chave-fim-de-curso NF, posição inicial) - Use numero do pino ou DESLIGADO
    12,       // FIM DE CURSO FIM -- final_limit_pin (Sinal da chave-fim-de-curso NF, posição final) - Use numero do pino ou DESLIGADO
    53,       // enable_pin (Fio Verde, sempre ligado) Deixar número 53
    8,        // DIR -- direction_pin (Fio Laranja, controlado pelo firmware)
    ANTIHORARIO,  // spin_direction (HORARIO ou ANTIHORARIO)
    9,        // PUL -- step_pin (Fio Amarelo, controlado pelo firmware)
    8500,    // step_number (de 0 a 400)
    2         // expected_delay
};
*/
StepperParameters ViaCrucis = {
    3,       // IN -- input_pin (Fio da LightORama)
    DESLIGADO,       // FIM DE CURSO INI -- initial_limit_pin (Sinal da chave-fim-de-curso NF, posição inicial) - Use numero do pino ou DESLIGADO
    DESLIGADO,       // FIM DE CURSO FIM -- final_limit_pin (Sinal da chave-fim-de-curso NF, posição final) - Use numero do pino ou DESLIGADO
    2,       // enable_pin (Fio Verde, sempre ligado) Deixar número 2
    4,        // DIR -- direction_pin (Fio Laranja, controlado pelo firmware)
    ANTIHORARIO,  // spin_direction (HORARIO ou ANTIHORARIO)
    5,        // PUL -- step_pin (Fio Amarelo, controlado pelo firmware)
    500,    // Um CM de fuso = 76,89655172
    2         // expected_delay
};

/*
StepperParameters EstrelaBelem = {
    14,        // IN -- input_pin (Fio da LightORama)
    DESLIGADO, // FIM DE CURSO INI -- initial_limit_pin (Sinal da chave-fim-de-curso NF, posição inicial) - Use numero do pino ou DESLIGADO
    DESLIGADO, // FIM DE CURSO FIM -- final_limit_pin (Sinal da chave-fim-de-curso NF, posição final) - Use numero do pino ou DESLIGADO
    53,        // enable_pin (Fio Verde, sempre ligado) Deixar número 53
    15,        // DIR -- direction_pin (Fio Laranja, controlado pelo firmware)
    HORARIO,   // spin_direction (HORARIO ou ANTIHORARIO)
    16,        // PUL -- step_pin (Fio Amarelo, controlado pelo firmware)
    100,        // step_number (de 0 a 400)
    50          // expected_delay
};
*/

StepperParameters SoldadosRomanosEsq = {
    DESLIGADO, // IN -- input_pin (Fio da LightORama)
    0,         // FIM DE CURSO INI -- initial_limit_pin (Sinal da chave-fim-de-curso NF, posição inicial) - Use numero do pino ou DESLIGADO
    0,         // FIM DE CURSO FIM -- final_limit_pin (Sinal da chave-fim-de-curso NF, posição final) - Use numero do pino ou DESLIGADO
    2,         // enable_pin (Fio Verde, sempre ligado) Deixar número 2
    10,        // DIR -- direction_pin (Fio Laranja, controlado pelo firmware)
    HORARIO,   // spin_direction (HORARIO ou ANTIHORARIO)
    11,        // PUL -- step_pin (Fio Amarelo, controlado pelo firmware)
    DESLIGADO  // step_number (de 0 a 400)
    DESLIGADO  // expected_delay
};

StepperParameters SoldadosRomanosDir = {
    DESLIGADO, // IN -- input_pin (Fio da LightORama)
    0,         // FIM DE CURSO INI -- initial_limit_pin (Sinal da chave-fim-de-curso NF, posição inicial) - Use numero do pino ou DESLIGADO
    0,         // FIM DE CURSO FIM -- final_limit_pin (Sinal da chave-fim-de-curso NF, posição final) - Use numero do pino ou DESLIGADO
    2,         // enable_pin (Fio Verde, sempre ligado) Deixar número 2
    10,        // DIR -- direction_pin (Fio Laranja, controlado pelo firmware)
    HORARIO,   // spin_direction (HORARIO ou ANTIHORARIO)
    11,        // PUL -- step_pin (Fio Amarelo, controlado pelo firmware)
    DESLIGADO, // step_number (de 0 a 400)
    DESLIGADO  // expected_delay
};

RomanosParameters romanos = {
    0, // IN -- input_pin (Fio da LightORama)
    17,       // reset_pin (Reset - Sinal da LightORama para voltar para posição inicial)
    400, // step_number;
    1    // expected_delay;
};

// ESPECIAL PARA as 2 fases

/*
Configurações do Driver:
- 
*/
StateMachineParameters stepper_special_params = {
    12,       // IN -- input_pin (Sinal da LightORama para andar pra frente)
    17,       // reset_pin (Reset - Sinal da LightORama para voltar para posição inicial)
    15,       // initial_limit_pin (Sinal da chave-fim-de-curso NF, posição inicial)
    16,       // final_limit_pin (Sinal da chave-fim-de-curso NF, posição final)
    2,        // enable_pin (Fio Verde, sempre ligado)
    13,       // DIR -- direction_pin (Fio Laranja, controlado pelo firmware)
    HORARIO,  // spin_direction (HORARIO ou ANTIHORARIO)
    14,       // PUL -- step_pin (Fio Amarelo, controlado pelo firmware)
    //
    2141,     // step_number1 883
    2587,     // step_number2
    5084,     // step_number3
    5174,     // step_number4
    //
    2       // expected_delay
};

// Nao mudar daqui para baixo
/* ------------------------------------------------------------*/

// Numero total de motores stepper
#define STEPPER_NUMBER 1

StepperParameters *param_stepper_array[] = {
    // Soldados romanos devem ser os 2 primeiros items da lista
    &SoldadosRomanosDir,
    &SoldadosRomanosEsq,
    &ViaCrucis,
    //&AnjosGloria,
    //&EstrelaBelem,
};

StepperController *stepper_array[STEPPER_NUMBER];
StateMachineStepperController *special_stepper;
RomanosStateMachine *soldados_romanos;

#endif

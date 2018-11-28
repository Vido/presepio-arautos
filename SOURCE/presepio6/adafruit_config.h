/*
===========================================
 Parametros para a controlar servos.
 Codigo para o driver PCA9685 da Adafruit
 Autor: Lucas Vido ( vidov8@gmail.com )
===========================================

******* Ligacao Eletrica *******
O driver PCA9685 e um dispositivo I2C. Isto significa que ele depende dos
sinais SDA e SCL para funcionar. O Arduino possue estes sinais, porem
eles no esto indicados na placa. E necessario consultar os manuais do
Arduino para conhecer a localizacao destes pinos.

Arduino UNO:
* SDA fica no pino A4
* SCL fica no pino A5

Arduino Mega:
Os pinos I2C nao estao marcados!
Eles ficam no header PWM, sao os pinos da extremidade.
* SCL pina mais na extremindade
* SDA pino vizinho do pino AREF

******* Parametros *******
Os parametros so incializados atravez da estrutura AdafruitParameters
Esta estrutura aceita os seguintes parametros, NESTA ORDEM:

* servo_address *
Local do servo no shield. Aceita uma numero inteiro entre 0 e 15

* input_pin *
Endereco do pino digital do arduino que ira controlar o comportamento
do servo. Se o pino receber um sinal HIGH, o servo ira se mover
ate a sua posicao final (parametro final_position). Se o pino receber um
sinal LOW, ele ira se mover ate a sua posicao inicial (parametro initial_position)

Aceita qualquer numero que represente um pino no Arduino, inclusive A0, ... A5

* min_12bits_pwm *
Largura do pulso que representa o fim de curso do servo. Este parametro
aceita um inteiro entre 0 e 4095. Onde 0 representa um pulso de largura zero,
e 4095 representa um pulso de largura igual ao periodo.

Para controlar um servo a largura do pulso minimo e de 0.5ms, e a largura entre
dois pulsos deve ser de 20ms.
Este software trabalha com uma frequencia de 50Hz, para atender um periodo
de 20ms. Dado uma frequencia de 50Hz, o pulso minimo tem seu duty cycle de 2.5%.
Portanto, teoricamente, o valor ideal min_12bits_pwm seria 103. Porem ele pode
variar de servo para servo.

CUIDADO! : Valores muito baixos, podem danificar o Servo.

* max_12bits_pwm *
Largura do pulso que representa o fim de curso do servo. Este parametro
aceita um inteiro entre 0 e 4095. Onde 0 representa um pulso de largura zero,
e 4095 representa um pulso de largura igual ao periodo.

Para controlar um servo a largura do pulso maximo e de 2.5ms, e a largura entre
dois pulsos deve ser de 20ms.
Este software trabalha com uma frequencia de 50Hz para atender um periodo
de 20ms. Dado uma frequencia de 50Hz, o pulso maximo tem seu duty cycle de 12.5%.
Portanto, teoricamente, o valor ideal max_12bits_pwm seria 512. Porem ele pode
variar de servo para servo.

CUIDADO! : Valores muito altos, podem danificar o Servo.

* initial_position *
Posicao inicial do servo. Este parametro recebe um inteiro entre 0 e 180 graus.
Ao iniciar o programa, o servo se move para esta posicao.
O valor da posicao inicial pode ser maior que a final. Neste caso o servo
ira se mover no sentido antihorario.

* final_position *
Posicao final do servo. Este parametro recebe um inteiro entre 0 e 180 graus.

* expected_delay *
Intervalo entre a mudanca de posicao do servo. Basicamente esse parametro
controla a velocidade em que o servo se move. O parametro aceita um numero entre
1ms e 4294967295ms (apx 49 dias). Para um servo que vai de 0 grau para 180
graus, o valor que faz o servo percorrer o curso em 1s seria 5ms.
Devido a natureza concorrente do programa e o baixo clock do Arduino (16Mhz), nao e
possivel garantir que estes intervalos serao obedecidos em tempo real.
*/

#ifndef ADAFRUIT_CONFIG_H
#define ADAFRUIT_CONFIG_H

#include "adafruit_controller.h"

// Nao mudar daqui para cima
/* ------------------------------------------------------------*/
/*
AdafruitParameters servo0 = {
    0,         // servo_address (nao mudar !!!)
    22,      // input_pin
    110,   // min_12bits_pwm (Cuidado !!!)
    510,   // max_12bits_pwm (Cuidado !!!)
    180,  // initial_position
    0,      // final_position
    30      // expected_delay
};

AdafruitParameters servo1 = {
    1,         // servo_address (nao mudar !!!)
    23,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm  (Cuidado !!!)
    0,        // initial_position
    180,   // final_position
    30      // expected_delay
};

AdafruitParameters servo2 = {
    2,         // servo_address (nao mudar !!!)
    24,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm  (Cuidado !!!)
    0,        // initial_position
    100,   // final_position
    30      // expected_delay
};

AdafruitParameters servo3 = {
    3,         // servo_address (nao mudar !!!)
    25,      // input_pin
    110,   // min_12bits_pwm   (Cuidado !!!)
    510,   // max_12bits_pwm  (Cuidado !!!)
    0,        // initial_position
    100,   // final_position
    30      // expected_delay
};

AdafruitParameters servo4 = {
    4,         // servo_address (nao mudar !!!)
    26,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm  (Cuidado !!!)
    180,   // initial_position
    30,       // final_position
    30      // expected_delay
};

AdafruitParameters servo5 = {
    5,         // servo_address (nao mudar !!!)
    27,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm  (Cuidado !!!)
    150,        // initial_position
    30,   // final_position
    20      // expected_delay
};

AdafruitParameters servo6 = {
    6,         // servo_address (nao mudar !!!)
    28,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm  (Cuidado !!!)
    180,        // initial_position
    30,   // final_position
    30      // expected_delay
};

AdafruitParameters servo7 = {
    7,         // servo_address (nao mudar !!!)
    29,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm  (Cuidado !!!)
    0,        // initial_position
    110,   // final_position
    30      // expected_delay
};

AdafruitParameters servo8 = {
    8,         // servo_address (nao mudar !!!)
    30,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm  (Cuidado !!!)
    0,        // initial_position
    180,   // final_position
    10      // expected_delay
};

AdafruitParameters servo9 = {
    9,         // servo_address (nao mudar !!!)
    30,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm (Cuidado !!!)
    0,        // initial_position
    180,   // final_position
    10      // expected_delay
};

AdafruitParameters servo10 = {
    10,      // servo_address (nao mudar !!!)
    30,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm (Cuidado !!!)
    0,        // initial_position
    180,   // final_position
    10      // expected_delay
};

AdafruitParameters servo11 = {
    11,      // servo_address (nao mudar !!!)
    30,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm (Cuidado !!!)
    0,        // initial_position
    180,   // final_position
    10      // expected_delay
};

AdafruitParameters servo12 = {
    12,      // servo_address (nao mudar !!!)
    30,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm (Cuidado !!!)
    0,        // initial_position
    180,   // final_position
    10      // expected_delay
};

AdafruitParameters servo13 = {
    13,       // servo_address (nao mudar !!!)
    30,       // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm (Cuidado !!!)
    0,        // initial_position
    180,   // final_position
    10      // expected_delay
};

AdafruitParameters servo14 = {
    14,      // servo_address (nao mudar !!!)
    30,      // input_pin
    110,   // min_12bits_pwm  (Cuidado !!!)
    510,   // max_12bits_pwm (Cuidado !!!)
    0,        // initial_position
    180,   // final_position
    10      // expected_delay
};

AdafruitParameters servo15 = {
    15,       // servo_address (nao mudar !!!)
    30,       // input_pin
    110,    // min_12bits_pwm  (Cuidado !!!)
    510,    // max_12bits_pwm (Cuidado !!!)
    0,        // initial_position
    180,   // final_position
    10      // expected_delay
};
*/
// Nao mudar daqui para baixo
/* ------------------------------------------------------------*/

AdafruitParameters *param_adafruit_array[] = {
    //&servo0,
    //&servo1,
    //&servo2,
    //&servo3,
    //&servo4,
    //&servo5,
    //&servo6,
    //&servo7,
    //&servo8,
    //&servo9,
    //&servo10,
    //&servo11,
    //&servo12,
    //&servo13,
    //&servo14,
    //&servo15,
};

// Numero total de enderecos de servo
#define ADAFRUIT_CHANNELS_NUMBER 0
AdafruitController *adafruit_array[ADAFRUIT_CHANNELS_NUMBER];

#endif

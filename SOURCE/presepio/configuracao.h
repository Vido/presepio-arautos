/*
 Parametros para a controlar servos.
 Autor: Lucas Vido ( vido@usp.br || vidov8@gmail.com )
*/

// Define a posicao inicial dos servos
// Min 0 graus -  Max 180 graus
// O valor da posicao inicial pode ser maior que a final (antihorario)
#define POS_INICIAL_2 150
#define POS_INICIAL_3 0 
#define POS_INICIAL_4 0 
#define POS_INICIAL_5 0
#define POS_INICIAL_6 0 
#define POS_INICIAL_7 0 
#define POS_INICIAL_8 0 
#define POS_INICIAL_9 0
#define POS_INICIAL_10 0 
#define POS_INICIAL_11 0 
#define POS_INICIAL_12 0 
#define POS_INICIAL_13 0

// Define a posicao final dos servos
// Min 0 graus - Max 180 graus
// O valor da posicao inicial pode ser maior que a final (antihorario)
#define POS_FINAL_2 40
#define POS_FINAL_3 180 
#define POS_FINAL_4 180 
#define POS_FINAL_5 180
#define POS_FINAL_6 180 
#define POS_FINAL_7 180 
#define POS_FINAL_8 180 
#define POS_FINAL_9 180
#define POS_FINAL_10 180 
#define POS_FINAL_11 180 
#define POS_FINAL_12 180 
#define POS_FINAL_13 180

// Velocidade e um intervalo de tempo, logo
// quanto maior o valor, mais lento o movimento.
// Min 0 ms representa a maxima velocidade
// O valor minimo recomendado e 1 ms
// Nao o valor maximo e 64000 ms
#define VELOCIDADE 15

// Exemplo:
// SINAL_ENTRADA_2 representa o servo no pino 2
// SINAL_ENTRADA_2 22 diz que o sinal de entrada que aciona o servo2
// vem do pino 22
// A numeracao nao precisa obedecer uma sequencia
#define SINAL_ENTRADA_2 22
#define SINAL_ENTRADA_3 23
#define SINAL_ENTRADA_4 24
#define SINAL_ENTRADA_5 25
#define SINAL_ENTRADA_6 26
#define SINAL_ENTRADA_7 27
#define SINAL_ENTRADA_8 28
#define SINAL_ENTRADA_9 29
#define SINAL_ENTRADA_10 30
#define SINAL_ENTRADA_11 31
#define SINAL_ENTRADA_12 32
#define SINAL_ENTRADA_13 33

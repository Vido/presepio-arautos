#include <Servo.h>
#include "configuracao.h"

Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
Servo Servo6;
Servo Servo7;
Servo Servo8;
Servo Servo9;
Servo Servo10;
Servo Servo11;
Servo Servo12;
Servo Servo13;

Servo *servo_map[] = {
  &Servo2,
  &Servo3,
  &Servo4,
  &Servo5,
  &Servo6,
  &Servo7,
  &Servo8,
  &Servo9,
  &Servo10,
  &Servo11,
  &Servo12,
  &Servo13
};

int pos_inicial_map[] = {
  POS_INICIAL_2, 
  POS_INICIAL_3, 
  POS_INICIAL_4, 
  POS_INICIAL_5,
  POS_INICIAL_6, 
  POS_INICIAL_7, 
  POS_INICIAL_8, 
  POS_INICIAL_9,
  POS_INICIAL_10, 
  POS_INICIAL_11, 
  POS_INICIAL_12, 
  POS_INICIAL_13
};

int pos_map[] = {
  POS_INICIAL_2, 
  POS_INICIAL_3, 
  POS_INICIAL_4, 
  POS_INICIAL_5,
  POS_INICIAL_6, 
  POS_INICIAL_7, 
  POS_INICIAL_8, 
  POS_INICIAL_9,
  POS_INICIAL_10, 
  POS_INICIAL_11, 
  POS_INICIAL_12, 
  POS_INICIAL_13
};

int pos_final_map[] = {
  POS_FINAL_2, 
  POS_FINAL_3, 
  POS_FINAL_4, 
  POS_FINAL_5,
  POS_FINAL_6, 
  POS_FINAL_7, 
  POS_FINAL_8, 
  POS_FINAL_9,
  POS_FINAL_10, 
  POS_FINAL_11, 
  POS_FINAL_12, 
  POS_FINAL_13
};

int sinal_entrada_map[] = {
  SINAL_ENTRADA_2,
  SINAL_ENTRADA_3,
  SINAL_ENTRADA_4,
  SINAL_ENTRADA_5,
  SINAL_ENTRADA_6,
  SINAL_ENTRADA_7,
  SINAL_ENTRADA_8,
  SINAL_ENTRADA_9,
  SINAL_ENTRADA_10,
  SINAL_ENTRADA_11,
  SINAL_ENTRADA_12,
  SINAL_ENTRADA_13,
};

void setup() {
  
  //Serial.begin(9600);
  
  Servo2.attach(2); 
  Servo3.attach(3); 
  Servo4.attach(4); 
  Servo5.attach(5);
  Servo6.attach(6); 
  Servo7.attach(7); 
  Servo8.attach(8); 
  Servo9.attach(9);
  Servo10.attach(10); 
  Servo11.attach(11); 
  Servo12.attach(12); 
  Servo13.attach(13);

  Servo2.write(POS_INICIAL_2);  // 0
  Servo3.write(POS_INICIAL_3);  // 1
  Servo4.write(POS_INICIAL_4);  // 2 
  Servo5.write(POS_INICIAL_5);  // 3
  Servo6.write(POS_INICIAL_6);  // 4 
  Servo7.write(POS_INICIAL_7);  // 5 
  Servo8.write(POS_INICIAL_8);  // 6 
  Servo9.write(POS_INICIAL_9);  // 7
  Servo10.write(POS_INICIAL_10);  // 8
  Servo11.write(POS_INICIAL_11);  // 9
  Servo12.write(POS_INICIAL_12);  // 10
  Servo13.write(POS_INICIAL_13);  // 11
}

void loop(){
  for(int i=0; i<12; i++){
    int reading = digitalRead(sinal_entrada_map[i]);
    if (reading==HIGH){
      if(pos_inicial_map[i] < pos_final_map[i]){
        if(pos_map[i] != pos_final_map[i]){
          pos_map[i]++;
          servo_map[i]->write(pos_map[i]);
        }
      }else{ // pos_inicial_map[i] > pos_final_map[i]
        if(pos_map[i] > pos_final_map[i]){
          pos_map[i]--;
          servo_map[i]->write(pos_map[i]); 
         }
      }
    }else{ // LOW
      if(pos_inicial_map[i] < pos_final_map[i]){
        if(pos_map[i] > pos_inicial_map[i]){
          pos_map[i]--;
          servo_map[i]->write(pos_map[i]); 
        }
      }else{ // pos_inicial_map[i] > pos_final_map[i]
        if(pos_map[i] < pos_inicial_map[i]){
          pos_map[i]++;
          servo_map[i]->write(pos_map[i]); 
         }
      }
    }
  }
  delay(VELOCIDADE);
}

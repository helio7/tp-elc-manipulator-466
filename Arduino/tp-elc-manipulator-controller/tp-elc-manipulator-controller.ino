// This program controls the TP-ELC Manipulator designed by Degem Systems.
// Link to the project: https://github.com/helio7/tp-elc-manipulator-466

#include <SoftwareSerial.h>

const int RX_bt = 10;
const int TX_bt = 11;
int pin1 = 53;
int pin3 = 51;
int pin5 = 49;
int pin7 = 47;
int pin9 = 45;
int pin11 = 43;
int pin13 = 41;
int pin15 = 39;
int pin17 = 37;
int pin26 = 28;
int pin27 = 27;
int pin30 = 24;

// analogRead(A0); returns a position value between 0 and 1023. That value change when the machine rotates.
// The value decreases as the machine rotates toward the valves ("into" the machine itself).
// The value increases as the machine rotates in the opposite direction ("outside" the machine).

// If you don't specify limits, the user could rotate the manipulator too much, and maybe break it.
// So there are 2 variables to control these limits. If the position returned by analogRead(0) isn't between
// these values, the machine won't rotate in a respective direction.

// At the first time, you can try with max_rot_pos as the maximum possible (1023) and min_rot_pos as the minimum
// possible (1). That way, the device will rotate without restrictions.

// Theorically the exact values are max_rot_pos = 346 and min_rot_pos = 90.
// However, the values you need may vary depending on the cables you use to connect the A0 and J6 ports. Their
// resistance affects these values. Anyways, find the pair you need.
// For example, [max = 410 and min = 125] worked for me.

int max_rot_pos = 1023;
int min_rot_pos = 1;

String opcion_elegida = "0";
int valor_recibido = 0;
SoftwareSerial BT(RX_bt,TX_bt);
int ciclos_orden = 0;

void setup(){
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(pin1, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin11, OUTPUT);
  pinMode(pin13, OUTPUT);
  pinMode(pin15, OUTPUT);
  pinMode(pin17, OUTPUT);
  pinMode(pin26, OUTPUT);
  pinMode(pin27, OUTPUT);
  pinMode(pin30, OUTPUT);
  digitalWrite(pin1, 1);
  digitalWrite(pin3, 1);
  digitalWrite(pin5, 1);
  digitalWrite(pin7, 1);
  digitalWrite(pin9, 1);
  digitalWrite(pin11, 1);
  digitalWrite(pin13, 1);
  digitalWrite(pin15, 1);
  digitalWrite(pin17, 1);
  digitalWrite(pin26, 1);
  digitalWrite(pin27, 1);
  digitalWrite(pin30, 1);
}

String LeerOrdenRecibida(){
  String S = "" ;
  char c = BT.read();
  while (c != '\n')
    {
      S = S + c;
      delay(25);
      c = BT.read();
    }
  return(S);
}

void PreOrden(){
  digitalWrite(pin3, 0);
  delay(1);
  digitalWrite(pin5, 0);
  delay(1);
  digitalWrite(pin7, 0);
  delay(1);
  digitalWrite(pin9, 0);
  delay(1);
  digitalWrite(pin11, 0);
  delay(1);
  digitalWrite(pin13, 0);
  delay(1);
  digitalWrite(pin30, 0);
  delay(1);

  digitalWrite(pin1, 0);
  delay(1);
}

void Orden_Avance(){
  PreOrden();

  digitalWrite(pin11, 1);
  delay(1);
  digitalWrite(pin15, 0);
  delay(1);
  digitalWrite(pin17, 0);
  delay(1);
  digitalWrite(pin26, 0);
  delay(1);

  digitalWrite(pin27, 0);
  delay(1);

  digitalWrite(pin11, 0);
  delay(1);
  digitalWrite(pin13, 1);
  delay(1);
  digitalWrite(pin15, 1);
  delay(1);
  digitalWrite(pin17, 1);
  delay(1);

  digitalWrite(pin1, 1);
  delay(1);
}

void Orden_Retroceso(){
  PreOrden();

  digitalWrite(pin9, 1);
  delay(1);
  digitalWrite(pin11, 1);
  delay(1);
  digitalWrite(pin15, 0);
  delay(1);
  digitalWrite(pin17, 0);
  delay(1);
  digitalWrite(pin26, 0);
  delay(1);

  digitalWrite(pin27, 0);
  delay(1);

  digitalWrite(pin9, 0);
  delay(1);
  digitalWrite(pin11, 0);
  delay(1);
  digitalWrite(pin13, 1);
  delay(1);
  digitalWrite(pin15, 1);
  delay(1);
  digitalWrite(pin17, 1);
  delay(1);

  digitalWrite(pin1, 1);
  delay(1);
}

void Orden_Giro_neg(){
  PreOrden();

  digitalWrite(pin26, 0);
  delay(1);

  digitalWrite(pin27, 0);
  delay(1);
  
  digitalWrite(pin13, 1);
  delay(1);
  digitalWrite(pin15, 1);
  delay(1);
  digitalWrite(pin17, 1);
  delay(1);

  digitalWrite(pin1, 1);
  delay(1);
}

void Orden_Giro_pos(){
  PreOrden();

  digitalWrite(pin13, 1);
  delay(1);
  digitalWrite(pin15, 0);
  delay(1);
  digitalWrite(pin26, 0);
  delay(1);

  digitalWrite(pin27, 0);
  delay(1);
  
  digitalWrite(pin15, 1);
  delay(1);

  digitalWrite(pin1, 1);
  delay(1);
}

void Orden_Zaxis_valve(){
  PreOrden();

  digitalWrite(pin5, 1);
  delay(1);
  digitalWrite(pin15, 0);
  delay(1);
  digitalWrite(pin17, 0);
  delay(1);
  digitalWrite(pin26, 0);
  delay(1);

  digitalWrite(pin27, 0);
  delay(1);

  digitalWrite(pin5, 0);
  delay(1);
  digitalWrite(pin13, 1);
  delay(1);
  digitalWrite(pin15, 1);
  delay(1);
  digitalWrite(pin17, 1);
  delay(1);

  digitalWrite(pin1, 1);
  delay(1);
}

void Orden_Vacuum_valve(){
  PreOrden();

  digitalWrite(pin3, 1);
  delay(1);
  digitalWrite(pin15, 0);
  delay(1);
  digitalWrite(pin17, 0);
  delay(1);
  digitalWrite(pin26, 0);
  delay(1);

  digitalWrite(pin27, 0);
  delay(1);

  digitalWrite(pin3, 0);
  delay(1);
  digitalWrite(pin13, 1);
  delay(1);
  digitalWrite(pin15, 1);
  delay(1);
  digitalWrite(pin17, 1);
  delay(1);

  digitalWrite(pin1, 1);
  delay(1);
}

void Orden_Desactivar_todo(){
  PreOrden();

  digitalWrite(pin15, 0);
  delay(1);
  digitalWrite(pin17, 0);
  delay(1);
  digitalWrite(pin26, 0);
  delay(1);

  digitalWrite(pin27, 0);
  delay(1);

  digitalWrite(pin13, 1);
  delay(1);
  digitalWrite(pin15, 1);
  delay(1);
  digitalWrite(pin17, 1);
  delay(1);

  digitalWrite(pin1, 1);
  delay(1);
}



void Ciclo_10hz(){
  digitalWrite(pin3, 1);
  digitalWrite(pin5, 1);
  digitalWrite(pin7, 1);
  delay(50);
  digitalWrite(pin3, 0);
  digitalWrite(pin5, 0);
  digitalWrite(pin7, 0);
  delay(50);
}

void ResetPins(){
  digitalWrite(pin1, 1);
  digitalWrite(pin3, 1);
  digitalWrite(pin5, 1);
  digitalWrite(pin7, 1);
  digitalWrite(pin9, 1);
  digitalWrite(pin11, 1);
  digitalWrite(pin13, 1);
  digitalWrite(pin15, 1);
  digitalWrite(pin17, 1);
  digitalWrite(pin26, 1);
  digitalWrite(pin27, 1);
  digitalWrite(pin30, 1);
}

//96 y 355

void loop(){
  if(BT.available()){
    opcion_elegida = LeerOrdenRecibida();
    valor_recibido = opcion_elegida.toInt();
    int posicion_giro = analogRead(A0);
    
    if (valor_recibido == 1){
      Orden_Avance();
      
      while(!BT.available()){
        Ciclo_10hz();
        ciclos_orden = ciclos_orden + 1;
        if (ciclos_orden == 50){

          ResetPins();
          Orden_Desactivar_todo();
          ResetPins();
          Orden_Avance();
          ciclos_orden = 0;
        }
      }
      
      opcion_elegida = LeerOrdenRecibida();
      ResetPins();
      Orden_Desactivar_todo();
      ResetPins();
    }

    if (valor_recibido == 2){
      Orden_Retroceso();
      
      while(!BT.available()){
        Ciclo_10hz();
        ciclos_orden = ciclos_orden + 1;
        if (ciclos_orden == 50){
          ResetPins();
          Orden_Desactivar_todo();
          ResetPins();
          Orden_Retroceso();
          ciclos_orden = 0;
        }
      }
      
      opcion_elegida = LeerOrdenRecibida();
      ResetPins();
      Orden_Desactivar_todo();
      ResetPins();
    }

    if (valor_recibido == 3 and analogRead(A0) < max_rot_pos){ //435
      Orden_Giro_neg();
      
      while(!BT.available()and analogRead(A0) < max_rot_pos){
        Ciclo_10hz();
        ciclos_orden = ciclos_orden + 1;
        if (ciclos_orden == 50){
          ResetPins();
          Orden_Desactivar_todo();
          ResetPins();
          Orden_Giro_neg();
          ciclos_orden = 0;
        }
      }

      if(BT.available()){
        opcion_elegida = LeerOrdenRecibida();
      }
      ResetPins();
      Orden_Desactivar_todo();
      ResetPins();
    }

    if (valor_recibido == 4 and analogRead(A0) > min_rot_pos){ //125
      Orden_Giro_pos();
      
      while(!BT.available() and analogRead(A0) > min_rot_pos){
        Ciclo_10hz();
        ciclos_orden = ciclos_orden + 1;
        if (ciclos_orden == 50){
          ResetPins();
          Orden_Desactivar_todo();
          ResetPins();
          Orden_Giro_pos();
          ciclos_orden = 0;
        }
      }
      
      if(BT.available()){
        opcion_elegida = LeerOrdenRecibida();
      }
      ResetPins();
      Orden_Desactivar_todo();
      ResetPins();
    }

    if (valor_recibido == 5){
      Orden_Zaxis_valve();
      
      while(!BT.available()){
        Ciclo_10hz();
        ciclos_orden = ciclos_orden + 1;
        if (ciclos_orden == 50){
          ResetPins();
          Orden_Desactivar_todo();
          ResetPins();
          Orden_Zaxis_valve();
          ciclos_orden = 0;
        }
      }
      
      opcion_elegida = LeerOrdenRecibida();
      ResetPins();
      Orden_Desactivar_todo();
      ResetPins();
    }

    if (valor_recibido == 6){
      Orden_Vacuum_valve();
      
      while(!BT.available()){
        Ciclo_10hz();
        ciclos_orden = ciclos_orden + 1;
        if (ciclos_orden == 50){
          ResetPins();
          Orden_Desactivar_todo();
          ResetPins();
          Orden_Vacuum_valve();
          ciclos_orden = 0;
        }
      }
      
      opcion_elegida = LeerOrdenRecibida();
      ResetPins();
      Orden_Desactivar_todo();
      ResetPins();
    }
   
  }
}


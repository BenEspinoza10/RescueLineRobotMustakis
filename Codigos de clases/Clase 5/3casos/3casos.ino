#include "Pines.h"
//Librería para el sensor IR
#include <QTRSensors.h>

const int freq = 5000;
const int resolution = 8;

//Se crea el objeto del qtr
QTRSensors qtr;

//Se crea el arreglo para almacenar las lectura
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

//Se definen umbrales para cada sensor (valores arbitrarios, en la practica se debe ajustar)
int umbrales[SensorCount] = {3000,3000,3000,3000,3000,3000,3000,3000};


void setup() {
  inicializarMotores();
  inicializarSensores();
  //La funcion calibrar sensores espera a que se apriete el botón para iniciar
  //Mientras se hace el proceso de calibración se encenderá el LED de la esp32
  //Cuando finalice la calibración, se espera a que se vuelva apretar el botón para iniciar el programa
  calibrarSensores();
}

void loop() {
  //Se actualiza la lectura del sensor
  qtr.read(sensorValues);
  if (es_interseccion()){
    Motor(0,0);
    delay(500);
    Motor(-150,150);
    delay(500);
  }else if(es_gap()){
    Motor(50,50); //avanzar en linea recta lento
  }else if(giro_90_izq()){
    Motor(0,0);
    delay(500);
    Motor(0,150);
    delay(500);
  }else if(giro_90_der()){
    Motor(0,0);
    delay(500);
    Motor(150,0);
    delay(500);
  }else{
    siguelineas();
  }
}

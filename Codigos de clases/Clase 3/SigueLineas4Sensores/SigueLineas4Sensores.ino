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
  while (digitalRead(BOTON) == 0) {
  }
}

void loop() {
  //Se actualiza la lectura del sensor
  qtr.read(sensorValues);
  //Se hace un siguelíneas simple con máquina de estados
  //B,B,B,B
  if (sensorValues[2] < umbrales[2] and sensorValues[3] < umbrales[3] and sensorValues[4] < umbrales[4] and sensorValues[5] < umbrales[5]){
    Motor(0,0);
  //B,N,N,B
  } else if (sensorValues[2] < umbrales[2] and sensorValues[3] >= umbrales[3] and sensorValues[4] >= umbrales[4] and sensorValues[5] < umbrales[5]){
    Motor(50,50);
  //N,N,B,B
  } else if (sensorValues[2] >= umbrales[2] and sensorValues[3] >= umbrales[3] and sensorValues[4] < umbrales[4] and sensorValues[5] < umbrales[5]){
    Motor(50,100);
  //B,B,N,N
  } else if (sensorValues[2] < umbrales[2] and sensorValues[3] < umbrales[3] and sensorValues[4] >= umbrales[4] and sensorValues[5] >= umbrales[5]){
    Motor(100,50);
  }
}

#include "Pines.h"
#include <QTRSensors.h>

const int freq = 5000;
const int resolution = 8;

QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

int umbrales[SensorCount] = { 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000 };


void setup() {
  inicializarMotores();
  inicializarSensores();
  while (digitalRead(BOTON) == 0) {
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  //B,B,B,B,B,B - (0,0)
  //N,N,B,B,B,B - (100,0)
  //B,N,N,B,B,B - (75,25)
  //B,B,N,N,B,B - (50,50)
  //B,B,B,N,N,B - (25,75)
  //B,B,B,B,N,N - (0,100)
  //N,N,N,N,N,N - (75,75)

  qtr.read(sensorValues);
  //B,B,B,B,B,B
  if (sensorValues[1] < umbrales[1] and sensorValues[2] < umbrales[2] and sensorValues[3] < umbrales[3] and sensorValues[4] < umbrales[4] and sensorValues[5] < umbrales[5] and sensorValues[6] < umbrales[6]) {
    Motor(0, 0);


    //N,N,B,B,B,B
  } else if (sensorValues[1] >= umbrales[1] and sensorValues[2] >= umbrales[2] and sensorValues[3] < umbrales[3] and sensorValues[4] < umbrales[4] and sensorValues[5] < umbrales[5] and sensorValues[6] < umbrales[6]) {
    Motor(0, 100);


    //B,N,N,B,B,B
  } else if (sensorValues[1] < umbrales[1] and sensorValues[2] >= umbrales[2] and sensorValues[3] >= umbrales[3] and sensorValues[4] < umbrales[4] and sensorValues[5] < umbrales[5] and sensorValues[6] < umbrales[6]) {
    Motor(25, 75);


    //B,B,N,N,B,B
  } else if (sensorValues[1] < umbrales[1] and sensorValues[2] < umbrales[2] and sensorValues[3] >= umbrales[3] and sensorValues[4] >= umbrales[4] and sensorValues[5] < umbrales[5] and sensorValues[6] < umbrales[6]) {
    Motor(50, 50);


    //B,B,B,N,N,B
  } else if (sensorValues[1] < umbrales[1] and sensorValues[2] < umbrales[2] and sensorValues[3] < umbrales[3] and sensorValues[4] >= umbrales[4] and sensorValues[5] >= umbrales[5] and sensorValues[6] < umbrales[6]) {
    Motor(75, 25);


    //B,B,B,B,N,N
  } else if (sensorValues[1] < umbrales[1] and sensorValues[2] < umbrales[2] and sensorValues[3] < umbrales[3] and sensorValues[4] < umbrales[4] and sensorValues[5] >= umbrales[5] and sensorValues[6] >= umbrales[6]) {
    Motor(100, 0);


    //N,N,N,N,N,N
  } else if (sensorValues[1] >= umbrales[1] and sensorValues[2] >= umbrales[2] and sensorValues[3] >= umbrales[3] and sensorValues[4] >= umbrales[4] and sensorValues[5] >= umbrales[5] and sensorValues[6] >= umbrales[6]) {
    Motor(75, 75);
  }
}

#include"definiciones.h"
//robot negro

//LIBRERIAS
#include <QTRSensors.h>

//VARIBLES
//sensores
QTRSensors qtr;
QTRSensors qtrIzq;
QTRSensors qtrDer;

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
uint16_t sensorValuesIzq[1];
uint16_t sensorValuesDer[1];

//pwm
const int freq = 5000;
const int resolution = 8;

//-----------------Variables PID----------------------------//
int proportional = 0;  // proporcional
int derivative = 0;    // derivada
int last_proportional;
int integrative = 0;  //integral
int error2 = 0;
int error3 = 0;
int error4 = 0;
int error5 = 0;
int error6 = 0;
int ref = 0;

#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  SerialBT.begin("DynamisBot");
  pinMode(BOTON, INPUT);
  pinMode(LED, OUTPUT);
  setupMotores();
  setupSensores();
  calibrar();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int estado = verificarCaso();  
  if (estado == 0){ //normal
    pid(30, 150, 0.2, 0, 0, -1);
  }else if (estado == 1){//interseccion
    mover(0,0);
  }
  
  /*
  int estado = verificarCasos();
  if (estado == algo){
    if (gap){
      //hacer codigo del gap
    }else if(interseccion){
      //hacer codigo de la interseccion
    }
  }else{
    pid();
  }*/
}

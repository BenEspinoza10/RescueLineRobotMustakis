#include <QTRSensors.h>
#include "Pines.h"

//Estas son las librerias del giroscopio
#include <MPU6050_light.h>
#include <Wire.h>


//Inicializaciones de sensores y motores
//Si bien los sensores no se utilizan, es necesario para que todo funcione manteniendo lo anterior
const int freq = 5000;
const int resolution = 8;

QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

//Aquí empieza lo nuevo

MPU6050 mpu(Wire);  //Crea un objeto MPU6050 para la comunicación I2C

void setup() {
  Serial.begin(115200); //Asegurarse que este siempre sea el primero en inicializarse para evitar cualquier problema
  inicializarGiroscopio(); //Para referencia ir a la pestaña giroscopio
  inicializarMotores();
}
void loop() {
  mpu.update();                  // Actualizar los datos del sensor
  int angulo_inicial = mpu.getAngleZ();  //Obtiene el ángulo actual del eje solicitado
  int angulo_actual = angulo_inicial;
  //Giro hacia la izquierda
  while(angulo_actual - angulo_inicial < 90){
    Motor(-100,100);
    mpu.update();     
    angulo_actual = mpu.getAngleZ();    
    Serial.print("Angulo Inicio: ");
    Serial.print(angulo_inicial);
    Serial.print("Angulo Actual: ");
    Serial.println(angulo_actual);
  }
  Motor(0,0);
  delay(1000);
  //Giro hacia la derecha
  angulo_inicial = mpu.getAngleZ();  //Obtiene el ángulo actual del eje solicitado
  angulo_actual = angulo_inicial;
  while(angulo_actual - angulo_inicial > -90){
    Motor(100,-100);
    mpu.update();     
    angulo_actual = mpu.getAngleZ();    
    Serial.print("Angulo Inicio: ");
    Serial.print(angulo_inicial);
    Serial.print("Angulo Actual: ");
    Serial.println(angulo_actual);
  }
  Motor(0,0);
  delay(1000);
}

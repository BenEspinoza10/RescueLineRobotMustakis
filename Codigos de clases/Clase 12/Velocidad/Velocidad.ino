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

unsigned long lastTime = 0;
float vx = 0;
long timer = 0;
int temp = 0;

void setup() {
  Serial.begin(115200);     //Asegurarse que este siempre sea el primero en inicializarse para evitar cualquier problema
  inicializarGiroscopio();  //Para referencia ir a la pestaña giroscopio
  inicializarMotores();
}
void loop() {
  Motor(temp,temp);
  mpu.update();
  float ax = mpu.getAccY();
  unsigned long currentTime = millis();
  float dt = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;

  // Convertir a m/s² (suponiendo ±2g full scale => 16384 LSB/g)
  float ax_m_s2 = (float)ax * 9.80665;
  // Suprimir ruido pequeño
  if (abs(ax_m_s2) < 0.1) ax_m_s2 = 0;

  vx += ax_m_s2 * dt;

  Serial.print("Velocidad X: ");
  Serial.print(vx);
  Serial.println(" m/s");

  if (millis()-timer >1000){
    temp+=50;
    timer = millis();
    if (temp > 150 ){
      temp = 0;
    }
  }
}

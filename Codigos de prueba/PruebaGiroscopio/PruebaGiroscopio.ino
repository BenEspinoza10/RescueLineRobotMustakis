#include <MPU6050_light.h>
#include <Wire.h>

MPU6050 mpu(Wire);  //Crea un objeto MPU6050 para la comunicación I2C

void setup() {
  Serial.begin(115200); //Asegurarse que este siempre sea el primero en inicializarse para evitar cualquier problema  
  Wire.begin();  // Inicializa la comunicación I2C
  mpu.begin();   // Inicializa el MPU6050  
  Serial.print(F("MPU6050 estado: "));
  Serial.println(F("Calculando compensación MPU6050"));  //no se debe mover el MPU6050
  mpu.calcGyroOffsets();                                   //Calibrar giroscopio (Se demora unos seg’s)
  Serial.println("Listo!\n");
}
void loop() {
  mpu.update();                  // Actualizar los datos del sensor
  int angulo = mpu.getAngleZ();  //Obtiene el ángulo actual del eje solicitado
  Serial.println(angulo);
}

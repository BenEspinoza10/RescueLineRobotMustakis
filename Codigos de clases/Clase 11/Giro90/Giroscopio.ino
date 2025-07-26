void inicializarGiroscopio(){
  Wire.begin();  // Inicializa la comunicación I2C
  mpu.begin();   // Inicializa el MPU6050  
  Serial.print(F("MPU6050 estado: "));
  Serial.println(F("Calculando compensación MPU6050"));  //no se debe mover el MPU6050
  mpu.calcGyroOffsets();                                   //Calibrar giroscopio (Se demora unos seg’s)
  Serial.println("Listo!\n");
}

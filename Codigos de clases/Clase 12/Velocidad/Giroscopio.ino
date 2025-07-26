void inicializarGiroscopio(){
  Wire.begin();  // Inicializa la comunicación I2C
  mpu.begin();   // Inicializa el MPU6050  
  Serial.print(F("MPU6050 estado: "));
  Serial.println(F("Calculando compensación MPU6050"));  //no se debe mover el MPU6050  
  mpu.calcOffsets(true,true); // hace la calibración del giroscopio Y el acelerómetro
  Serial.println("Listo!\n");
}

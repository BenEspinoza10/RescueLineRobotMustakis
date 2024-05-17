int verificarCaso() {
  int umbral = 3900;
  int x;
  qtr.read(sensorValues);
  if (sensorValues[0] >= umbral and sensorValues[1] >= umbral and sensorValues[2] >= umbral and sensorValues[3] >= umbral and sensorValues[4] >= umbral and sensorValues[5] >= umbral) {
    x = 1;  //todo negro
  } else if (sensorValues[0] < umbral and sensorValues[1] < umbral and sensorValues[2] < umbral and sensorValues[3] < umbral and sensorValues[4] < umbral and sensorValues[5] < umbral) {
    x = 2;  // todo blanco
  } else {
    x = 0;
  }
  return x;
}
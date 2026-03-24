bool es_interseccion(){
  if (sensorValues[0] < umbrales[0] and sensorValues[1] < umbrales[1] and sensorValues[2] < umbrales[2] and sensorValues[3] < umbrales[3] and sensorValues[4] < umbrales[4] and sensorValues[5] < umbrales[5] and sensorValues[6] < umbrales[6] and sensorValues[7] < umbrales[7]) {
    return true;
  }else{
    return false;
  }
}

bool es_gap(){
  if (sensorValues[0] >= umbrales[0] and sensorValues[1] >= umbrales[1] and sensorValues[2] >= umbrales[2] and sensorValues[3] >= umbrales[3] and sensorValues[4] >= umbrales[4] and sensorValues[5] >= umbrales[5] and sensorValues[6] >= umbrales[6] and sensorValues[7] >= umbrales[7]) {
    return true;
  }else{
    return false;
  }
}

bool giro_90_izq(){
  if (sensorValues[0] >= umbrales[0] and sensorValues[1] >= umbrales[1] and sensorValues[2] >= umbrales[2] and sensorValues[3] >= umbrales[3] and sensorValues[4] >= umbrales[4] and sensorValues[5] < umbrales[5] and sensorValues[6] < umbrales[6] and sensorValues[7] < umbrales[7]) {
    return true;
  }else{
    return false;
  }
}

bool giro_90_der(){
  if (sensorValues[0] < umbrales[0] and sensorValues[1] < umbrales[1] and sensorValues[2] < umbrales[2] and sensorValues[3] >= umbrales[3] and sensorValues[4] >= umbrales[4] and sensorValues[5] >= umbrales[5] and sensorValues[6] >= umbrales[6] and sensorValues[7] >= umbrales[7]) {
    return true;
  }else{
    return false;
  }
}
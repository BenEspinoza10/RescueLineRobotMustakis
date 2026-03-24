void siguelineas(){
  int posicion = qtr.readLineBlack(sensorValues);
  posicion = map(posicion, 0, 7000, -255, 255);  
  //Se hace un siguelíneas simple de 3 casos
  //El robot está relativamente centrado
  if (posicion <= 50 and posicion >= -50){
    Motor(100,100);
  //La línea se encuentra a la izquierda del robot
  }else if (posicion < -50){
    Motor(0,100);
  //La línea se encuentra a la derecha del robot
  }else if(posicion > 50){
    Motor(100,0);
  } 
}
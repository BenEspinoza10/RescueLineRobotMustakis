//Se incluyen los pines
#include "Pines.h"

//Se define la frecuencia y resolución
//Se puede jugar con la frecuencie entre 5000 y 8000, no vale la pena tocar la resolución
const int freq = 5000;
const int resolution = 8;


void setup() {
  // Se inicializa los motores
  inicializarMotores();
  //Se espera a que se presione el botón para empezar
  while (digitalRead(BOTON) == 0) {
  }
}

void loop() {
  //Una serie de movimientos para probar las diferentes capacidades de la funcion
  Motor(150,150);
  delay(1000);
  Motor(-150,150);
  delay(1000);
  Motor(0,0);
  delay(1000);
  Motor(150,-150);
  delay(1000);
}

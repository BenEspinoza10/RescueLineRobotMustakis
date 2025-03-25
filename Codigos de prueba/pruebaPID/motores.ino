void Motoriz(int value) {
  if ( value >= 0 ) {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  } else {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    value *= -1;
  }
  ledcWrite(0, value);
}
// Función accionamiento motor derecho
void Motorde(int value) {
  if ( value >= 0 ) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    value *= -1;
  }
  ledcWrite(1, value);
}

//Accionamiento de motores
void Motor(int left, int righ) {
  Motoriz(left);
  Motorde(righ);
}
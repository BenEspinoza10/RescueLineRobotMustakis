#define AIN1 16
#define AIN2 17
#define PWMA 4

#define BIN1 5
#define BIN2 18
#define PWMB 19

#define BOTON 12

const int freq = 5000;
const int resolution = 8;

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
void setup() {
  // put your setup code here, to run once:
  pinMode(BIN2  , OUTPUT);
  pinMode(BIN1  , OUTPUT);
  ledcSetup(1, freq, resolution);
  ledcAttachPin(PWMB, 1);
  pinMode(AIN1  , OUTPUT);
  pinMode(AIN2  , OUTPUT);
  ledcSetup(0, freq, resolution);
  ledcAttachPin(PWMA, 0);
  while (digitalRead(BOTON) == 0) {
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Motor(255,255);
  /*Motor(-150,150);
  delay(1000);
  Motor(0,0);
  delay(1000);
  Motor(150,-150);
  delay(1000);*/
}

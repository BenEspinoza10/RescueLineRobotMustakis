#define AIN1 14
#define AIN2 13
#define PWMA 19

#define BIN1 4
#define BIN2 5
#define PWMB 18

const int freq = 5000;
const int resolution = 8;

void Motoriz(int value) {
  if ( value >= 0 ) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
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
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Motor(100,100);
  delay(1000);
  Motor(-100,-100);
  delay(1000);
  Motor(0,100);
  delay(1500);
}

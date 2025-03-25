#define boton 12


void setup() {
  pinMode(boton, INPUT);
  Serial.begin(115200);
}

void loop() {
  int estado_boton = digitalRead(boton);
  Serial.print("estado boton ");
  Serial.println(estado_boton);
  delay(100);
}

#include <QTRSensors.h>

#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


QTRSensors qtr;
QTRSensors qtrIzq;
QTRSensors qtrDer;

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
uint16_t sensorValuesIzq[1];
uint16_t sensorValuesDer[1];

#define LED 2

void setup() {
  // configure the sensors
  //siguelineas
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ 25, 33, 32, 35, 34, 39 }, SensorCount);
  qtr.setEmitterPin(27);
  //sensor izquierdo
  qtrIzq.setTypeAnalog();
  qtrIzq.setSensorPins((const uint8_t[]){ 26 }, 1);
  qtrIzq.setEmitterPin(27);
  //sensor derecho
  qtrDer.setTypeAnalog();
  qtrDer.setSensorPins((const uint8_t[]){ 36 }, 1);
  qtrDer.setEmitterPin(27);
  pinMode(LED,OUTPUT);

  for (int i = 0; i < 200; i++) {
    qtr.calibrate();
    digitalWrite(LED, HIGH);
    delay(10);
    digitalWrite(LED, LOW);
    delay(10);
  }
  Serial.begin(115200);
  SerialBT.begin("RescueLineBot");
}


void loop() {
  // read raw sensor values
  qtr.read(sensorValues);
  /*
  int posicion = qtr.readLineBlack(sensorValues);
  posicion = map(posicion,0,5000,-255,255);
  Serial.println(posicion);
  */
  qtrIzq.read(sensorValuesIzq);
  qtrDer.read(sensorValuesDer);
  //int lecturaIzquierda = analogRead(26);
  //int lecturaDerecha = analogRead(36);

  // print the sensor values as numbers from 0 to 1023, where 0 means maximum
  // reflectance and 1023 means minimum reflectance
  Serial.print(sensorValuesIzq[0]);
  Serial.print('\t');
  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(sensorValuesDer[0]);
  delay(100);
}

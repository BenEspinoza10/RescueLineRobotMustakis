#include <QTRSensors.h>

#include <BluetoothSerial.h>

#define BOTON 12

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

#define LED 2

void setup() {
  // configure the sensors
  //siguelineas
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ 36, 39, 34, 35, 32, 33, 25, 26 }, SensorCount);
  qtr.setEmitterPin(27);
  pinMode(LED, OUTPUT);

  for (int i = 0; i < 200; i++) {
    qtr.calibrate();
    digitalWrite(LED, HIGH);
    delay(10);
    digitalWrite(LED, LOW);
    delay(10);
  }
  Serial.begin(115200);
  SerialBT.begin("RescueLineBot");

  while (digitalRead(BOTON) == 0) {
  }
}

void loop() {
  // read raw sensor values
  qtr.read(sensorValues);
  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  int posicion = qtr.readLineBlack(sensorValues);
  posicion = map(posicion, 0, 7000, -255, 255);
  Serial.print(posicion);
  Serial.println('\t');
}

#include <QTRSensors.h>

#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


QTRSensors qtr;

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

void setup() {
  // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ 25, 33, 32, 35, 34, 36 }, SensorCount);
  qtr.setEmitterPin(27);

  Serial.begin(115200);
  SerialBT.begin("RescueLineBot");
}


void loop() {
  // read raw sensor values
  qtr.read(sensorValues);
  int lecturaIzquierda = analogRead(26);
  int lecturaDerecha = analogRead(39);

  // print the sensor values as numbers from 0 to 1023, where 0 means maximum
  // reflectance and 1023 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++) {
    SerialBT.print(sensorValues[i]);
    SerialBT.print('\t');
  }
  SerialBT.print("||||");
  SerialBT.print(lecturaIzquierda);
  SerialBT.print('\t');
  SerialBT.println(lecturaDerecha);
  delay(250);
}

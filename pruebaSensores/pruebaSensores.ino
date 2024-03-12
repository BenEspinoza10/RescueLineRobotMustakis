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

void setup() {
  // configure the sensors
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){25, 33, 32, 35, 34, 39}, SensorCount);  
  qtr.setEmitterPin(27);
  qtrIzq.setTypeAnalog();
  qtrIzq.setSensorPins((const uint8_t[]){ 26 }, 1);
  qtrIzq.setEmitterPin(27);
  qtrDer.setTypeAnalog();
  qtrDer.setSensorPins((const uint8_t[]){ 36 }, 1);
  qtrDer.setEmitterPin(27);


  Serial.begin(115200);
  SerialBT.begin("RescueLineBot");
}


void loop() {
  // read raw sensor values
  qtr.read(sensorValues);
  qtrIzq.read(sensorValuesIzq);
  qtrDer.read(sensorValuesDer);
  //int lecturaIzquierda = analogRead(26);
  //int lecturaDerecha = analogRead(36);

  // print the sensor values as numbers from 0 to 1023, where 0 means maximum
  // reflectance and 1023 means minimum reflectance
  SerialBT.print(sensorValuesIzq[0]);
  SerialBT.print('\t');
  for (uint8_t i = 0; i < SensorCount; i++) {
    SerialBT.print(sensorValues[i]);
    SerialBT.print('\t');
  }
  
  SerialBT.println(sensorValuesDer[0]);
  delay(250);
}

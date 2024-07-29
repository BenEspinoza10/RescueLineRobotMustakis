#include <QTRSensors.h>

#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


QTRSensors qtr;

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];


#define LED 2

void setup() {
  // configure the sensors
  //siguelineas
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ 26,25, 33, 32, 35, 34, 39, 36}, SensorCount);
  qtr.setEmitterPin(27);  
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
  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  int posicion = qtr.readLineBlack(sensorValues);
  posicion = map(posicion,0,7000,-255,255);
  Serial.print(posicion);
  Serial.println('\t');  
}

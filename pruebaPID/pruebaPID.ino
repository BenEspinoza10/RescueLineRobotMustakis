#include <QTRSensors.h>

#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;


QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

//-------------------Definición motores------------------------//

#define AIN1 16
#define AIN2 17
#define PWMA 4

#define BIN1 5
#define BIN2 18
#define PWMB 19

const int freq = 5000;
const int resolution = 8;

//-----------------Variables PID----------------------------//
int proportional = 0;  // proporcional
int derivative = 0;    // derivada
int last_proportional;
int integrative = 0;  //integral
int error2 = 0;
int error3 = 0;
int error4 = 0;
int error5 = 0;
int error6 = 0;
int ref = 0;


void setup() {
  //Seteo motores
  pinMode(BIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  ledcSetup(1, freq, resolution);
  ledcAttachPin(PWMB, 1);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  ledcSetup(0, freq, resolution);
  ledcAttachPin(PWMA, 0);
  //Seteo sensores
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ 26,25, 33, 32, 35, 34, 36,39 }, SensorCount);
  qtr.setEmitterPin(27);

  Serial.begin(115200);
  SerialBT.begin("RescueLineBot");

  for (uint16_t i = 0; i < 100; i++) {
    qtr.calibrate();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  seguir_linea(60, 170, 1.02, 0, 10.75, 170);
}

#include <Wire.h>
#include <MPU6050_light.h>
#include "Adafruit_VL53L0X.h"
#include <QTRSensors.h>
#include "BluetoothSerial.h"

#define BOTON 12
#define LED 2

MPU6050 mpu(Wire);
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
BluetoothSerial SerialBT;
QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

enum ModoTest {
  TEST_GIRO = 0,
  TEST_LASER,
  TEST_QTR
};

ModoTest modoActual = TEST_GIRO;
ModoTest ultimoModo = (ModoTest)(-1);

bool estadoBotonAnterior = HIGH;
unsigned long ultimoCambioBoton = 0;
const unsigned long debounceMs = 200;

unsigned long ultimoUpdate = 0;

bool gyroInicializado = false;
bool laserInicializado = false;
bool qtrInicializado = false;
bool btInicializado = false;

void anunciarModo() {
  Serial.println();
  Serial.println("==================================");
  switch (modoActual) {
    case TEST_GIRO:
      Serial.println("Modo actual: GIROSCOPIO");
      break;
    case TEST_LASER:
      Serial.println("Modo actual: LASER VL53L0X");
      break;
    case TEST_QTR:
      Serial.println("Modo actual: SENSORES QTR");
      break;
  }
  Serial.println("Presiona el boton para cambiar de test");
  Serial.println("==================================");
  Serial.println();
}

void initGyro() {
  if (gyroInicializado) return;

  Wire.begin();
  mpu.begin();
  Serial.println("Inicializando MPU6050...");
  Serial.println("No mover el robot, calibrando...");
  mpu.calcGyroOffsets();
  Serial.println("MPU6050 listo");
  gyroInicializado = true;
}

void initLaser() {
  if (laserInicializado) return;

  Serial.println("Inicializando VL53L0X...");
  if (!lox1.begin()) {
    Serial.println("Error: no se pudo iniciar VL53L0X");
    return;
  }
  Serial.println("VL53L0X listo");
  laserInicializado = true;
}

void initQTR() {
  if (qtrInicializado) return;

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){36, 39, 34, 35, 32, 33, 25, 26}, SensorCount);
  qtr.setEmitterPin(27);

  if (!btInicializado) {
    SerialBT.begin("RescueLineBot");
    btInicializado = true;
  }

  Serial.println("Calibrando QTR...");
  for (int i = 0; i < 200; i++) {
    qtr.calibrate();
    digitalWrite(LED, HIGH);
    delay(10);
    digitalWrite(LED, LOW);
    delay(10);
  }
  Serial.println("QTR listo");
  qtrInicializado = true;
}

void entrarModo(ModoTest nuevoModo) {
  modoActual = nuevoModo;

  switch (modoActual) {
    case TEST_GIRO:
      initGyro();
      break;
    case TEST_LASER:
      initLaser();
      break;
    case TEST_QTR:
      initQTR();
      break;
  }

  anunciarModo();
}

void siguienteModo() {
  int siguiente = (modoActual + 1) % 3;
  entrarModo((ModoTest)siguiente);
}

void leerBoton() {
  bool estadoActual = digitalRead(BOTON);

  if (estadoBotonAnterior == HIGH && estadoActual == LOW) {
    if (millis() - ultimoCambioBoton > debounceMs) {
      ultimoCambioBoton = millis();
      siguienteModo();
    }
  }

  estadoBotonAnterior = estadoActual;
}

void ejecutarGyro() {
  if (!gyroInicializado) return;

  if (millis() - ultimoUpdate >= 100) {
    ultimoUpdate = millis();
    mpu.update();
    int angulo = mpu.getAngleZ();
    Serial.print("Angulo Z: ");
    Serial.println(angulo);
  }
}

void ejecutarLaser() {
  if (!laserInicializado) return;

  if (millis() - ultimoUpdate >= 150) {
    ultimoUpdate = millis();

    VL53L0X_RangingMeasurementData_t measure1;
    lox1.rangingTest(&measure1, false);

    if (measure1.RangeStatus != 4) {
      Serial.print("Distancia (mm): ");
      Serial.println(measure1.RangeMilliMeter);
    } else {
      Serial.println("Laser: out of range");
    }
  }
}

void ejecutarQTR() {
  if (!qtrInicializado) return;

  if (millis() - ultimoUpdate >= 100) {
    ultimoUpdate = millis();

    qtr.read(sensorValues);
    for (uint8_t i = 0; i < SensorCount; i++) {
      Serial.print(sensorValues[i]);
      Serial.print('\t');
    }

    int posicion = qtr.readLineBlack(sensorValues);
    posicion = map(posicion, 0, 7000, -255, 255);
    Serial.print("Posicion: ");
    Serial.println(posicion);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BOTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  delay(500);
  entrarModo(TEST_GIRO);
}

void loop() {
  leerBoton();

  switch (modoActual) {
    case TEST_GIRO:
      ejecutarGyro();
      break;
    case TEST_LASER:
      ejecutarLaser();
      break;
    case TEST_QTR:
      ejecutarQTR();
      break;
  }
}
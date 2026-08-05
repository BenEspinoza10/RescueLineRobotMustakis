#include <Wire.h>
#include <Adafruit_TCS34725.h>

// ---------------------------------------------------
// Dirección I2C del multiplexor PCA9548A
// (0x70 es la dirección por defecto si A0,A1,A2 están a GND)
// ---------------------------------------------------
#define MUXADDR 0x70

// Canales del multiplexor donde conectaste cada rgb
#define CANAL_SENSOR_1 0
#define CANAL_SENSOR_2 1

// Ambos sensores usan la misma dirección I2C (0x29),
// pero al estar en canales distintos del mux no hay conflicto.
Adafruit_TCS34725 rgb1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 rgb2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// ---------------------------------------------------
// Selecciona el canal activo del PCA9548A.
// Es solo un byte: cada bit habilita un canal (0-7).
// ---------------------------------------------------
void muxSelect(uint8_t canal) {
  Wire.beginTransmission(0x70);
  Wire.write(1 << canal);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // --- Inicializar sensor 1 ---
  muxSelect(CANAL_SENSOR_1);
  rgb1.begin();
 
  // --- Inicializar sensor 2 ---
  muxSelect(CANAL_SENSOR_2);
  rgb2.begin();
}

// ---------------------------------------------------
// Lee y muestra los datos crudos de color de un rgb,
// seleccionando primero su canal en el mux.
// ---------------------------------------------------
void leerSensor(Adafruit_TCS34725 &rgb, uint8_t canal, const char* nombre) {
  muxSelect(canal);

  uint16_t r, g, b, c;
  rgb.getRawData(&r, &g, &b, &c);

  Serial.print(nombre);
  Serial.print(" -> R: "); Serial.print(r);
  Serial.print("  G: "); Serial.print(g);
  Serial.print("  B: "); Serial.print(b);
  Serial.print("  C: "); Serial.println(c);
}

void loop() {
  leerSensor(rgb1, CANAL_SENSOR_1, "rgb 1");
  leerSensor(rgb2, CANAL_SENSOR_2, "rgb 2");

  Serial.println("-----------------------------");
  delay(500);
}

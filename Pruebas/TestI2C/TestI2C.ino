/**
 * TCA9548 I2CScanner.ino -- I2C bus scanner for Arduino
 *
 * Based on https://playground.arduino.cc/Main/I2cScanner/
 *
 */

#include "Wire.h"


#define TCAADDR 0x70

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup()
{

    Wire.begin();
    
    Serial.begin(115200);
    Serial.println("\nTCA escaner listo");
    
    for (uint8_t t=0; t<8; t++) {
      tcaselect(t);
      Serial.print("  Escaneando salida "); Serial.println(t);

      for (uint8_t addr = 0x20; addr<=0x40; addr++) {
        if (addr == TCAADDR) continue;
        Serial.print("Direccion analizada: ");
        Serial.println(addr);
        Wire.beginTransmission(addr);
        if (!Wire.endTransmission()) {
          Serial.print("  - Encontrado I2C 0x");  Serial.println(addr,HEX);
        }
      }
    }
    Serial.println("Finalizado");
}

void loop() 
{
}
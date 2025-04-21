#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();

#define BOTON 12

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
 
  Serial.println("Adafruit VL53L0X test");
  if (!lox1.begin()) {
    Serial.println(F("Failed to boot VL53L0X 1"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
  while (digitalRead(BOTON) == 0) {
  }
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure1;
   
  //Serial.print("Reading a measurement... ");
  
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!

  if (measure1.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure1.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
   
  delay(100);
}

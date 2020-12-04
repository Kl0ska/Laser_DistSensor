/*
 * Laser-Sensor Testprogramm
 * Pick-Uptroniker
 * 03.12.2020
 * 
 * Laser Sensor über I2C angeschlossen
 * 
 * 
 * Adafruit VL53L0X Bibliothek für Lasersensor über I2C
 * EWMA Bibliothek für die Glättung des Messwertes
 */


#include "Adafruit_VL53L0X.h"   //Bibliothek für das Auslesen vom Sensor über I2C
#include <Ewma.h>   //Bibliothek für das Glätten

Adafruit_VL53L0X lox = Adafruit_VL53L0X();


float distanzGlatt;  //Der geglättet Wert der Messung

Ewma adcFilter2(0.15); //Den Faktor und den Filternamen deklarieren

void setup() {
  Serial.begin(9600);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  // power
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  int raw = measure.RangeMilliMeter;

  if (measure.RangeStatus != 4)
  {
    distanzGlatt = adcFilter2.filter(raw);   //Filtern des Messwertes
  }


  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4)
  { // phase failures have incorrect data
    Serial.print("Distanz Glatt (mm): "); Serial.println(distanzGlatt);
    //Serial.print("    Distanz Roh (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }

  delay(100);
}

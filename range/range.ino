#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X rangeSensor = Adafruit_VL53L0X();
unsigned long timing;
void setup()
{
Serial.begin(115200);
rangeSensor.begin();
}
void loop()
{
  if (millis() - timing > 5000){
    timing = millis();
    VL53L0X_RangingMeasurementData_t measure;
    Serial.print("Reading a measurement... ");
    rangeSensor.rangingTest(&measure, false);
    if (measure.RangeStatus != 4)
    { 
      Serial.print("Distance (mm): ");
      Serial.println(measure.RangeMilliMeter);
    }
    else
    {
    Serial.println(" out of range ");
    }
  }
}

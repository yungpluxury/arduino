//wind direction sensor
#define CLK 14
#define DT 12
#include "GyverEncoder.h"

//temperature sensor
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2

//range sensor
#include "Adafruit_VL53L0X.h"

//range sensor
Adafruit_VL53L0X rangeSensor = Adafruit_VL53L0X();

//temperature sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float temp1, temp2, temp3;

//speed sensor
int linearHallSensorPin = A0;
int linearHallSensorValue = 0;
int counter = 0;
long loopTime = 10000;

//wind direction sensor
Encoder enc1(CLK, DT);
int value = 0;

unsigned long timing1;
unsigned long timing2;
unsigned long timing3;

void setup() {
Serial.begin(9600);
sensors.begin(); // temperature sensors
enc1.setType(TYPE1); //wind direction sensor
rangeSensor.begin(); //range sensor
}

void loop() {

//temperature sensor
if (millis() - timing1 > 9000)
{
timing1 = millis(); 
sensors.requestTemperatures(); 
temp1 = sensors.getTempCByIndex(0); 
temp2 = sensors.getTempCByIndex(1);
temp3 = sensors.getTempCByIndex(2);
Serial.println("Температура 1:");
Serial.println(temp1);
Serial.println("Температура 2:");
Serial.println(temp2);  
Serial.println("Температура 3:");
Serial.println(temp3);
}

//range sensor
if (millis() - timing2 > 10000)
{
timing2 = millis();
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

//speed sensor
unsigned long currentMillis = millis();
if (millis() - timing3 > 15000)
{
timing3 = millis();
unsigned long currentMillis = millis();
while(millis()-currentMillis<=loopTime)
{
linearHallSensorValue = analogRead (linearHallSensorPin);
  if (linearHallSensorValue < 700) {
    counter++;
    Serial.println(counter);
    }
}
}

//wind direcrion sensor
enc1.tick();
if (enc1.isRight()) value++;
if (enc1.isLeft()) value--;
if (value == 20 || value == -20) {
  value = 0;
  }
if (enc1.isTurn()) { 
Serial.println(value);
}
}

//LoRa Transiver
#include <SPI.h>
#include <LoRa.h>
#define ss 15
#define rst 16
#define dio0 2
String loraSignal = "Передача пакета ЛоРа";
String LoRaMessage = "";


//ws2812 led
#include "FastLED.h"
#define LED_COUNT 1
#define LED_PIN 0
CRGB strip[LED_COUNT];


//Range sensor
#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X rangeSensor = Adafruit_VL53L0X();
float range;


//Temperature sensor
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float temp1, temp2, temp3;


//Timers
unsigned long timing1;
unsigned long timing2;
unsigned long timing3;
unsigned long timing4;
unsigned long timing5;
unsigned long timing6;
unsigned long timing7;
unsigned long timing8;


//UF sensor
float uf;


void setup() 
{
//UF sensor
FastLED.addLeds<WS2812B, LED_PIN, RGB>(strip, LED_COUNT);
//Range sensor
rangeSensor.begin();
//Temperature sensors
sensors.begin();
//Serial port opening
Serial.begin(115200);
//LoRa transsiver
while (!Serial);
Serial.println(F("Starting LoRa successful"));
LoRa.setPins(ss, rst, dio0);
if (!LoRa.begin(868E6)) {
  Serial.println("Starting LoRa failed!");
  delay(100);
  while (1);
}
}
 
void loop() 
{

//UF sensor
if (millis() - timing4 > 8000) 
{
    timing4 = millis();
    uf = analogRead(A0);
    Serial.println("UF:");
    Serial.println(uf);
    strip[0] = CRGB::Red;
    FastLED.show();
    if (millis() - timing5 > 1000)
    {
      timing5 = millis();
      strip[0] = CRGB::Black;  
      FastLED.show();
    }
    
}
  
//Range sensor
if (millis() - timing3 > 10000)
{
timing3 = millis();
VL53L0X_RangingMeasurementData_t measure;
rangeSensor.rangingTest(&measure, false);
if (measure.RangeStatus != 4) { 
  Serial.print("Distance (mm): ");
  Serial.println(measure.RangeMilliMeter);
  range = measure.RangeMilliMeter;
} else {
  Serial.println(" out of range ");
}
strip[0] = CRGB::Green;
    FastLED.show();
    if (millis() - timing6 > 1000)
    {
      timing6 = millis();
      strip[0] = CRGB::Black;  
      FastLED.show();
    }
}

//Temperature sensors
if (millis() - timing2 > 11000)
{
timing2 = millis(); 
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
strip[0] = CRGB::Blue;
    FastLED.show();
    if (millis() - timing7 > 1000)
    {
      timing7 = millis();
      strip[0] = CRGB::Black;  
      FastLED.show();
    }

}


//Lora transiving
if (millis() - timing1 > 12000)
{
  timing1 = millis();
  Serial.print(loraSignal);
  Serial.println("");
  
  LoRaMessage = String(loraSignal) + "&" + String(range) + "&" + String(temp1) + "&" + String(temp2) + "&" + String(temp3) + "&" + String(uf) + "&" + "/";

  Serial.println(LoRaMessage);
  
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket(); 
  strip[0] = CRGB::White;
    FastLED.show();
    if (millis() - timing8 > 1000)
    {
      timing8 = millis();
      strip[0] = CRGB::Black;  
      FastLED.show();
    }

}
}

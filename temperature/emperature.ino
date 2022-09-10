#include <OneWire.h>
#include <DallasTemperature.h> 
#define ONE_WIRE_BUS 2

 
OneWire oneWire(ONE_WIRE_BUS); // передаем данные о аналоговом выходе
DallasTemperature sensors(&oneWire); // объявление датчиков
float temp1, temp2, temp3; // создаем переменные для температуры
void setup() {
Serial.begin(115200); 
sensors.begin(); // начинаем считывать данные с датчиков
}
void loop() {
sensors.requestTemperatures(); // опрашиваем датчики 
temp1 = sensors.getTempCByIndex(0); // присваиваем
temp2 = sensors.getTempCByIndex(1);
temp3 = sensors.getTempCByIndex(2);
Serial.println("Температура 1:");
Serial.println(temp1);
Serial.println("Температура 2:");
Serial.println(temp2);
Serial.println("Температура 3:");
Serial.println(temp3);


delay(5000); // выставляем задержку 5 секунд 
}

int linearHallSensorPin = A0;    // выбор пина для датчика
int linearHallSensorValue = 0;   // переменная для значения с датчика
int counter = 0;
 
void setup () 
{
  Serial.begin (9600);
}
 
void loop () 
{
  
  linearHallSensorValue = analogRead (linearHallSensorPin);
  if (linearHallSensorValue < 700) {
    counter++;
    Serial.println(counter);
    }
}

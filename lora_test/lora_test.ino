#include <SPI.h>
#include <LoRa.h>
 
#define ss 15
#define rst 16
#define dio0 4

String data;
int pos1,pos2;
 
void setup() {
  Serial.begin(115200);
  while (!Serial);
 
  Serial.println("LoRa Receiver");
 
  LoRa.setPins(ss, rst, dio0);
 
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");

}
 
void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    String LoRaData = LoRa.readString();

    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    
    pos1 = LoRaData.indexOf('&');
    pos2 = LoRaData.indexOf('/');

    data = LoRaData.substring(pos1, pos2);
    

    Serial.println(data);
 
    

    }
}

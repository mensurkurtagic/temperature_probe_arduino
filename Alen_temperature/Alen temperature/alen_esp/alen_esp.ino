#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 //podatkovna zica sa sonde
#define RX 11
#define TX 10
SoftwareSerial esp(RX, TX);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  esp.begin(115200);
  delay(3000);  //sacekaj da ucita wifi, mozda i ne treba
  sensors.begin();
}

void sendSendCommand(String command){
  Serial.println(command);
  esp.println(command);
  if(esp.find("OK")){
    Serial.println("AT+CIPSTART succesful");
  } else Serial.println("AT+CIPSTART failed");
}

void sendChipCommand(String command){
  Serial.println(command);
  esp.println(command);
  if(esp.find(">")){
    Serial.println("CHIP command succesful");
  } else Serial.println("CHIP command failed");
}

void sendGetUpdateCommand(String command){
  Serial.println(command);
  esp.println(command);
  delay(3000);
}

void sendCloseCommand(String command){
  Serial.println(command);
  esp.println(command);
  if(esp.find("OK")){
    Serial.println("CLOSE command succesful");
  } else Serial.println("CLOSE command failed");
}

void loop() {
  //prvo dohvati temperaturu
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0); //vrijednost temperature u Celzijusima
  Serial.println(temperatura);
  
  //sad pokreni slanje na server
  sendSendCommand("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
  sendChipCommand("AT+CIPSEND=51");
  sendGetUpdateCommand("GET /update?key=B7GYXG1EORWTZLJ6&field1=" + String(temperatura) + " \r\n");
  sendCloseCommand("AT+CIPCLOSE");
  delay(1000);
}

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

  //definisi input output za pinove
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A0, OUTPUT);
}
/*
void postaviNaHigh(){
  for(int i = 3; i <= 9; i++){
    digitalWrite(i, HIGH);
  }
}

void nula(){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  postaviNaHigh();
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void jedan(){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  postaviNaHigh();
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void dva(){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  postaviNaHigh();
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(9, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
}

void tri(){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  postaviNaHigh();
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
}

void cetiri(){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  postaviNaHigh();
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(5, LOW);
}

void pet(){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  postaviNaHigh();
  digitalWrite(3, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void sest(){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  postaviNaHigh();
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void sedam(){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  postaviNaHigh();
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void osam(){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  postaviNaHigh();
  for(int i = 3; i <= 9; i++){
    digitalWrite(i, LOW);
  }
}

void devet(){
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  postaviNaHigh();
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void drugaNula(){
  digitalWrite(A1, HIGH);
  digitalWrite(A0, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void ispisiPrveCifre(int cifra){
  switch(cifra){
    case 0:
      nula();
      delay(1000);
      break;
    case 1:
      jedan();
      delay(1000);
      break;
    case 2:
      dva();
      delay(1000);
      break;
    case 3:
      tri();
      delay(1000);
      break;
  }
}

void ispisiDrugeCifre(int cifra){
  switch(cifra){
    case 0:
      drugaNula();
      delay(1000);
      break;
  }
}
*/
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

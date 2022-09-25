#include <SPI.h>
#include <LoRa.h> 

int smokeA0=A0;
int ss=10;
int rst=9;
int dio0=2;


void setup() {

  pinMode(ss,OUTPUT);
  digitalWrite(ss, HIGH);
  Serial.begin(9600);
  pinMode(smokeA0,INPUT);
  LoRa.setPins(ss, rst,dio0);  

  while (!Serial);
  Serial.println("LoRa Sender");
    
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  
  //LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
  }
}
 
void loop() {

  float sensorValue=analogRead(smokeA0);
  Serial.println(sensorValue);
  
  LoRa.beginPacket();  
  LoRa.print(sensorValue);
  LoRa.endPacket();
  delay(1000);
    

 
}

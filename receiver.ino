#include <SPI.h>
#include <LoRa.h> 

int REDLED = 3;
int GREENLED = 4;
int ss=10;
int rst= 9;
int dio0= 2;
String inString ="";
int sensorVal=0;
 
void setup() {
  Serial.begin(9600);
  pinMode(REDLED,OUTPUT);
  pinMode(GREENLED,OUTPUT);
  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  while (!Serial);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1); 
  }
 
  //LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}
 
void loop() {
  
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) { 
    // read packet    
    while (LoRa.available())
    {
      int inChar=LoRa.read(); 
      inString+=(char)inChar;
      
      sensorVal=inString.toInt();  
      Serial.println(sensorVal);  

      if(sensorVal > 240)
      {
        Serial.println(sensorVal);
        digitalWrite(REDLED,HIGH);
    
        
      }
      else
      {
        Serial.println(sensorVal);  
        digitalWrite(GREENLED,HIGH);
     
    
      }
      delay(2*1000); // wait 2s for next reading
      digitalWrite(REDLED,LOW);
      digitalWrite(GREENLED,LOW);
    }     
    inString="";    
    LoRa.packetRssi();    
  }
  Serial.println(sensorVal);
  delay(500); // wait 2s for next reading
}

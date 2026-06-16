#include <Ethernet.h>        
#include <ThingSpeak.h>

unsigned long channelID = 3409407;            
const char* writeAPIKey = "UTRP8URMKVNBOGBN"; 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;

const int moisturePinA = A0;
const int moisturePinB = A1;
const int moisturePinC = A2;

const int ldrPinA = A3;
const int ldrPinB = A4;
const int ldrPinC = A5;

const int relayPinA = 2;
const int relayPinB = 3;
const int relayPinC = 4;


const int dryThresholdA = 550; 
const int dryThresholdB = 550; 
const int dryThresholdC = 550; 
const int minLightThreshold = 300; 

void setup() {
  Serial.begin(9600); 
  
  
  pinMode(relayPinA, OUTPUT);
  pinMode(relayPinB, OUTPUT);
  pinMode(relayPinC, OUTPUT);
  
 
  digitalWrite(relayPinA, LOW);
  digitalWrite(relayPinB, LOW);
  digitalWrite(relayPinC, LOW);

  Ethernet.begin(mac);
  ThingSpeak.begin(client);
  
  Serial.println("Multi-Zone Irrigation System Started!");
}

void loop() {
 
  int moistA = analogRead(moisturePinA);
  int moistB = analogRead(moisturePinB);
  int moistC = analogRead(moisturePinC);
  
  int lightA = analogRead(ldrPinA);
  int lightB = analogRead(ldrPinB);
  int lightC = analogRead(ldrPinC);

 
  Serial.print("Plant A - Moist: " + String(moistA) + " Light: " + String(lightA));
  Serial.print(" | Plant B - Moist: " + String(moistB) + " Light: " + String(lightB));
  Serial.println(" | Plant C - Moist: " + String(moistC) + " Light: " + String(lightC));

  int pumpA = 0, pumpB = 0, pumpC = 0;


  if (moistA > dryThresholdA && lightA > minLightThreshold) {
    digitalWrite(relayPinA, HIGH);
    pumpA = 1;
    Serial.println("-> Pump A: ON");
  } else {
    digitalWrite(relayPinA, LOW);
  }

 
  if (moistB > dryThresholdB && lightB > minLightThreshold) {
    digitalWrite(relayPinB, HIGH);
    pumpB = 1; 
    Serial.println("-> Pump B: ON");
  } else {
    digitalWrite(relayPinB, LOW);  
  }


  if (moistC > dryThresholdC && lightC > minLightThreshold) {
    digitalWrite(relayPinC, HIGH); 
    pumpC = 1;
    Serial.println("-> Pump C: ON");
  } else {
    digitalWrite(relayPinC, LOW); 
  }

  ThingSpeak.setField(1, moistA);
  ThingSpeak.setField(2, moistB);
  ThingSpeak.setField(3, moistC);
  ThingSpeak.setField(4, lightA);  
  ThingSpeak.setField(5, pumpA);
  ThingSpeak.setField(6, pumpB);
  ThingSpeak.setField(7, pumpC);

  int result = ThingSpeak.writeFields(channelID, writeAPIKey);
  if (result == 200) {
    Serial.println("ThingSpeak update successful!");
  } else {
    Serial.println("ThingSpeak update failed. Error: " + String(result));
  }

  Serial.println("------------------------------------");
  delay(2000); 
}
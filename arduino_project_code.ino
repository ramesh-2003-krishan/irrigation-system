
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




  if (moistA > dryThresholdA && lightA > minLightThreshold) {
    digitalWrite(relayPinA, HIGH);
    Serial.println("-> Pump A: ON");
  } else {
    digitalWrite(relayPinA, LOW);
  }

 
  if (moistB > dryThresholdB && lightB > minLightThreshold) {
    digitalWrite(relayPinB, HIGH); 
    Serial.println("-> Pump B: ON");
  } else {
    digitalWrite(relayPinB, LOW);  
  }


  if (moistC > dryThresholdC && lightC > minLightThreshold) {
    digitalWrite(relayPinC, HIGH); 
    Serial.println("-> Pump C: ON");
  } else {
    digitalWrite(relayPinC, LOW); 
  }

  Serial.println("------------------------------------");
  delay(2000); 
}
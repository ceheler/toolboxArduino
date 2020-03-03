/*
* Written by Chris Eheler & logic by Tyler Gellinck
* New design 40 Gal TB test solenoid program
* Cycles the latches with solenoids
*/
#include "functions.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  pinMode(solenoid1, OUTPUT);
  pinMode(solenoid2, OUTPUT);
  pinMode(solenoid3, OUTPUT);
  pinMode(lidSense1, INPUT);
  pinMode(lidSense2, INPUT);
  pinMode(resetButton, INPUT_PULLUP);
  digitalWrite(solenoid1, LOW);
  digitalWrite(solenoid2, HIGH);  
  digitalWrite(solenoid3, HIGH);  
}

void loop() {

//  EEPROM.write(addressInt, 0);
  int realTimeProm = EEPROM.readInt(addressInt);
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print((cycleCount));
  lid1 = digitalRead(lidSense1);
  lid2 = digitalRead(lidSense2);
  Serial.print("Sensor readings before opening:");
  Serial.print('\t');
  Serial.print(lid1);
  Serial.print('\t');
  Serial.print(lid2);
  Serial.print('\n');
  checkLid(lid1, lid2);
  
  if (lidError > 0) 
  {
    lcd.setCursor(0,1);
    lcd.print("Correlation flt");
    stopLoop();
   } else 
   {
    if (cycleCount % 2 == 0)
    {
      if (isLidOpen(lid1, lid2) == false)
      {
      openLid('L', lid1, lid2);
      lid1 = digitalRead(lidSense1);
      lid2 = digitalRead(lidSense2);
      Serial.print("Sensor readings after opening:");
      Serial.print('\t');
      Serial.print(lid1);
      Serial.print('\t');
      Serial.print(lid2);
      Serial.print('\n');
      
      closeLid();
      lid1 = digitalRead(lidSense1);
      lid2 = digitalRead(lidSense2);
      delay(50);
      checkOpen(lid1, lid2);
      }
    } else if (cycleCount % 2 == 1)
    {
      if(isLidOpen(lid1, lid2) == false)
      {
      openLid('R', lid1, lid2);
      closeLid();
      lid1 = digitalRead(lidSense1);
      lid2 = digitalRead(lidSense2);
      delay(50);
      checkOpen(lid1, lid2);
      }
      }
   }
   if(cycleCount >= 1000) 
   {
     lcd.clear();
     lcd.setCursor(6,0);
     lcd.print((cycleCount));
     stopLoop(); 
   }   
}

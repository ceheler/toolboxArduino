/*
* Written by Chris Eheler & logic by Tyler Gellinck
* New design 40 Gal TB test solenoid program
* Cycles the latches with solenoids and counts complete cycles
*/
#include "functions.h"

void setup() {
  Serial.begin(9600);                                           // Used for debugging 
  Wire.begin();                                                 // Used for LCD readout
  lcd.init();
  lcd.backlight();                                              // Start with the backlight on
  pinMode(solenoid1, OUTPUT);                                   // Set the Inputs and write default values
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

//  EEPROM.write(addressInt, 0);                                  // Uncomment this line and comment the rest out to clear the EEPROM address value
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print((cycleCount));                                        // Print cycle count on the display
  lid1 = digitalRead(lidSense1);                                  // Read sensor and print to serial the readings
  lid2 = digitalRead(lidSense2);
  Serial.print("Sensor readings before opening:");
  Serial.print('\t');
  Serial.print(lid1);
  Serial.print('\t');
  Serial.print(lid2);
  Serial.print('\n');
  checkLid(lid1, lid2);                                           // Check the lid for correlation 
  
  if (lidError > 0)                                               // If the lid does not correlate report and error and stop execution
  {
    lcd.setCursor(0,1);
    lcd.print("Correlation flt");
    stopLoop();
   } else 
   {
    if (cycleCount % 2 == 0)                                     // Use modulo so alternate between latches that are actuated
    {
      if (isLidOpen(lid1, lid2) == false)
      {
      openLid('L', lid1, lid2);                                 // Open left latch and verify open
      Serial.print("Sensor readings after opening:");           // Print to serial for debugging
      Serial.print('\t');
      Serial.print(lid1);
      Serial.print('\t');
      Serial.print(lid2);
      Serial.print('\n');
      
      closeLid();                                               // Close the lid
      lid1 = digitalRead(lidSense1);                            // Read sensors to validate closed
      lid2 = digitalRead(lidSense2);
      
      checkOpen(lid1, lid2);                                    // Check to ensure the lid closed
      }
    } else if (cycleCount % 2 == 1)                             // Wash rise repeat for other latch
    {
      if(isLidOpen(lid1, lid2) == false)
      {
      openLid('R', lid1, lid2);
      closeLid();
      Serial.print("Sensor readings after opening:");
      Serial.print('\t');
      Serial.print(lid1);
      Serial.print('\t');
      Serial.print(lid2);
      Serial.print('\n');
      delay(50);
      checkOpen(lid1, lid2);
      }
      }
   }
   if(cycleCount >= 1000)                                       // Once we hit 1000 stop the program
   {
     lcd.clear();
     lcd.setCursor(6,0);
     lcd.print((cycleCount));
     stopLoop(); 
   }   
}

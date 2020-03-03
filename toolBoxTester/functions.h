#include "globals.h"

/*
*  A infinite loop to stop the main arduino loop
*/
void stopLoop() {                                               
  for(;;)
  {
  }
}

/*
* Takes in 2 sensor values and compares them against eachother to validate correlation
*/

void checkLid(int checkVal1, int checkVal2) {
  if ( checkVal1 != checkVal2) 
  {
    lidError++;
  }
}

/*
* Takes in 2 sensors and determines if they are open (0) or closed (1) or faulty
*/

bool isLidOpen(int sensor1, int sensor2) {
  if (sensor1 && sensor2 == 0) 
  {
    return true;
  }
  else if (sensor1 && sensor2 != 0) 
  {
    return false;
  } else 
  {
      lcd.setCursor(2,1);
      lcd.print("Lid flt");
      stopLoop();
   }
}

/*
* Reads 2 sensors for error checking as well as reads in a char that is used to determine which latch is opened
*/

void openLid(char i, int sensor1, int sensor2) {
  if ( i == 'L')
  {
    Serial.print("Opening Left Latch:");              // For error checking
    Serial.print('\n');
    digitalWrite(solenoid2, LOW);                     // Actuates the air solenoid
    delay(650);                                       // Delayes then releases the solenoid
    digitalWrite(solenoid2, HIGH);
    delay(4000);                                      // Had to use two delays because this secion of code would skip intermittently 
    delay(4000);
    sensor1 = digitalRead(lidSense1);                 // Check lid to ensure it opened or report the error to the lcd
    sensor2 = digitalRead(lidSense2);
    if(sensor1 && sensor2 != 0 && cycleCount > 1)
    {
      lcd.setCursor(2,1);
      lcd.print("lid closed flt");
      stopLoop();
    }
    else 
    {
      if( cycleCount < cycleCountProm) 
      {
        cycleCount = cycleCountProm;
      }
        EEPROM.write(addressInt, cycleCount);         // Write to EEPROM so that when restarted the number is stored (not used) 
        cycleCount++;
    }
    delay(1000);
  }
  else if ( i == 'R')                                 // wash rinse repeat for the other latch
  {
    Serial.print("Opening Right Latch");
    Serial.print('\n');
    digitalWrite(solenoid3, LOW);
    delay(650);
    digitalWrite(solenoid3, HIGH);
    delay(2000);
    delay(2000);
    sensor1 = digitalRead(lidSense1);
    sensor2 = digitalRead(lidSense2);
    if(sensor1 && sensor2 != 0 && cycleCount > 1)
    {
      lcd.setCursor(2,1);
      lcd.print("lid closed flt");
      stopLoop();
    } else 
    {
      if( cycleCount < cycleCountProm) 
      {
        cycleCount = cycleCountProm;
      }
        EEPROM.write(addressInt, cycleCount);
        cycleCount++;
    }
  }
}

/*
* Takes no arguments and closes the lid
*/

void closeLid() {
  Serial.print("Closing Lid");                      // error checking 
  Serial.print('\n');
  digitalWrite(solenoid1, LOW);
  delay(1000);
  digitalWrite(solenoid1, HIGH);
  delay(1000);
  delay(1000);
  
}

/*
* If the lid is open report an error to the LCD
*/

void checkOpen(int sensor1, int sensor2) {
  if (isLidOpen(sensor1, sensor2) == true)
  {
    lcd.setCursor(2,1);
    lcd.print("Lid open flt");
    stopLoop(); 
  } 
}

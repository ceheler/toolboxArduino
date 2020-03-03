#include "globals.h"

void stopLoop() {
  for(;;)
  {
  }
}

void checkLid(int checkVal1, int checkVal2) {
  Serial.print("checkLid function running");
  Serial.print('\n');
  if ( checkVal1 != checkVal2) 
  {
    lidError++;
  }
}

bool isLidOpen(int sensor1, int sensor2) {
  Serial.print("isLidOpen funtion running");
  Serial.print('\n');
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
      lcd.print("Lid open flt");
      stopLoop();
   }
}

void openLid(char i, int sensor1, int sensor2) {
  if ( i == 'L')
  {
    Serial.print("Opening Left Latch:");
    Serial.print('\n');
    digitalWrite(solenoid2, LOW);
    delay(650);
    digitalWrite(solenoid2, HIGH);
    delay(4000);
    delay(4000);
    sensor1 = digitalRead(lidSense1);
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
        EEPROM.write(addressInt, cycleCount);
        cycleCount++;
    }
    delay(1000);
  }
  else if ( i == 'R')
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

void closeLid() {
  Serial.print("Closing Lid");
  Serial.print('\n');
  digitalWrite(solenoid1, LOW);
  delay(1000);
  digitalWrite(solenoid1, HIGH);
  delay(1000);
  delay(1000);
  
}

void checkOpen(int sensor1, int sensor2) {
  Serial.print("checkOpen Function Running");
  Serial.print('\n');
  if (isLidOpen(sensor1, sensor2) == true)
  {
    lcd.setCursor(2,1);
    lcd.print("Lid open flt");
    stopLoop(); 
  } 
}

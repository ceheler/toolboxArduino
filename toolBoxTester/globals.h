#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int solenoid1 = 53;                                  // Solenoid to close the toool box
const int solenoid2 = 51;                                  // Solenoid to open the tool box (left)
const int solenoid3 = 49;                                  // Solenoid to open the tool box (right)
const int lidSense1 = 39;                                  // Safety switch 1
const int lidSense2 = 35;                                  // Safety switch 2
const int resetButton = 43;                                // Input for reset of EEPROM mem
int lidError = 0;                                          // Counter of when the safety switches do not agree with eachother
int lid1 = 0;                                              // Variable to store read value of lidSense1
int lid2 = 0;                                              // Variable to store read value of lidSense2
int cycleCount = 0;
int addressInt = 32;
int cycleCountProm = EEPROM.readInt(addressInt);               // Count to keep track of cycling latches

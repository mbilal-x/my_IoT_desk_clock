/* SevSeg Counter Example
 
 Copyright 2020 Dean Reading
 
 This example demonstrates a very simple use of the SevSeg library with a 4
 digit display. It displays a counter that counts up, showing deci-seconds.
 */

#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(20);
}

void loop() {
  static unsigned long timer = millis();
  static int Seconds = 0;
  static int Minutes = 0;
  
  if (millis() - timer >= 1000) { 
    timer += 1000;
    Seconds++; // 1000 milliSeconds is equal to 1 Second
    
    if (Seconds == 60) { // Reset to 0 after counting for 1000 seconds.
      Seconds=0;
    }
    sevseg.setNumber(Seconds, 2);
  }
// minutes
    if (millis() - timer >= 60000) { 
    timer += 1000;
    Minutes++; // 60000 milliSeconds is equal to 1 Minute
    
    if (Minutes == 60) { // Reset to 0 after counting for 1000 seconds.
      Minutes=0;
    }
    sevseg.setNumber(Minutes, 3);
  }

  sevseg.refreshDisplay(); // Must run repeatedly
}

/// END ///

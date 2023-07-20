#include <SevSeg.h>

SevSeg sevseg; // Create an instance of the SevSeg library

const int buzzerPin = 2;

const int incrementButtonPin = 4;
const int decrementButtonPin = 5;
const int startButtonPin = 6;
const int modeButtonPin = 3;

const int buzzerDuration = 500; // 5 seconds

unsigned long timerDuration = 60000; // Default timer duration is 1 minute
unsigned long timerStartTime;
bool timerActive = false;

bool isClockMode = false; // Flag to indicate if the clock mode is active
bool prevModeButtonState = HIGH; // Previous state of the mode button for debouncing

void setup() {
  byte numDigits = 4; // Number of digits in the display
  byte digitPins[] = {A0, A1, A2, A3}; // Digit pins
  byte segmentPins[] = {7, 8, 9, 10, 11, 12, 13, A4};
  sevseg.setBrightness(90); // Segment pins
  
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  
  pinMode(buzzerPin, OUTPUT);
  pinMode(incrementButtonPin, INPUT_PULLUP);
  pinMode(decrementButtonPin, INPUT_PULLUP);
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(modeButtonPin, INPUT_PULLUP);
}

void loop() {
  // Check if the increment button is pressed
  if (digitalRead(incrementButtonPin) == LOW) {
    timerDuration += 60000; // Increment timer duration by 1 minute
    delay(250); // Delay to avoid button bounce
  }
  
  // Check if the decrement button is pressed
  if (digitalRead(decrementButtonPin) == LOW) {
    if (timerDuration >= 60000) {
      timerDuration -= 60000; // Decrement timer duration by 1 minute
    }
    delay(250); // Delay to avoid button bounce
  }
  
  // Check if the start button is pressed
  if (digitalRead(startButtonPin) == LOW) {
    timerActive = true;
    timerStartTime = millis(); // Store the start time of the timer
    delay(250); // Delay to avoid button bounce
  }
  
  // Check if the mode button is pressed
  int modeButtonState = digitalRead(modeButtonPin);
  if (modeButtonState == LOW && prevModeButtonState == HIGH) {
    isClockMode = !isClockMode; // Toggle the clock mode flag
    if (isClockMode) {
      // Clear the display when switching to clock mode
      sevseg.setNumber(0, 2);
    }
    delay(250); // Delay to avoid button bounce
  }
  prevModeButtonState = modeButtonState;
  
  // Check if the timer is active
  if (timerActive) {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - timerStartTime;
    
    // Check if the timer has finished
    if (elapsedTime >= timerDuration) {
      for (int i = 0; i < 5; i++) { // Sound the buzzer 5 times
        digitalWrite(buzzerPin, HIGH);
        delay(buzzerDuration);
        digitalWrite(buzzerPin, LOW);
        delay(buzzerDuration);
      }
      timerActive = false; // Timer is no longer active
      sevseg.setNumber(0, 2); // Set display to "00:00"
      sevseg.refreshDisplay();
    }
  }
  
  // Display time based on the current mode
  if (isClockMode) {
    // Get the current time in hours and minutes
    unsigned long currentTime = millis();
    int currentHours = currentTime / 3600000;
    int currentMinutes = (currentTime / 60000) % 60;
    
    // Combine hours and minutes for display (HHMM format)
    int displayTime = currentHours * 100 + currentMinutes;
    
    // Display current time on the 7-segment display
    sevseg.setNumber(displayTime, 2);
  } else {
    // Calculate remaining minutes and seconds
    int remainingMinutes = (timerDuration - (millis() - timerStartTime)) / 60000;
    int remainingSeconds = ((timerDuration - (millis() - timerStartTime)) / 1000) % 60;
    
    // Display remaining time on the 7-segment display
    sevseg.setNumber(remainingMinutes * 100 + remainingSeconds, 2);
  }
  
  // Refresh the display
  sevseg.refreshDisplay();
}

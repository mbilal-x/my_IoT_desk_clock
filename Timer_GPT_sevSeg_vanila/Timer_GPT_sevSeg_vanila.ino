#include <SevSeg.h>

SevSeg sevseg; // Create an instance of the SevSeg library

const int buttonPin = 2;
const int buzzerPin = 3;

const int incrementButtonPin = 4;
const int decrementButtonPin = 5;
const int startButtonPin = 6;

const int buzzerDuration = 500; // 5 seconds

unsigned long timerDuration = 0000; // Default timer duration is 1 minute
unsigned long timerStartTime;
bool timerActive = false;


void setup() {
  byte numDigits = 4; // Number of digits in the display
  byte digitPins[] = {A0, A1, A2, A3}; // Digit pins
  byte segmentPins[] = {7, 8, 9, 10, 11, 12, 13, A4};
  sevseg.setBrightness(90); // Segment pins
  
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(incrementButtonPin, INPUT_PULLUP);
  pinMode(decrementButtonPin, INPUT_PULLUP);
  pinMode(startButtonPin, INPUT_PULLUP);
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
  
  // Check if the timer is active
  if (timerActive) {
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - timerStartTime;
    
    // Check if the timer has finished
    if (elapsedTime >= timerDuration) {
      digitalWrite(buzzerPin, HIGH); // Activate the buzzer
      delay(buzzerDuration); // Sound the buzzer for the specified duration
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
      delay(buzzerDuration); // Sound the buzzer for the specified duration
      digitalWrite(buzzerPin, HIGH); // Activate the buzzer
      delay(buzzerDuration); // Sound the buzzer for the specified duration
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
      delay(buzzerDuration); // Sound the buzzer for the specified duration
      digitalWrite(buzzerPin, HIGH); // Activate the buzzer
      delay(buzzerDuration); // Sound the buzzer for the specified duration
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
      delay(buzzerDuration); // Sound the buzzer for the specified duration
      digitalWrite(buzzerPin, HIGH); // Activate the buzzer
      delay(buzzerDuration); // Sound the buzzer for the specified duration
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
      delay(buzzerDuration); // Sound the buzzer for the specified duration
      digitalWrite(buzzerPin, HIGH); // Activate the buzzer
      delay(buzzerDuration); // Sound the buzzer for the specified duration
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
      
      timerActive = false; // Timer is no longer active
    }
  }
  
  // Calculate remaining minutes and seconds
  int remainingMinutes = (timerDuration - (millis() - timerStartTime)) / 60000;
  int remainingSeconds = ((timerDuration - (millis() - timerStartTime)) / 1000) % 60;
  
  // Display minutes and seconds on the 7-segment display
  sevseg.setNumber(remainingMinutes * 100 + remainingSeconds, 2); // Set the number to display
  sevseg.refreshDisplay(); // Refresh the display
}
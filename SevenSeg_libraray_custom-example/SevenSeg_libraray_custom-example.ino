#include <SevenSeg.h>

SevenSeg disp(11,7,3,5,6,10,2);

const int numOfDigits=4;
int digitPins[numOfDigits]={12,9,8,13};

void setup() {
  disp.setCommonCathode();
  disp.setDigitPins(numOfDigits, digitPins);

}  

void loop() {

    disp.write(13.28);

}

// Best library so far. All keywords on github and in auto segessions.
#include "SPI.h"
#include "Adafruit_WS2801.h"

/*****************************************************************************
Example sketch for driving Adafruit WS2801 pixels!


  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683

  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
  
  Modified to run the sign for the Madagascar Institute Dueling Mechanical Bulls by Becky Stern!

*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
int dataPin  = 2;    // Yellow wire on Adafruit Pixels
int clockPin = 3;    // Green wire on Adafruit Pixels

char buff[]= "0000000000";
int  receivedNumber = 0;

//locations of LEDs on sign
int L[] = {29, 30, 31, 32, 33, 27, 34, 35, 36};
int O[] = {38, 39, 38, 40, 41, 43, 44, 45};
int S[] = {52, 51, 50, 49, 53, 54, 55, 59, 58, 57, 56};
int E[] = {72, 71, 70, 69, 68, 66, 64, 65, 60, 61, 62};
int R[] = {82, 83, 81, 75, 74, 73, 76, 77, 78, 79, 84, 85};
int rightArrow[] = {90, 92, 89, 93, 88, 94, 87, 95, 97, 96, 99, 103, 100, 101, 107, 106, 108, 109, 116, 110, 115, 111, 114, 112, 113};
int leftArrow[] = {22, 20, 23, 19, 24, 18, 25, 17, 16, 15, 13, 14, 12, 11, 9, 10, 8, 7, 0, 6, 1, 5, 2, 4, 3};

const int leftButtonPin = 5;
const int rightButtonPin = 4;
// Variables will change:
int rightButtonState;             // the current reading from the input pin
int leftButtonState;             // the current reading from the input pin
int lastRightButtonState = LOW;   // the previous reading from the input pin
int lastLeftButtonState = LOW;   // the previous reading from the input pin
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastLeftDebounceTime = 0;  // the last time the output pin was toggled
long LeftdebounceDelay = 50;    // the debounce time; increase if the output flickers'
long lastRightDebounceTime = 0;  // the last time the output pin was toggled
long RightdebounceDelay = 50;    // the debounce time; increase if the output flickers

// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(117, dataPin, clockPin);

// Optional: leave off pin numbers to use hardware SPI
// (pinout is then specific to each board and can't be changed)
//Adafruit_WS2801 strip = Adafruit_WS2801(25);

// For 36mm LED pixels: these pixels internally represent color in a
// different format.  Either of the above constructors can accept an
// optional extra parameter: WS2801_RGB is 'conventional' RGB order
// WS2801_GRB is the GRB order required by the 36mm pixels.  Other
// than this parameter, your code does not need to do anything different;
// the library will handle the format change.  Examples:
//Adafruit_WS2801 strip = Adafruit_WS2801(25, dataPin, clockPin, WS2801_GRB);
//Adafruit_WS2801 strip = Adafruit_WS2801(25, WS2801_GRB);

void setup() {
    
  strip.begin();
  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);
  Serial.begin(9600);
  // Update LED contents, to start they are all 'off'
  strip.show();
  
}

void loop() {
  
  int rightReading = digitalRead(rightButtonPin);
  //Serial.print("rightReading is ");
  //Serial.println(rightReading);
  
  if (rightReading != lastRightButtonState) {
    // reset the debouncing timer
    lastRightDebounceTime = millis();
  } 
  
  if ((millis() - lastRightDebounceTime) > RightdebounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    if (rightReading == 1){
       Serial.println("Loser is on the right");

      for (int i=0; i<3; i++){
        loserWipe(Color(255,0,0), 50);
        loserWipe(Color(128,0,0), 50);
        loserWipe(Color(0,0,0), 50);
        loserWipe(Color(255,0,0), 50);
        loserWipe(Color(128,0,0), 50);
        loserWipe(Color(0,0,0), 50);
        loserWipe(Color(255,0,0), 50);
        arrowWipeOn(Color(255,0,0), rightArrow);
        arrowWipeOn(Color(255,0,0), rightArrow);
        loserWipe(Color(0,0,0), 50);
        }
     }
  }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastRightButtonState = rightReading;
  
  int leftReading = digitalRead(leftButtonPin);
  //Serial.print("leftReading is ");
  //Serial.println(leftReading);
  if (leftReading != lastLeftButtonState) {
    // reset the debouncing timer
    lastLeftDebounceTime = millis();
  } 
  
  if ((millis() - lastLeftDebounceTime) > LeftdebounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    if (leftReading == 1){
      Serial.println("Loser is on the left");
      for (int i=0; i<3; i++){
        loserWipe(Color(255,0,0), 50);
      loserWipe(Color(128,0,0), 50);
      loserWipe(Color(0,0,0), 50);
      loserWipe(Color(255,0,0), 50);
      loserWipe(Color(128,0,0), 50);
      loserWipe(Color(0,0,0), 50);
      loserWipe(Color(255,0,0), 50);
      arrowWipeOn(Color(255,0,0), leftArrow);
      arrowWipeOn(Color(255,0,0), leftArrow);
      loserWipe(Color(0,0,0), 50);
      }
    }
  }
    // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastLeftButtonState = leftReading;
  
//standby behavior-- when nobody's losing
loserWalk(Color(255,0,0), 35);
arrowWipeBoth(Color(255,0,0));
arrowWipeBoth(Color(255,0,0));
arrowWipeOff(leftArrow);
arrowWipeOff(rightArrow);
}
  
void arrowWipeOn(uint32_t c, int TheArray[]) {
    for (int i=0; i < 37; i++) {
      
      if (i<25){
    strip.setPixelColor(TheArray[i], c);
//     Serial.print("Lighting up LED #");
 //    Serial.print(i);
 //    Serial.println();
      strip.show();
      delay(1);
      }
      
      if (i<31 && i>5){
      strip.setPixelColor(TheArray[i-6], Color(128,0,0));
     Serial.print("Dimming LED #");
     Serial.print(TheArray[i-6]);
     Serial.println();
      strip.show();
      delay(1);
      }
      
      if (i<37 && i>11){
      strip.setPixelColor(TheArray[i-12], 0);
     Serial.print("Shutting off LED #");
     Serial.print(TheArray[i-12]);
     Serial.println();
      strip.show();
      delay(1);
      }
  }
     
}

void arrowWipeBoth(uint32_t c) {
    for (int i=0; i <= 36; i++) {
      if (digitalRead(rightButtonPin) == 1 || digitalRead(leftButtonPin) == 1) {
        break;
      }
      if (i<=24){
    strip.setPixelColor(rightArrow[i], c);
    strip.setPixelColor(leftArrow[i], c);
      strip.show();
      delay(1);
      }
      
      if (i<31 && i>5){
      strip.setPixelColor(rightArrow[i-6], Color(128,0,0));
      strip.setPixelColor(leftArrow[i-6], Color(128,0,0));
      strip.show();
      delay(1);
      }
   
      if (i<=36 && i>11){
      strip.setPixelColor(rightArrow[i-12], 0);
      strip.setPixelColor(leftArrow[i-12], 0);
      strip.show();
      delay(1);
      }
  }
    
     
}

void arrowWipeOff(int TheArray[]) {
    for (int i=0; i < 25; i++) {
      
    strip.setPixelColor(TheArray[i], 0);
//     Serial.print("Shutting off LED #");
//     Serial.print(i);
//     Serial.println();
     
  }
  strip.show();
      delay(1);
} 

void loserWalk(uint32_t c, uint8_t wait) {
for (int i=0; i <= 13; i++) {
    if (digitalRead(rightButtonPin) == 1 || digitalRead(leftButtonPin) == 1) {
        break;
      }
  if (i<=8){
  strip.setPixelColor(L[i], c);
  }
  if (i<=13 && i>=4){
    strip.setPixelColor(L[i-4], 0);
  }
  strip.show();
  delay(wait);
}
for (int i=0; i <= 11; i++) {
  if (digitalRead(rightButtonPin) == 1 || digitalRead(leftButtonPin) == 1) {
        break;
      }
  if (i<=7){
  strip.setPixelColor(O[i], c);
  }
  if (i<=11 && i>=4){
    strip.setPixelColor(O[i-4], 0);
  }
  strip.show();
  delay(wait);
}

for (int i=0; i <= 14; i++) {
 if (digitalRead(rightButtonPin) == 1 || digitalRead(leftButtonPin) == 1) {
        break;
      }
      if (digitalRead(leftButtonPin) == 1) {
        break;
      }
  if (i<=10){
  strip.setPixelColor(S[i], c);
}
  if (i<=14 && i>=4){
    if (digitalRead(rightButtonPin) == 1 || digitalRead(leftButtonPin) == 1) {
        break;
      }
    strip.setPixelColor(S[i-4], 0);
  }
  strip.show();
  delay(wait);
}

for (int i=0; i <= 14; i++) {
      if (digitalRead(rightButtonPin) == 1 || digitalRead(leftButtonPin) == 1) {
        break;
      }
  if (i<=10){
  strip.setPixelColor(E[i], c);
  }
  if (i<=14 && i>=4){
    strip.setPixelColor(E[i-4], 0);
  }
  strip.show();
  delay(wait);
}

for (int i=0; i <= 15; i++) {
      if (digitalRead(rightButtonPin) == 1) {
        break;
      }
      if (digitalRead(leftButtonPin) == 1) {
        break;
      }
  if (i<=11){
    strip.setPixelColor(R[i], c);
  }
  if (i<=15 && i>=4){
    strip.setPixelColor(R[i-4], 0);
  }
  strip.show();
  delay(wait);
}
}

void loserWipe(uint32_t c, uint8_t wait) {
    strip.setPixelColor(29, c);
    strip.setPixelColor(30, c);
    strip.setPixelColor(40, c);
    strip.setPixelColor(50, c);
    strip.setPixelColor(51, c);
    strip.setPixelColor(69, c);
    strip.setPixelColor(70, c);
    strip.setPixelColor(71, c);
    strip.setPixelColor(73, c);
    strip.setPixelColor(76, c);
    strip.show();
    delay(1);
    
    strip.setPixelColor(31, c);
    strip.setPixelColor(39, c);
    strip.setPixelColor(41, c);
    strip.setPixelColor(49, c);
    strip.setPixelColor(52, c);
    strip.setPixelColor(68, c);
//    strip.setPixelColor(72, c);
    strip.setPixelColor(74, c);
    strip.setPixelColor(77, c);
    strip.show();
    delay(1);
    
//    strip.setPixelColor(28, c);
    strip.setPixelColor(32, c);
//    strip.setPixelColor(37, c);
    strip.setPixelColor(38, c);
    strip.setPixelColor(41, c);
//    strip.setPixelColor(42, c);
    strip.setPixelColor(43, c);
//    strip.setPixelColor(48, c);
    strip.setPixelColor(53, c);
//    strip.setPixelColor(67, c);
    strip.setPixelColor(66, c);
    strip.setPixelColor(64, c);
//    strip.setPixelColor(80, c);
    strip.setPixelColor(75, c);
    strip.setPixelColor(78, c);
    strip.setPixelColor(79, c);
    strip.show();
    delay(1);
    
    strip.setPixelColor(33, c);
    strip.setPixelColor(36, c);
    strip.setPixelColor(46, c);
    strip.setPixelColor(44, c);
    strip.setPixelColor(56, c);
    strip.setPixelColor(54, c);
    strip.setPixelColor(55, c);
    strip.setPixelColor(65, c);
    strip.setPixelColor(81, c);
    strip.setPixelColor(84, c);
    strip.show();
    delay(1);
    
    strip.setPixelColor(27, c);
    strip.setPixelColor(34, c);
    strip.setPixelColor(35, c);
    strip.setPixelColor(45, c);
    strip.setPixelColor(57, c);
    strip.setPixelColor(58, c);
    strip.setPixelColor(59, c);
    strip.setPixelColor(60, c);
    strip.setPixelColor(61, c);
    strip.setPixelColor(62, c);
    strip.setPixelColor(82, c);
    strip.setPixelColor(83, c);
    strip.setPixelColor(85, c);
    strip.show();
    delay(1);
     
}

void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint32_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      
    strip.setPixelColor(i, c);
     Serial.print("Lighting up LED #");
     Serial.print(i);
     Serial.println();
      strip.show();
      delay(wait);
  }
}

void colorChase(uint32_t c, uint32_t wait) {
  int i;
  
  for (i=54; i < strip.numPixels(); i++) {
      
    strip.setPixelColor(i, c);
    strip.setPixelColor(i-1, 0);
     Serial.print("Lighting up LED #");
     Serial.print(i);
     Serial.println();
      strip.show();
      delay(wait);
  }
}

void letterChase(uint32_t c, uint32_t wait, int TheArray[]) {
  int i;
  
  for (i=0; i < (sizeof(TheArray)/sizeof(int)) - 1; i++) {
      
    strip.setPixelColor(TheArray[i], c);
    strip.setPixelColor(TheArray[i-1], 0);
     Serial.print("Lighting up LED #");
     Serial.print(i);
     Serial.println();
      strip.show();
      delay(wait);
  }
}

void colorNumber(uint32_t c, uint8_t whichLED) {
      strip.setPixelColor(whichLED, c);
      strip.show();
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

#include <Adafruit_CircuitPlayground.h>

#include <Adafruit_NeoPixel.h>

#include <Wire.h>
#include <SPI.h>

// Adjust this number for the sensitivity of the 'click' force
// this strongly depend on the range! for 16G, try 5-10
// for 8G, try 10-20. for 4G try 20-40. for 2G try 40-80
#define CLICKTHRESHHOLD 90
int red[7] = {255, 0, 0, 238, 244, 66, 255};
int green[7] = {0, 255, 0, 66, 215, 244, 255};
int blue[7] = {0, 0, 255, 244, 66, 235, 255};
int color = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(432, 6);

void setup(void) {
  CircuitPlayground.begin();
  Serial.begin(9600);

  strip.begin();
  strip.clear();
  strip.show();
  
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
  
  // 0 = turn off click detection & interrupt
  // 1 = single click only interrupt output
  // 2 = double click only interrupt output, detect single click
  // Adjust threshhold, higher numbers are less sensitive
  CircuitPlayground.setAccelTap(2, CLICKTHRESHHOLD);
  
  // have a procedure called when a tap is detected
  attachInterrupt(digitalPinToInterrupt(7), tapTime, FALLING);
}

void tapTime(void) {
  Serial.println("tap!");
  strip.setBrightness(255);
  for(int i = 0; i < 432; i++){
    strip.setPixelColor(i, red[color], green[color], blue[color]);
  }
  strip.show();
  color = (color+1)%7;
  
  for(int j = 240; j>=0; j=j-20){
    strip.setBrightness(j);
    strip.show();
    delay(2);
  }
}

void loop() {

}

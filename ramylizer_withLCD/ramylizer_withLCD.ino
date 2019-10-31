#include <SoftwareSerial.h>

// ramylizer_withLCD.ino
// Created by: Samuel Bechara, PhD
// Created on: 21 October 2019

// These are the Arduino pins required to create a software seiral
//  instance. We'll actually only use the TX pin.
const int softwareTx = 8;
const int softwareRx = 7;

// Pins and Initialization
const int analogPin = 0;
float sensorReading = 0;
float V_rl = 0;
float ppm = 0;
float bac = 0;

SoftwareSerial s7s(softwareRx, softwareTx);

void setup() {
  Serial.begin(9600);
  s7s.begin(9600);
  s7s.write(0x76);
  
  // Subfunction to set decimal place on LCD
  setDecimals(0b00000001);
}

void loop() {
  // Get sensor value
  sensorReading = analogRead(analogPin);
  
  // Convert to sensor voltage
  V_rl = sensorReading * 5 / 1024;

  // Calculate PPM based off of curve on spec sheet
  ppm = 4.62986*exp(1.05313*V_rl);

  // Calculate BAC
  bac = ppm/2600;

  // Sensor floats around a little bit...this is a cheat
  // Only register BAC if > 0.01
  if (bac<=0.01){
    bac = 0.00;
  }
  
  s7s.print(bac);
  // Serial print commands for testing purposes
  // Serial.println(sensorReading);
  // Serial.println(V_rl);
  // Serial.println(ppm);
  // Serial.println(bac);
  delay(500);
}

// Turn on any, none, or all of the decimals.
//  The six lowest bits in the decimals parameter sets a decimal 
//  (or colon, or apostrophe) on or off. A 1 indicates on, 0 off.
//  [MSB] (X)(X)(Apos)(Colon)(Digit 4)(Digit 3)(Digit2)(Digit1)
void setDecimals(byte decimals)
{
  s7s.write(0x77);
  s7s.write(decimals);
}

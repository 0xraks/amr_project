#include<Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>


// ENCODER PIN DECLERATIONS
// Left A and Right A should be interrupt pins
// In mega the interrupt pins are 2,3,18,19,20,21
// In uno the interrupt pins are 2,3



#define LeftA 2
#define LeftB 4
#define RightA 3
#define RightB 5


long counts = 0;
long counts2 = 0;

void readEncoder() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{
  if (digitalRead(LeftB) == digitalRead(LeftA) )
  {
    counts = counts - 1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts = counts + 1;
  }
    Serial.println(counts+" and "+counts2);
}

void readEncoder2() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{
  if (digitalRead(RightB) == digitalRead(RightA) )
  {
    counts2 = counts2 - 1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts2 = counts2 + 1;
  }
  Serial.println(counts+" and "+counts2);
}


void setup() {
  pinMode(LeftA, INPUT); //initialize Encoder Pins
  pinMode(LeftB, INPUT);
  digitalWrite(LeftA, LOW); //initialize Pin States
  digitalWrite(LeftB, LOW);
  pinMode(RightA, INPUT); //initialize Encoder Pins
  pinMode(RightB, INPUT);
  digitalWrite(RightA, LOW); //initialize Pin States
  digitalWrite(RightB, LOW);
  attachInterrupt(digitalPinToInterrupt(LeftA), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RightA), readEncoder2, CHANGE);
  Serial.begin(115200);
}

void loop() {



}


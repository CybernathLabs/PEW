/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;

int bRead = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(7,INPUT_PULLUP);
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop() {
  
  if (bRead == HIGH && digitalRead(7) == LOW) {
   
      irsend.sendNEC(0x2107EE11, 32);
      digitalWrite(13,HIGH);
      delay(40);
      digitalWrite(13,LOW);
      Serial.println("boop");
  }
  bRead = digitalRead(7);
  delay(50);
}

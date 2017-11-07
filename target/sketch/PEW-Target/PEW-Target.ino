#include <Servo.h>
#include <IRremote.h>
#include <Wire.h>

// DF95E263 is the corrupted code being returned by some of the inputs.

Servo myservo;  // create servo object to control a servo
IRrecv irrecv(4);
decode_results results;
int dipPins[] = {A2, A1, A0}; //DIP Switch Pins


int triggered = 0;

int nodeAddress = 0;

void setup() {
  Serial.begin(57600);
  
  pinMode(4,INPUT);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);

  nodeAddress = address();
  Serial.print("Node Address: ");
  Serial.println(nodeAddress);

  Wire.begin(nodeAddress);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  
  myservo.attach(9);
  irrecv.enableIRIn();
  
  
  resetTarget();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if(results.value == 0x2107EE11 || results.value == 0xDF95E263){
      if(triggered == 0){
        triggerTarget();
        // This code was added to Auto-reset the targets, ignoring the i2c signals (or lack thereof)
        delay(2000);
        resetTarget();
      }
    }
    irrecv.resume();
  }

  if(triggered == 2){
    resetTarget();
  }
}

void resetTarget(){
  myservo.write(180);
  delay(750);
  myservo.write(50);
  delay(250);
  triggered = 0;
}

void triggerTarget(){
  triggered = 1;
  myservo.write(20);
  delay(500);
  myservo.write(50);
  delay(250);

}
//Create Address from DIP Switch (4 positions used)
byte address(){
 int i,j=0;
 
 //Get the switches state
 for(i=0; i<3; i++){
  int v = digitalRead(dipPins[i]);
  if(v == 1){ v = 0;}else{v = 1;}
 j = (j << 1) | v;   // read the input pin
 }
 return j; //return address
}

// Return data when the master requests it.
void requestEvent()
{
  Wire.write(triggered); // respond with message of 1 byte
                       // as expected by master
}

void receiveEvent(int howMuch){
  Serial.println("Resetting.");
  int d = Wire.read();
  if(d == 1){
    triggered=2;
  }

}


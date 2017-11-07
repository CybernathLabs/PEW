#include <Wire.h>

byte targets[10] = {};
int nTargets;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Wire.begin();
  Serial.println("Scanning for Attached Targets");
  scanForTargets();
  Serial.print(nTargets);
  Serial.println(" Targets Found");
}

void loop() {
  // put your main code here, to run repeatedly:
  int triggered = 0;
  Serial.print("\\u ");
  for(int i=0; i < nTargets; i++){
    Wire.requestFrom(int(targets[i]), 1);
    int c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    if(c == 1) triggered++;
  }
  if(triggered == nTargets){
    delay(2000);
    resetAllTargets();
  }
  Serial.println();
  
  delay(1000);
}

void resetAllTargets(){
  Serial.println("Resetting All Targets");
  
  for(int i=0; i < nTargets; i++){
    Serial.println(targets[i]);
    Wire.beginTransmission(targets[i]);
    Wire.write(0x01);
    Wire.endTransmission();
    delay(500);
  }
  
}

void scanForTargets(){
  byte error,address;
  nTargets = 0;
  
  for(address = 1; address < 16; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("!");
      targets[nTargets] = address;
 
      nTargets++;
    }  
  }
  if (nTargets == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n"); 
}


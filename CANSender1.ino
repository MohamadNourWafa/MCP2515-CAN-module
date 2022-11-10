// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>
#include <EasyUltrasonic.h>
#define TRIGPIN 5 
#define ECHOPIN 5
EasyUltrasonic ultrasonic;
void setup() {
  Serial.begin(9600);
  ultrasonic.attach(TRIGPIN, ECHOPIN);
  while (!Serial);

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  float distanceCM = ultrasonic.getDistanceCM();
  
  
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data


  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending extended packet ... ");

  CAN.beginExtendedPacket(0x036);
  CAN.write(distanceCM*5);
  
  
  
  CAN.endPacket();
 

  Serial.println("done");

  delay(100);
}

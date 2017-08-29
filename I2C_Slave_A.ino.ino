// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
byte state18 ;
byte statec ;
int myInts[6];

void setup() {
  Wire.begin(0x38);                // join i2c bus with address 0111000
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}



// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    byte numc = Wire.read(); // receive byte as a character
    for (byte i = 0; i < 8; i++) {
      byte statec = bitRead(numc, i);
      {
        //Serial.print(statec); // print the character
      }

    }
    if (Wire.available() == 18 )
    {
      myInts[0] = numc;
    }
    else if (Wire.available() == 19 )
    {
      myInts[1] = numc;
    }
    else if (Wire.available() == 20 )
    {
      myInts[2] = numc;
    }
    else if (Wire.available() == 21 )
    {
      myInts[3] = numc;
    }

    //Serial.print(";");
    //  Serial.print(Wire.available());
    //  Serial.print(";");
    //   Serial.print(numc);
    //   Serial.write( '\n' ); //  Carriage Return
  }
  byte numx = Wire.read();    // receive byte as an integer
  for (byte i = 0; i < 8; i++) {
    byte statex = bitRead(numx, i);
    //  Serial.print(statex);
  }
  // print the character
  // Serial.print(";");
  // Serial.print(Wire.available());
  //  Serial.write( '\n' ); //  Carriage Return
}
void loop() {
  delay(5000);
  //Serial.print(myInts[0]);      // print the character

  for (byte p = 0; p < 5; p++) {
    Serial.print(myInts[p]);
    Serial.write( '\n' ); //  Carriage Return
  }
}

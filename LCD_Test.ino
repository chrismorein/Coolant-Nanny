/* Test library for Display from PHILIPS Navigator F 505-2
Display is controlled by 3 pcs. PCF8576 chips over I2C bus.

Address by the Wiring-library in Arduino.

Remember, when doing a Wire.beginTransmission, only input 7 bits data and omit the LSB digit
(Wiring takes care of the R/W bit itself)
*/

#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  
  Wire.beginTransmission(B0111000);  //adress the I2C-controller.
  Wire.write(B11001000);  //MODE SET (Command)(10)(LowPower)(Enable)(Bias)(Mux)
                         //         (1)          (0)       (1)     (1/3) (1:4)
  Wire.write(B11100000);  //Device select (Command)(1100)(A2 A1 A0)
                         //              (1)            (0  0  0 )
  Wire.endTransmission(); 
}

void loop()
{ 
  
  Wire.beginTransmission(B0111000);  //address the I2C-controller.
  Wire.write(B11100000);  //Device select (Command)(1100)(A2 A1 A0)
                          //              (1)            (0  0  0 )
  Wire.write(B00000000);  //Data pointer points at adress "000000"
  
  Wire.write(B00000111);  //Display 1: 7 "HR GL", 6 "Setup", 5 "CAL", 4 "P", 3 ":", 210 "Main Digit 4"
  Wire.write(B11111111);  //Display 2: 7654 "Main Digit 4", 3210 "Main Digit 3"
  Wire.write(B11110000);  //Display 3: 7654 "Main Digit 3", 3 "FP", 2 "C", 1 "F", 0 "M D"
  Wire.write(B11111111);  //Display 4: 76543210 "Main Digit 2"
  Wire.write(B00001111);  //Display 5: 7 "ATC", 6 "V/V", 5 "%", 4 "%0", 3210 Main Digit 1 
  Wire.write(B11110000);  //Display 6: 7654 Main Digit 1, 3 "nD", 2 "%Brix", 1 "20", 0 "ppt"
  Wire.write(B10000100);  //Display 7: 7 "g"m 6 "PSU", 5 "SG", 4 "Baume", 3 "mL" ,2 "Temp F", 1 "Temp C", 0 "Moles/L"
  Wire.write(B00000000);  //Display 8
  Wire.write(B00000000);  //Display 9
  Wire.write(B00000000);  //Display 10
  Wire.write(B00000000);  //Display 11
  Wire.write(B00001111);  //Display 12
  Wire.write(B10111111);  //Display 13
  Wire.write(B00110111);  //Display 14
  Wire.write(B00000000);  //Display 15
  Wire.write(B00000000);  //Display 16
  Wire.write(B00000000);  //Display 17
  Wire.write(B00000000);  //Display 18
  Wire.write(B00000000);  //Display 19
  Wire.write(B00000000);  //Display 20
  
  Wire.endTransmission();

  //--------------------------------------------------------------------------- 
 
  delay(20);
}

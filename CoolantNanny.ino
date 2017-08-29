
//This code will output data to the Arduino serial monitor.
//Type commands into the Arduino serial monitor to control the pH circuit.
//"R" for Sensor Read

#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>                           //we have to include the SoftwareSerial library, or else we can't use it
#include <LiquidCrystal.h>
#include <TimerOne.h>
#include "LcdKeypad.h"
#include "MenuData.h"

#define rx 2                                          //define what pin rx is going to be
#define tx 3                                          //define what pin tx is going to be
#define ONE_WIRE_BUS 11                                // Data wire is plugged into pin 4 on the Arduino
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

SoftwareSerial myserial(rx, tx);                      //define how the soft serial port is going to work
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

float CurrentMilli;
String inputstring = "";                              //a string to hold incoming data from the PC
String jsonString = "";                              //a string to hold incoming data from the PC
String sensorstring = "";                             //a string to hold the data from the Atlas Scientific product
String tempstring = "";                              //a string to hold incoming data from the PC
boolean input_string_complete = false;                //have we received all the data from the PC
boolean sensor_string_complete = false;               //have we received all the data from the Atlas Scientific product
float pH;                                             //used to hold a floating point number that is the pH
String pH_Status = "";                                 //a string to hold High or Low
int lcd_key     = 0;
int adc_key_in  = 0;


int read_LCD_buttons() {              // read the buttons
  adc_key_in = analogRead(0);       // read the value from the sensor

  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  // We make this the 1st option for speed reasons since it will be the most likely result

  if (adc_key_in > 1000) return btnNONE;

  // For V1.1 us this threshold
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT;

  return btnNONE;                // when all others fail, return this.
}



void setup() {                                        //set up the hardware
  Serial.begin(9600);                                 //set baud rate for the hardware serial port_0 to 9600
  myserial.begin(9600);
  inputstring.reserve(10);                            //set aside some bytes for receiving data from the PC
  sensorstring.reserve(30);                           //set aside some bytes for receiving data from Atlas Scientific product
  sensors.begin();                                    // Start up the temperture library
  lcd.begin(16, 2);               // start the library
  lcd.setCursor(0, 0);            // set the LCD cursor   position
  lcd.print("Coolant Nanny");  // print a simple message on the LCD
  lcd.setCursor(0, 1);
  lcd.print("coolantnanny.com");  // print a simple message on the LCD
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);            // set the LCD cursor   position
  lcd.print("Press Select to");  // print a simple message on the LCD
  lcd.setCursor(0, 1);
  lcd.print("take reading...");  // print a simple message on the LCD

  backLightOn();
  Timer1.initialize();
  Timer1.attachInterrupt(lcdBacklightISR, 500);
  setBacklightBrightness(1);
}


void serialEvent() {                                  //if the hardware serial port_0 receives a char
  inputstring = Serial.readStringUntil(13);           //read the string until we see a <CR>
  input_string_complete = true;                       //set the flag used to tell if we have received a completed string from the PC
}


void loop() {                                         //here we go...
  

  lcd.setCursor(0, 1);            // move to the begining of the second line
  lcd_key = read_LCD_buttons();   // read the buttons

  switch (lcd_key) {              // depending on which button was pushed, we perform an action

    case btnRIGHT: {            //  push button "RIGHT" and show the word on the screen
        lcd.clear();
        lcd.print("RIGHT ");
        break;
      }
    case btnLEFT: {
        lcd.clear();
        lcd.print("LEFT   "); //  push button "LEFT" and show the word on the screen
        break;
      }
    case btnUP: {
        lcd.clear();
        lcd.print("UP    ");  //  push button "UP" and show the word on the screen
        break;
      }
    case btnDOWN: {
        lcd.clear();
        lcd.print("DOWN  ");  //  push button "DOWN" and show the word on the screen
        break;
      }
    case btnSELECT: {
        //lcd.print("SELECT");  //  push button "SELECT" and show the word on the screen
        backLightOn();
        lcd.clear();
        lcd.print("SELECT");
        inputstring = "R";
        input_string_complete = true;
        break;
      }
    case btnNONE: {
        lcd.print("");  //  No action  will show "None" on the screen
        break;
      }
  }

  if (input_string_complete) {                        //if a string from the PC has been received in its entirety
    delay(100);
    if (inputstring == "R" or "r") {
      sensors.requestTemperatures();                    // Send the command to get temperatures
      tempstring = sensors.getTempCByIndex(0);
      myserial.print("T,");                            //send that string to the Atlas Scientific product
      myserial.print(tempstring);                      //send that string to the Atlas Scientific product
      myserial.print('\r');                             //add a <CR> to the end of the string
      lcd.clear();
      lcd.print("Reading...");
      delay(250);
      lcd.clear();
      lcd.print("Reading...|");
      delay(250);
      lcd.clear();
      lcd.print("Reading...-");
      delay(250);
      lcd.clear();
      lcd.print("Reading...|");
      delay(250);
      lcd.clear();
      lcd.print("Reading...-");
      delay(250);
      lcd.clear();
      lcd.print("Reading...|");
      delay(250);
      lcd.clear();
      lcd.print("Reading...-");
      delay(250);
      lcd.clear();
      ;
      myserial.print(inputstring);                      //send that string to the Atlas Scientific product
      myserial.print('\r');                             //add a <CR> to the end of the string
      inputstring = "";                                 //clear the string
      lcd.print("Reading...|");
      delay(250);
      lcd.clear();
      lcd.print("Reading...-");
      delay(250);
      lcd.clear();
      lcd.print("Reading...|");
      delay(250);
      lcd.clear();
      lcd.print("Reading...-");
      delay(250);
      lcd.clear();
      lcd.print("Reading...|");
      input_string_complete = false;                    //reset the flag used to tell if we have received a completed string from the PC
    }

    else {
      myserial.print(inputstring);                  //send that string to the Atlas Scientific product
      myserial.print('\r');                             //add a <CR> to the end of the string
      inputstring = "";                                 //clear the string
      input_string_complete = false;                    //reset the flag used to tell if we have received a completed string from the PC
    }
  }
  if (myserial.available() > 0) {                     //if we see that the Atlas Scientific product has sent a character
    char inchar = (char)myserial.read();              //get the char we just received
    sensorstring += inchar;                           //add the char to the var called sensorstring
    if (inchar == '\r') {                             //if the incoming character is a <CR>
      sensor_string_complete = true;                  //set the flag
    }
  }


  if (sensor_string_complete == true) {               //if a string from the Atlas Scientific product has been received in its entirety
    if (isdigit(sensorstring[0])) {                   //if the first character in the string is a digit
      pH = sensorstring.toFloat();                    //convert the string to a floating point number so it can be evaluated by the Arduino
      if (pH >= 8.0) {                                //if the pH is greater than or equal to 7.0
        pH_Status = "HIGH";                              //print "high" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
      if (pH < 8.0 and pH >7.0) {                              //if the pH is less than or equal to 6.999
        pH_Status = "IDEAL";                               //print "low" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
      if (pH <= 7.0) {                              //if the pH is less than or equal to 6.999
        pH_Status = "LOW";                               //print "low" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
    }

    if (isdigit(sensorstring[0])) {
      String jsonString = "{\"PH\":\"";                // form a JSON-formatted string:
      jsonString += sensorstring;
      jsonString += "\",\"PH_STATUS\":\"";
      jsonString += pH_Status;
      jsonString += "\",\"TEMP\":\"";
      jsonString += tempstring;
      jsonString += "\"}";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("pH: ");
      lcd.setCursor(4, 0);
      lcd.print(sensorstring);
      lcd.setCursor(11, 0);
      lcd.print(pH_Status);
      lcd.setCursor(0, 1);
      lcd.print("Temp: ");
      lcd.setCursor(6, 1);
      lcd.print(tempstring);
      lcd.setCursor(12, 1);
      lcd.print("C");
      Serial.println(jsonString);
      tempstring = "";                               //clear the string
      pH_Status = "";                                //clear the string
      delay(10000);
      lcd.setCursor(0, 0);
      lcd.print("Press Select to ");
      lcd.setCursor(0, 1);
      lcd.print("take reading...");
      backLightOff();
    }
    else if (sensorstring.startsWith("*OK"))
    {
    }
    else {
      String jsonString = "{\"IC_STATUS\":\"";                // form a JSON-formatted string:
      jsonString += sensorstring;
      jsonString += "\"}";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(sensorstring);
      Serial.println(jsonString);

    }

    sensorstring = "";                             //clear the string
    jsonString = "";                               //clear the string
    sensor_string_complete = false;                //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
  }
}



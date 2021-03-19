// Device Information : AVR MEGA4809 ARDUINO NANO EVERY
// LCD Size 20 x 4
// Recive the BYTEdate and Sendback on same Serial port (BYTEdata + 0x01) 

#include <LiquidCrystal.h>

#define SERIAL_BAUD_RATE 9800
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
// set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
// Print a message to the LCD. for check LCD Connection.
  lcd.print("HELLO!_HELLO!_HELLO!");
  delay(200);
  lcd.setCursor(0, 1);  // (COL, ROW ) 
  lcd.print("HELLO!_HELLO!_HELLO!");
  delay(200);
  lcd.setCursor(0, 2);  
  lcd.print("Sereal_Byte_Monitor_");
  delay(200);
  lcd.setCursor(0, 3);   
  lcd.print("HELLO!_HELLO!_HELLO!");
  delay(1000);
// Init the LCD for Standby
  lcd.clear();
  lcd.setCursor(0, 0);   
  lcd.print("RCV :");
  lcd.setCursor(0, 2);  
  lcd.print("SEND:");
// start serial port and set BPS:
  Serial.begin(SERIAL_BAUD_RATE);
}

void loop() {
// if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    delay(300);  // Wating for all data comming.
    int SerialReciveByteCount = Serial.available();
//Recive Data
    int ArrayReadDataByte[SerialReciveByteCount];
    byte inByte = 0;
    String LcdPrintString = "";
    for (int i=0; i < SerialReciveByteCount ; i++){
      inByte = Serial.read();
      LcdPrintString = LcdPrintString + ":" + String(inByte, HEX);
      ArrayReadDataByte[i] = inByte + 0x01;
    }
    lcd.clear();
    lcd.setCursor(0, 0);  // (COL, ROW ) 
    lcd.print("RCV :");
    lcd.setCursor(0, 1);  
    lcd.print(LcdPrintString);
//Send Back Data
    LcdPrintString = "";
    for (int i=0; i < SerialReciveByteCount; i++){
      LcdPrintString = LcdPrintString + ":" + String(ArrayReadDataByte[i], HEX);
      Serial.write(ArrayReadDataByte[i]); //Send back data to same SerilPort witn BYTE
    }
    lcd.setCursor(0, 2);
    lcd.print("SEND:");
    lcd.setCursor(0, 3);
    lcd.print(LcdPrintString);
  }
}
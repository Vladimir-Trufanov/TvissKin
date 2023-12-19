/* ========================================================================= */
/*   I2C-Scanner.ino                                                         */
/*   (c) 2023-12-19 Труфанов Владимир                                        */
/*                                                                           */
/*   Description:            Программа для сканирования адресов I2C на плате */
/*                                 Arduino Nano 33 BLE Sense или Arduino UNO */
/* ========================================================================= */

/** 
 *  Для доступа к I2C используется библиотека Wire: #include <Wire.h>. 
 * (дополнительная информация о библиотеке Wire на официальном сайте 
 * по адресу https://www.arduino.cc/en/Reference/Wire)
**/
 
#include <Wire.h>

void setup() 
{
   Serial.begin(115200);
   Wire.begin();
   Serial.println("\nI2C Scanner");
}
void loop() 
{
   byte error, address;
   int nDevices;
   Serial.println("Scanning...");
   
   nDevices = 0;
   for(address = 1; address < 127; address++) 
   {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
      if (error == 0) 
      {
          Serial.print("I2C device found at address 0x");
          if (address < 16) Serial.print("0");
          Serial.println(address, HEX);
          nDevices++;
      }
      else 
      if (error == 4) 
      {
         Serial.print("Unknown error at address 0x");
         if (address < 16) Serial.print("0");
         Serial.println(address, HEX);
      }
   }
   
   if (nDevices == 0) Serial.println("No I2C devices found");
   else Serial.println("done");
   delay(5000);
}

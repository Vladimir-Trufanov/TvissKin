/* ========================================================================= */
/*                                                                           */
/*   AnalogSensor.ino                                                        */
/*   (c) 2023-12-16 Труфанов Владимир                                        */
/*                                                                           */
/*   Description:         примеры работы с аналоговыми датчиками температуры */
/*       (температуры и влажности) на Arduino UNO, Arduino Nano 33 BLE Sense */
/* ========================================================================= */

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

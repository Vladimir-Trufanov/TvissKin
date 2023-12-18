/* ========================================================================= */
/*   Dht11v2.ino                                                             */
/*   (c) 2023-12-12 Труфанов Владимир                                        */
/*                                                                           */
/*   Description:      скетч для иллюстрации совместного подключения на двух */
/*      макетных платах LCD1602a и DHT11 (с библиотекой версии DHT11-2.0.0). */
/* ========================================================================= */

// Подключаем библиотеку версии DHT11-2.0.0
#include "DHT11.h"
// Подключаем штатную библиотеку LiquidCrystal.h
#include <LiquidCrystal.h>

// Создаем объект дисплея на заданных контактах
//               [RS, E, D4, D5, D6, D7] 
LiquidCrystal lcd (3, 4,  5,  6,  7,  8);   
// Создаем объект датчика DHT11 на 2 пине
// - For Arduino: Connect the sensor to Digital I/O Pin 2.
// - For ESP32: Connect the sensor to pin GPIO2 or P2.
// - For ESP8266: Connect the sensor to GPIO2 or D4.
DHT11 dht11(2);

int temperature;
int humidityErr;
String messa;

void setup()
{
   // Инициируем дисплей на 16 столбцов и 2 строки (LCD 16x2)
   lcd.begin(16,2);  
    
   lcd.setCursor(0,0);                // установили курсор на первую строку
   lcd.print("Hello, Arduino!");       // вывели текст
   lcd.setCursor(0,1);                // установили курсор на вторую строку
   lcd.print("www.ittve.me");         // вывели текст

   // Initialize serial communication to allow debugging and data readout.
   // Using a baud rate of 9600 bps.
   Serial.begin(9600);
}

void loop()
{
   // Wait for 1 seconds before the next reading.
   delay(1000);

   FromDht11(temperature, humidityErr, messa);
   Serial.println(messa);

   Serial.println(temperature);
   Serial.println(humidityErr);
   Serial.println(" ");
}

void FromDht11 (int &temperature, int &humidityErr, String &messa)
{
   messa = "";
   // Attempt to read the temperature and humidity values from the DHT11 sensor.
   temperature = dht11.readTemperature();
   // При использовании ESP32 или ESP8266 (архитектура xtensa) следует сделать
   // небольшую задержку для стабилизации показаний
   // при последовательном вызове методов
   // delay(50);
   humidityErr = dht11.readHumidity();
   // Check the results of the readings.
   // If there are no errors, print the temperature and humidity values.
   // If there are errors, print the appropriate error messages.
   if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT &&
       humidityErr != DHT11::ERROR_CHECKSUM && humidityErr != DHT11::ERROR_TIMEOUT)
   {
      messa += "Температура: ";    
      messa += temperature;    
      messa += "°C\r\n";    
      messa += "Влажность: ";    
      messa += humidityErr;    
      messa += "%";    
   }
   else
   {
      if (humidityErr == DHT11::ERROR_TIMEOUT || humidityErr == DHT11::ERROR_CHECKSUM)
      {
         messa += "Ошибка чтения влажности: "+DHT11::getErrorString(humidityErr); 
         humidityErr=-2;
      }
      if (temperature == DHT11::ERROR_TIMEOUT || temperature == DHT11::ERROR_CHECKSUM)
      {
         messa += "Ошибка чтения температуры: "+DHT11::getErrorString(temperature);    
         humidityErr=-1;
      }
   }
}

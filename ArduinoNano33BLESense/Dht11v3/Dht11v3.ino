/* ========================================================================= */
/*   Dht11v2.ino                                                             */
/*   (c) 2023-12-18 Труфанов Владимир                                        */
/*                                                                           */
/*   Description:      скетч снятия показаний с датчика DHT11 (с библиотекой */ 
/*                 версии DHT11-1.0.0) и вывода значений на дисплей LCD1602a */
/* ========================================================================= */

#include <Wire.h>
// Include the DHT11 library for interfacing with the sensor.
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
#define DHT11PIN 2
DHT11 sensor(DHT11PIN);

byte degree[8] = // кодируем символ градуса
{
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
};

void setup()
{
   // Инициируем дисплей на 16 столбцов и 2 строки (LCD 16x2)
   lcd.begin(0x27,16,2); 
   // Создаем символ под номером 1 
   lcd.createChar(1, degree); 
}

void loop()
{
   // Wait for 1 seconds before the next reading.
   delay(1000);
   lcd.setCursor(0, 0);
   // Read the humidity from the sensor.
   int humidity = sensor.readHumidity();
   // If the humidity reading was successful, print it to the serial monitor.
   if (humidity != -1)
   {
     lcd.print("Humidity:     %");
     lcd.setCursor(12, 0);
     lcd.print(humidity);
   }
   else
   {
      // If the humidity reading failed, print an error message.
      lcd.print("Error humidity");
   }
   
   lcd.setCursor(0, 1);
   int temperature = sensor.readTemperature();
   if (temperature != -1)
   {
      lcd.print("Temperature   \1C");
      lcd.setCursor(12, 1);
      lcd.print(temperature);
   }
   else
   {
      lcd.print("Error temperature");
   }
   delay(2000);
}


/**
 * DHT11 Sensor Reader for Arduino
 * This sketch reads temperature and humidity data from the DHT11 sensor and prints the values to the serial port.
 * It also handles potential error states that might occur during reading.
 *
 * Author: Dhruba Saha
 * Version: 2.0.0
 * License: MIT
 */

// Include the DHT11 library for interfacing with the sensor.
// #include <DHT11.h>
#include "DHT11.h"

// Create an instance of the DHT11 class.
// - For Arduino: Connect the sensor to Digital I/O Pin 2.
// - For ESP32: Connect the sensor to pin GPIO2 or P2.
// - For ESP8266: Connect the sensor to GPIO2 or D4.
DHT11 dht11(2);

int temperature;
int humidityErr;
String messa;

void setup()
{
    // Initialize serial communication to allow debugging and data readout.
    // Using a baud rate of 9600 bps.
    Serial.begin(9600);
}

void loop()
{
    FromDht11(temperature, humidityErr, messa);
    Serial.println(messa);

    Serial.println(temperature);
    Serial.println(humidityErr);
    Serial.println(" ");

    /*
    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    int temperature = dht11.readTemperature();

    // If using ESP32 or ESP8266 (xtensa architecture), uncomment the delay below.
    // This ensures stable readings when calling methods consecutively.
    // delay(50);

    int humidity = dht11.readHumidity();

    // Check the results of the readings.
    // If there are no errors, print the temperature and humidity values.
    // If there are errors, print the appropriate error messages.
    if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT &&
        humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT)
    {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }
    else
    {
        if (temperature == DHT11::ERROR_TIMEOUT || temperature == DHT11::ERROR_CHECKSUM)
        {
            Serial.print("Temperature Reading Error: ");
            Serial.println(DHT11::getErrorString(temperature));
        }
        if (humidity == DHT11::ERROR_TIMEOUT || humidity == DHT11::ERROR_CHECKSUM)
        {
            Serial.print("Humidity Reading Error: ");
            Serial.println(DHT11::getErrorString(humidity));
        }
    }
    */
    
    // Wait for 1 seconds before the next reading.
    delay(1000);
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

      /*
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C\r\n");

      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");
      */
   }
   else
   {
      if (humidityErr == DHT11::ERROR_TIMEOUT || humidityErr == DHT11::ERROR_CHECKSUM)
      {
         messa += "Ошибка чтения влажности: "+DHT11::getErrorString(humidityErr); 
         humidityErr=-2;
         /*   
         Serial.print("Humidity Reading Error: ");
         Serial.println(DHT11::getErrorString(humidity));
         */   
      }
      if (temperature == DHT11::ERROR_TIMEOUT || temperature == DHT11::ERROR_CHECKSUM)
      {
         messa += "Ошибка чтения температуры: "+DHT11::getErrorString(temperature);    
         humidityErr=-1;
         /*
         Serial.print("Temperature Reading Error: ");
         Serial.println(DHT11::getErrorString(temperature));
         */
      }
   }
}







/*
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <dht11.h>
dht11 sensor;
#define DHT11PIN 2
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
  lcd.init();
  lcd.backlight();
  lcd.createChar(1, degree); // Создаем символ под номером 1
}
void loop()
{
  int chk = sensor.read(DHT11PIN);
  lcd.setCursor(0, 0);
  lcd.print("Hum:          %");
  lcd.setCursor(11, 0);
  lcd.print(sensor.humidity);
  lcd.setCursor(0, 1);
  lcd.print("temp:         \1C");
  lcd.setCursor(11, 1);
  lcd.print(sensor.temperature);
  delay(2000);
}
*/

/*
void loop()
{
  int chk = sensor.read(DHT11PIN);
  lcd.setCursor(0, 0);
  lcd.print("Hum:          %");
  lcd.setCursor(11, 0);
  lcd.print(sensor.humidity);
  lcd.setCursor(0, 1);
  lcd.print("temp:         1C");
  lcd.setCursor(11, 1);
  lcd.print(sensor.temperature);
  delay(2000);
}
*/

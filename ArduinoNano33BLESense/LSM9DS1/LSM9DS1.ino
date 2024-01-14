/* ========================================================================= */
/*   LSM9DS1.ino                                                             */
/*   (c) 2024-01-14 [2024-01-14] Труфанов Владимир                           */
/*                                                                           */
/*   Description:     скетч проверки датчика IMU с микросхемой LSM9DS1. Этот */
/*    чип содержит трехосные датчики IMU, такие как акселерометр, гироскоп и */
/*                                 магнитометр на Arduino Nano 33 BLE Sense. */
/* ========================================================================= */

#include <Arduino_LSM9DS1.h>

void setup() 
{
   // Инициализируем последовательную связь
   Serial.begin(115200);
   while (!Serial);
   Serial.println("Started");
   if (!IMU.begin()) 
   {
      Serial.println("Failed to initialize IMU!");
      while (1);
   }
}

void loop() 
{
   float x, y, z;
   
   // Читаем датчик ускорения: сначала проверяем, доступны ли данные датчика, 
   // используя IMU.accelerationAvailable(). Затем мы можем прочитать данные 
   // датчика, вызвав IMU.readAcceleration(). После этого мы печатаем данные 
   // датчика на последовательный терминал
   if (IMU.accelerationAvailable()) 
   {
      IMU.readAcceleration(x,y,z);
      Serial.print("Accelerometer: ");
      Serial.print(x);
      Serial.print('\t');
      Serial.print(y);
      Serial.print('\t');
      Serial.println(z);
   }

   // Считываем показания датчика гироскопа, вызвав IMU.readGyroscope () 
   // после вызова функции IMU.gyroscopeAvailable().
   if (IMU.gyroscopeAvailable()) 
   {
      IMU.readGyroscope(x,y,z);
      Serial.print("Gyroscop: ");
      Serial.print(x);
      Serial.print('\t');
      Serial.print(y);
      Serial.print('\t');
      Serial.println(z);
   }
   
   // Считываем показания датчика магнитного поля, вызывая функцию 
   // IMU.readMintageField(), а затем выводим результат на последовательный 
   // терминал. Следует обязательно позвонить в IMU.gyroscopeAvailable() перед 
   // чтением данных датчика.
   if (IMU.magneticFieldAvailable()) 
   {
      IMU.readMagneticField(x, y, z);
      Serial.print("Magnetic Field: ");
      Serial.print(x);
      Serial.print('\t');
      Serial.print(y);
      Serial.print('\t');
      Serial.println(z);
   }
   delay(300);
}

/* ============================================================= LSM9DS1.ino */

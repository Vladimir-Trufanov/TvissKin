/* ========================================================================= */
/*   OnlyLCD1602a.ino                                                        */
/*   (c) 2023-12-12 Труфанов Владимир                                        */
/*                                                                           */
/*   Description:          проверка подключения дисплея LCD1602a в различных */
/*                                               вариантах на Arduino 1.8.18 */
/* ========================================================================= */

/* 
// exam1: подключение со штатной библиотекой Arduino 1.8.18

#include <LiquidCrystal.h>
// Создаем объект дисплея на заданных контактах
//               [RS, E, D4, D5, D6, D7] 
LiquidCrystal lcd (3, 4,  5,  6,  7,  8);   

int temperature;
int humidityErr;
String messa;

void setup()
{
   // Инициируем дисплей на 16 столбцов и 2 строки (LCD 16x2)
   lcd.begin(16,2);  
    
   lcd.setCursor(0,0);             // Установить курсор на первую строку
   lcd.print("Hello, world");      // Вывести текст
   lcd.setCursor(0,1);             // Установить курсор на вторую строку
   lcd.print("www.ittve.me");  // Вывести текст
}

void loop()
{
}
*/

#include <Wire.h> 
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print("Ywrobot Arduino!");
   lcd.setCursor(0,2);
  lcd.print("Arduino LCM IIC 2004");
   lcd.setCursor(2,3);
  lcd.print("Power By Ec-yuan!");
}


void loop()
{
}

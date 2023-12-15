/* ========================================================================= */
/*                                                                           */
/*   MemoryGuide.ino                                                         */
/*   (c) 2023-12-13 Труфанов Владимир                                        */
/*                                                                           */
/*   Description:                                                            */
/*   https://docs.arduino.cc/learn/programming/memory-guide                  */
/* ========================================================================= */

/**
*  1 пример: Как определить, сколько осталось свободной оперативной памяти (RAM)
*  Это может оказаться полезным, когда скетч работает некорректно, и трудно определить причину ошибки.
*  Количество свободной памяти может меняться с течением времени, пока работает Ваша программа. 
*  Очень важно удостовериться, что Вы не тратите больше памяти, чем имеется в наличии у системы.
*  
*  После запуска этого варианта скетча Вы увидите, что количество памяти уменьшается, потому что каждая прокрутка цикла loop увеличивает размер строки. 
*  В какой-то момент память переполнится, и программа может перестанет работать. Поэтому не увеличивайте размер строк сверх необходимого, 
*  и следите за их размером. Также будьте особенно внимательны с кодом, который использует динамическое выделение памяти. Не пишите код, который динамически 
*  создает разное количество переменных в зависимости от некоторых параметров во время своей работы, потому что очень сложно бывает найти ошибки во время выполнения кода, 
*  связанные с переполнением памяти.
**/

/*
String c="Начало: ";

void setup()
{
   Serial.begin(9600);
}
 
void loop()
{
   c=c+"memoryFree() memoryFree() memoryFree() memoryFree() memoryFree() memoryFree() memoryFree() memoryFree() memoryFree() memoryFree() ";
   Serial.println(c);
   Serial.print(memoryFree()); // печать количества свободной оперативной памяти
   Serial.println(' ');        // печать пробела
   delay(2000);
}
*/
// Функция, возвращающая количество свободного ОЗУ (RAM)
int memoryFree()
{
// Переменные, создаваемые процессом сборки,
// когда компилируется скетч
   extern int __bss_end; 
   extern void *__brkval;
   int freeValue;
   if((int)__brkval == 0)
      freeValue = ((int)&freeValue) - ((int)&__bss_end);
   else
      freeValue = ((int)&freeValue) - ((int)__brkval);
   return freeValue;
}

/**
*  2 пример: Здесь совмещены два варианта показа свободной памяти
*  
*  [data] раздел содержит переменные, инициализированные в скетче
*  extern unsigned int __data_start;
*  extern unsigned int __data_end;
*  [BSS] раздел содержит неинициализированные данные
*  extern unsigned int __bss_start;
*  extern unsigned int __bss_end;
*  [heap] раздел хранит переменные, созданные во время выполнения
*  extern unsigned int __heap_start;
*  Высокая точка в оперативной памяти (RAM), занимаемая кучей. 
*  Это значение может быть найдено в системной переменной, которая называется __brkval.
*  extern void        *__brkval;
**/

void setup()
{
   Serial.begin(9600);
}
 
void loop()
{
  // Показываем свободную память второй функцией
  Serial.print(F("- SRAM left: "));
  Serial.println(freeRam());
  // Показываем свободную память первой функцией
  Serial.print("-  Free RAM: "); 
  Serial.println(memoryFree()); 
  proba();
  Serial.println(" ");
  delay(2000);
}
 
void proba()
{
   int hs;
   // Начало раздела инициализированных переменных
   extern int __data_start;
   hs = (int)&__data_start;
   Serial.print("&__data_start = "); 
   Serial.println(hs); 
   // Завершение раздела инициализированных переменных
   extern int __data_end;
   hs = (int)&__data_end;
   Serial.print("&__data_end = "); 
   Serial.println(hs); 
   // Начало раздела неинициализированных данных
   extern int __bss_start;
   hs = (int)&__bss_start;
   Serial.print("&__bss_start = "); 
   Serial.println(hs); 
   // Завершение раздела неинициализированных данных
   extern int __bss_end;
   hs = (int)&__bss_end;
   Serial.print("&__bss_end = "); 
   Serial.println(hs); 
   // Начало раздела переменных, созданных во время выполнения
   extern int __heap_start;
   hs = (int)&__heap_start;
   Serial.print("&__heap_start = "); 
   Serial.println(hs); 
   // Высокая точка в оперативной памяти (RAM)

   extern int __brkval;
   hs = (int) &__brkval;
   Serial.print("&__brkval = "); 
   Serial.println(hs); 
   hs = (int) __brkval;
   Serial.print("__brkval = "); 
   Serial.println(hs); 

   /*
   extern int *__brkval;
   hs = (int) &__brkval;
   Serial.print("&__brkval = "); 
   Serial.println(hs); 
   hs = (int) __brkval;
   Serial.print("__brkval = "); 
   Serial.println(hs); 
   */
}

// Второй вариант расчета свободной памяти
int freeRam() 
{
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int) __brkval);  
}

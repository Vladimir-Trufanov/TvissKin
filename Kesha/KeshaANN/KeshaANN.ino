// Arduino C/C++                                              *** Kesha.ino ***

// ****************************************************************************
// *            Мобильная игра по отгадыванию задуманной комбинации триггеров *
// *  (фоторезисторов) на основе искусственного интеллекта вместе со внуками. *
// *                                                                          *
// * Как проходит игра (1 версия):                                            *
// * играют двое, играют две игры на время. Вначале первый задумывает         *
// * комбинацию триггеров и обучает ИИ, а второй отгадывает эту комбинацию.   *
// * Во второй игре меняются местами - второй игрок задумывает комбинацию,    *
// * первый отгадывает. Кто быстрее отгадал, тот и выиграл.                   *
// *                                                                          *
// * v1.0, 04.12.2023                               Автор:      Труфанов В.Е. *
// * Copyright © 2022 tve                           Дата создания: 23.03.2012 *
// ****************************************************************************


// Переключаемся при отладке на библиотечные файлы в каталоге
#define isArduinoANNtve_lib
#if !defined(isArduinoANNtve_lib)
   #include "ArduinoANNtve.h"
#else
   #include <ArduinoANNtve.h>
#endif

// Инициируем счетчик проведенных тренировочных циклов (эпох)
int nEpoch = 0;
// Инициируем нейронную сеть
ArduinoANN myANN; 

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  nEpoch++;
  Serial.print (nEpoch);
  Serial.print (": ");
  Serial.println ("Kesha");
  myANN.Train();
  delay(10000);
}

/*** 
 * Конфигурация сети настраивается для каждой сети и включает в себя два массива
 * данных - входной и целевой, которые вместе составляют таблицу истинности 
 * обучающего набора. Таблица истинности показывает правила преобразования 
 * семи сегментов светодиодного цифрового дисплея (0-9) в двоичное число (0000 - 1001)
 * 
 * Cкорость обучения установлена на уровне 0.3 (желательно - порядка 0.01). 
 * Более низкое значение скорости обучения приводит к замедлению процесса обучения, 
 * но снижает вероятность того, что сеть начнет колебаться, будет выходит за 
 * рамки решения задачи обучения и никогда не достигает порога успеха.
 * 
 * Импульс сглаживает процесс обучения, добавляя часть предыдущего обратного 
 * распространения в текущее обратное распространение. Он помогает предотвратить 
 * явление, при котором сеть сходится к решению, которое является хорошим, но не
 * лучшим, также известное как сходимость к локальному минимуму. Значения импульса 
 * должны быть в диапазоне от 0 до 1.
 * 
 * Количество скрытых нейронов влияет на скорость обучения, предотвращает сходимость 
 * к локальному минимуму. Недостатком большого количества скрытых нейронов 
 * является большое количество весов, которые необходимо сохранить.
 * 
 * Начальные рандомизированные веса должны быть относительно небольшими. Значение 
 * в скетче равно .5. Это установит все начальные веса в диапазоне от -.5 до .5.
 * 
 * Успех - конечное значение порогового уровня ошибки в системе, при котором 
 * обучающий набор будет считаться выученным. Это очень небольшое число, большее нуля. 
 * Природа нейронной сети такова, что общая ошибка будет приближаться к нулю, но 
 * на самом деле никогда не достигнет его.
***/

// ************************************************************** Kesha.ino ***
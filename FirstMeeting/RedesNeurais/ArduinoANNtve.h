// Arduino C/C++                                        *** ArduinoANNtve.h ***

// ****************************************************************************
// * ArduinoANNtve                   Искусственная нейронная сеть для Arduino *
// *                            http://robotics.hobbizine.com/arduinoann.html *
// *                                                                          *
// *              Определения класса искусственной нейронной сети для Arduino *
// *                                                                          *
// * v2.0, 11.12.2023                  Авторы: Ralph Heymsfeld, Труфанов В.Е. *
// * Copyright © 2022 tve              Дата создания:              23.03.2012 *
// ****************************************************************************

/*** 
 * Конфигурация сети настраивается для каждой сети и включает в себя два массива
 * данных - входной и целевой, которые вместе составляют таблицу истинности 
 * обучающего набора. 
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

#ifndef ArduinoANNtve_h
#define ArduinoANNtve_h

#include "Arduino.h"

class ArduinoANN
{
  public:
  
  ArduinoANN();
  void Train();

  // Подключаем тренировочные матрицы и параметры   
  #include "WorkSet-Ralph-Heymsfeld.hh"
  // Подключаем тренировочные матрицы и параметры   
  //#include "WorkSet-Mil-Grau.hh"

  private:
  
  int i, j, p, q, r;
  int ReportEvery1000;
  int RandomizedIndex[PatternCount];
  long  TrainingCycle;
  float Rando;
  float Error;
  float Accum;

  float Hidden[HiddenNodes];
  float Output[OutputNodes];
  float HiddenWeights[InputNodes+1][HiddenNodes];         // Веса, поступающие в промежуточный слой  
  float OutputWeights[HiddenNodes+1][OutputNodes];        // Веса, поступающие на выход
  float HiddenDelta[HiddenNodes];
  float OutputDelta[OutputNodes];
  float ChangeHiddenWeights[InputNodes+1][HiddenNodes];   // Изменения обратного распространения из скрытого слоя
  float ChangeOutputWeights[HiddenNodes+1][OutputNodes];  // Изменения обратного распространения с выходов в скрытый слой

  void toTerminal();
};

#endif

// ******************************************************** ArduinoANNtve.h ***

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


#ifndef ArduinoANNtve_h
#define ArduinoANNtve_h

#include "Arduino.h"

class ArduinoANN
{
  public:
  
  ArduinoANN();
  void Train();

  // Подключаем тренировочные матрицы и параметры   
  // #include "WorkSet-Ralph-Heymsfeld.hh"
  // Подключаем тренировочные матрицы и параметры   
  #include "WorkSet-Mil-Grau.hh"

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

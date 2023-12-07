/*
  ArduinoANNtve.h - Библиотека для мигания азбуки Морзе.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef ArduinoANNtve_h
#define ArduinoANNtve_h

#include "Arduino.h"

/*
class Morse
{
  public:
    Morse(int pin);
    void begin();
    void dot();
    void dash();
  private:
    int _pin;
};
*/

class ArduinoANN
{
  public:
  
  ArduinoANN();
  void train();

  static const int PatternCount=4;         // Количество шаблонов - количество обучающих элементов или строк в таблице истинности. 
  static const int InputNodes=2;            // Входные узлы - количество входных нейронов. 
  static const int HiddenNodes = 3;           // Скрытые узлы - количество скрытых нейронов. 
  static const int OutputNodes = 4;           // Выходные узлы - количество выходных нейронов.
  static const float LearningRate = 0.3;      // Скорость обучения - параметр, который определяет, какая часть ошибки фактически передается обратно. 
  static const float Momentum = 0.9;          // Импульс - регулирует, насколько результаты предыдущей итерации влияют на текущую итерацию.
  static const float InitialWeightMax = 0.5;  // Начальный максимальный вес - устанавливает максимальные начальные значения для весов.
  static const float Success = 0.0004;        // Успех - конечное значение порога ошибки, при котором будет считаться, что сеть решила обучающий набор.

  byte Input[PatternCount][InputNodes]= 
  {
    {0,0},
    {0,1},
    {1,0},
    {1,1}
  }; 

  byte Target[PatternCount][OutputNodes] = 
  {
    { 0, 0, 0, 1 },  
    { 0, 0, 1, 0 }, 
    { 0, 1, 0, 0 }, 
    { 1, 0, 0, 0 }
  };

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

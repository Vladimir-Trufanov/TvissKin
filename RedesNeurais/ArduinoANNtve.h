/*
  ArduinoANNtve.h - Библиотека для --------- мигания азбуки Морзе.
  ---Created by David A. Mellis, November 2, 2007.
  --Released into the public domain.
*/
#ifndef ArduinoANNtve_h
#define ArduinoANNtve_h

#include "Arduino.h"

class ArduinoANN
{
  public:
  
  ArduinoANN();
  void Train(byte _Input[], byte _Target[], int _PatternCount, int _InputNodes, int _OutputNodes);

  static const int HiddenNodes = 3;           // Скрытые узлы - количество скрытых нейронов. 
  static const float LearningRate = 0.3;      // Скорость обучения - параметр, который определяет, какая часть ошибки фактически передается обратно. 
  static const float Momentum = 0.9;          // Импульс - регулирует, насколько результаты предыдущей итерации влияют на текущую итерацию.
  static const float InitialWeightMax = 0.5;  // Начальный максимальный вес - устанавливает максимальные начальные значения для весов.
  static const float Success = 0.0004;        // Успех - конечное значение порога ошибки, при котором будет считаться, что сеть решила обучающий набор.
  
   int PatternCount;              // Количество шаблонов - количество обучающих элементов или строк в таблице истинности. 
   int InputNodes;                // Входные узлы - количество входных нейронов. 
   int OutputNodes;               // Выходные узлы - количество выходных нейронов.

   //byte *Input;
   //byte Target[PatternCount][OutputNodes]; 



   int RowNol;
   int ColNol;
   //byte* myArray;


  
  /*
  static const int PatternCount;              // Количество шаблонов - количество обучающих элементов или строк в таблице истинности. 
  static const int InputNodes;                // Входные узлы - количество входных нейронов. 
  static const int OutputNodes;               // Выходные узлы - количество выходных нейронов.
  */

  private:
  
int i, j, p, q, r;
int ReportEvery1000;
long  TrainingCycle;
float Rando;
float Error;
float Accum;
void toTerminal();

};

#endif

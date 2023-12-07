/*
  ArduinoANNtve.h - Библиотека для мигания азбуки Морзе.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef ArduinoANNtve_h
#define ArduinoANNtve_h

#include "Arduino.h"

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

class ArduinoANN
{
  public:
  
  
const int PatternCount = 4;         // Количество шаблонов - количество обучающих элементов или строк в таблице истинности. 
const int InputNodes = 2;            // Входные узлы - количество входных нейронов. 
const int HiddenNodes = 3;           // Скрытые узлы - количество скрытых нейронов. 
const int OutputNodes = 4;           // Выходные узлы - количество выходных нейронов.
const float LearningRate = 0.3;      // Скорость обучения - параметр, который определяет, какая часть ошибки фактически передается обратно. 
const float Momentum = 0.9;          // Импульс - регулирует, насколько результаты предыдущей итерации влияют на текущую итерацию.
const float InitialWeightMax = 0.5;  // Начальный максимальный вес - устанавливает максимальные начальные значения для весов.
const float Success = 0.0004;        // Успех - конечное значение порога ошибки, при котором будет считаться, что сеть решила обучающий набор.

const byte Input[PatternCount][InputNodes]= 
{
   {0,0},
   {0,1},
   {1,0},
   {1,1}
}; 

const byte Target[PatternCount][OutputNodes] = 
{
  { 0, 0, 0, 1 },  
  { 0, 0, 1, 0 }, 
  { 0, 1, 0, 0 }, 
  { 1, 0, 0, 0 }
};
  
    ArduinoANN();

  private:
    int _pin;
};

#endif

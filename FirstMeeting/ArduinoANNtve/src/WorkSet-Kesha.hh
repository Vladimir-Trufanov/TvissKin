// Arduino C/C++                                       *** WorkSet-Kesha.hh ***

// ****************************************************************************
// *       Обучающий блок (тренировочные матрицы и параметры ) мобильной игры *
// *                со внуками по отгадыванию задуманной комбинации триггеров *
// *                     (фоторезисторов) на основе искусственного интеллекта *
// *                                                                          *
// * v1.0, 04.12.2023                               Автор:      Труфанов В.Е. *
// * Copyright © 2022 tve                           Дата создания: 23.03.2012 *
// ****************************************************************************

static const int   PatternCount = 6;           // Количество шаблонов - количество обучающих элементов или строк в таблице истинности. 
static const int   InputNodes = 4;             // Входные узлы - количество входных нейронов. 
static const int   OutputNodes = 1;            // Выходные узлы - количество выходных нейронов.
static const int   HiddenNodes = InputNodes+1; // Скрытые узлы - количество скрытых нейронов. 

static const float LearningRate = 0.3;         // Скорость обучения - параметр, который определяет, какая часть ошибки фактически передается обратно. 
static const float Momentum = 0.9;             // Импульс - регулирует, насколько результаты предыдущей итерации влияют на текущую итерацию.
static const float InitialWeightMax = 0.5;     // Начальный максимальный вес - устанавливает максимальные начальные значения для весов.
static const float Success = 0.0004;           // Успех - конечное значение порога ошибки, при котором будет считаться, что сеть решила обучающий набор.

// Матрица входов для отгадывания двух триггеров из четырех
// (для контроля - число сочетаний по 2 из 4)
//
// С из4по2 = 4! / ( (4-2)! * 2! = 1*2*3*4 / 1*2*1*2 = 24/4 = 6
byte Input[PatternCount][InputNodes]= 
{
   { 1, 1, 0, 0 },   // 0
   { 1, 0, 1, 0 },   // 1
   { 1, 0, 0, 1 },   // 2
   { 0, 1, 1, 0 },   // пусть это сочетание выбрано игроком
   { 0, 1, 0, 1 },   // 4
   { 0, 0, 1, 1 }    // 5
}; 

// Матрица выходов    
byte Target[PatternCount][OutputNodes] = 
{
   {0},              // 0
   {0},              // 1
   {0},              // 2
   {1},              // 3
   {0},              // 4
   {0}               // 5
};

/* Результат обучения: 2023-12-11

2: Kesha
Train
Исходные/нетренированные результаты (initial/untrained outputs):

  Training Pattern: 0
  Input 1 1 0 0   Target 0   Output 0.46877 
  Training Pattern: 1
  Input 1 0 1 0   Target 0   Output 0.46741 
  Training Pattern: 2
  Input 1 0 0 1   Target 0   Output 0.46242 
  Training Pattern: 3
  Input 0 1 1 0   Target 1   Output 0.46242 
  Training Pattern: 4
  Input 0 1 0 1   Target 0   Output 0.45796 
  Training Pattern: 5
  Input 0 0 1 1   Target 0   Output 0.45554 

TrainingCycle: 1  Error = 0.65369

  Training Pattern: 0
  Input 1 1 0 0   Target 0   Output 0.33988 
  Training Pattern: 1
  Input 1 0 1 0   Target 0   Output 0.33729 
  Training Pattern: 2
  Input 1 0 0 1   Target 0   Output 0.33349 
  Training Pattern: 3
  Input 0 1 1 0   Target 1   Output 0.33950 
  Training Pattern: 4
  Input 0 1 0 1   Target 0   Output 0.33620 
  Training Pattern: 5
  Input 0 0 1 1   Target 0   Output 0.33315 

TrainingCycle: 490  Error = 0.00040

  Training Pattern: 0
  Input 1 1 0 0   Target 0   Output 0.00936 
  Training Pattern: 1
  Input 1 0 1 0   Target 0   Output 0.00902 
  Training Pattern: 2
  Input 1 0 0 1   Target 0   Output 0.00070 
  Training Pattern: 3
  Input 0 1 1 0   Target 1   Output 0.97853 
  Training Pattern: 4
  Input 0 1 0 1   Target 0   Output 0.00925 
  Training Pattern: 5
  Input 0 0 1 1   Target 0   Output 0.00910 

Обучение завершено! Точность достигнута.
--------

*/


// ******************************************************* WorkSet-Kesha.hh ***

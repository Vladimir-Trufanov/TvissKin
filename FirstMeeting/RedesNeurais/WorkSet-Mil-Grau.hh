// Arduino C/C++                                    *** WorkSet-Mil_Grau.hh ***

// ****************************************************************************
// * ArduinoANNtve                   Искусственная нейронная сеть для Arduino *
// *                            http://robotics.hobbizine.com/arduinoann.html *
// *                                                                          *
// *        Тренировочные матрицы и параметры для обучения четырехлампочковой *
// *                  модели по материалам ютуб-канала Inteligencia Mil Grau: *
// * https://www.youtube.com/watch?v=c5TA2Y8DeaM&list=PLYAGaVIlnsYaRibf94GEOwZh7qdCLcbJ5&index=2
// * https://www.youtube.com/watch?v=qPrrQVxQcWU&list=PLYAGaVIlnsYaRibf94GEOwZh7qdCLcbJ5&index=2
// * https://www.youtube.com/watch?v=xMleUVNRPbY&list=PLYAGaVIlnsYaRibf94GEOwZh7qdCLcbJ5&index=3
// * https://www.youtube.com/watch?v=h4-1y_dXtKE&list=PLYAGaVIlnsYaRibf94GEOwZh7qdCLcbJ5&index=4
// *                                                                          *
// * и статьи:              https://github.com/inteligenciamilgrau/arduinoann *
// *                                                                          *
// * v2.0, 11.12.2023            Авторы: Inteligencia Mil Grau, Труфанов В.Е. *
// * Copyright © 2022 tve        Дата создания:                    23.03.2012 *
// ****************************************************************************

static const int   PatternCount=4;             // Количество шаблонов - количество обучающих элементов или строк в таблице истинности. 
static const int   InputNodes=2;               // Входные узлы - количество входных нейронов. 
static const int   OutputNodes = 4;            // Выходные узлы - количество выходных нейронов.
static const int   HiddenNodes = InputNodes+1; // Скрытые узлы - количество скрытых нейронов. 

static const float LearningRate = 0.3;         // Скорость обучения - параметр, который определяет, какая часть ошибки фактически передается обратно. 
static const float Momentum = 0.9;             // Импульс - регулирует, насколько результаты предыдущей итерации влияют на текущую итерацию.
static const float InitialWeightMax = 0.5;     // Начальный максимальный вес - устанавливает максимальные начальные значения для весов.
static const float Success = 0.0004;           // Успех - конечное значение порога ошибки, при котором будет считаться, что сеть решила обучающий набор.

// Матрица входов
byte Input[PatternCount][InputNodes]= 
{
   {0,0},
   {0,1},
   {1,0},
   {1,1}
}; 

// Матрица выходов    
byte Target[PatternCount][OutputNodes] = 
{
   { 0, 0, 0, 1 },  
   { 0, 0, 1, 0 }, 
   { 0, 1, 0, 0 }, 
   { 1, 0, 0, 0 }
};

/*
ТАБЛИЦЫ NEURAIS
Исходные/нетренированные результаты (initial/untrained outputs):

  Training Pattern: 0
  Input 0 0   Target 0 0 0 1   Output 0.64099 0.57317 0.36329 0.63768 
  Training Pattern: 1
  Input 0 1   Target 0 0 1 0   Output 0.63671 0.56262 0.36555 0.63961 
  Training Pattern: 2
  Input 1 0   Target 0 1 0 0   Output 0.63764 0.56844 0.36493 0.63674 
  Training Pattern: 3
  Input 1 1   Target 1 0 0 0   Output 0.63331 0.55802 0.36719 0.63858 

TrainingCycle: 1  Error = 2.30145

  Training Pattern: 0
  Input 0 0   Target 0 0 0 1   Output 0.50331 0.49906 0.32573 0.57399 
  Training Pattern: 1
  Input 0 1   Target 0 0 1 0   Output 0.50739 0.49272 0.33052 0.57924 
  Training Pattern: 2
  Input 1 0   Target 0 1 0 0   Output 0.50423 0.49678 0.32867 0.57451 
  Training Pattern: 3
  Input 1 1   Target 1 0 0 0   Output 0.50817 0.49054 0.33344 0.57964 

TrainingCycle: 1000  Error = 0.00307

  Training Pattern: 0
  Input 0 0   Target 0 0 0 1   Output 0.00001 0.01439 0.01816 0.97436 
  Training Pattern: 1
  Input 0 1   Target 0 0 1 0   Output 0.01976 0.00012 0.97258 0.02346 
  Training Pattern: 2
  Input 1 0   Target 0 1 0 0   Output 0.01945 0.97840 0.00001 0.01974 
  Training Pattern: 3
  Input 1 1   Target 1 0 0 0   Output 0.96913 0.02037 0.02526 0.00069 

TrainingCycle: 2000  Error = 0.00144

  Training Pattern: 0
  Input 0 0   Target 0 0 0 1   Output 0.00000 0.00983 0.01261 0.98261 
  Training Pattern: 1
  Input 0 1   Target 0 0 1 0   Output 0.01359 0.00006 0.98113 0.01600 
  Training Pattern: 2
  Input 1 0   Target 0 1 0 0   Output 0.01333 0.98514 0.00000 0.01330 
  Training Pattern: 3
  Input 1 1   Target 1 0 0 0   Output 0.97878 0.01419 0.01728 0.00039 

TrainingCycle: 3000  Error = 0.00094

  Training Pattern: 0
  Input 0 0   Target 0 0 0 1   Output 0.00000 0.00789 0.01023 0.98606 
  Training Pattern: 1
  Input 0 1   Target 0 0 1 0   Output 0.01097 0.00004 0.98477 0.01285 
  Training Pattern: 2
  Input 1 0   Target 0 1 0 0   Output 0.01075 0.98800 0.00000 0.01061 
  Training Pattern: 3
  Input 1 1   Target 1 0 0 0   Output 0.98287 0.01154 0.01391 0.00029 

TrainingCycle: 4000  Error = 0.00069

  Training Pattern: 0
  Input 0 0   Target 0 0 0 1   Output 0.00000 0.00675 0.00882 0.98807 
  Training Pattern: 1
  Input 0 1   Target 0 0 1 0   Output 0.00945 0.00003 0.98690 0.01103 
  Training Pattern: 2
  Input 1 0   Target 0 1 0 0   Output 0.00925 0.98967 0.00000 0.00907 
  Training Pattern: 3
  Input 1 1   Target 1 0 0 0   Output 0.98527 0.00998 0.01194 0.00023 

TrainingCycle: 5000  Error = 0.00055

  Training Pattern: 0
  Input 0 0   Target 0 0 0 1   Output 0.00000 0.00599 0.00787 0.98942 
  Training Pattern: 1
  Input 0 1   Target 0 0 1 0   Output 0.00842 0.00002 0.98833 0.00980 
  Training Pattern: 2
  Input 1 0   Target 0 1 0 0   Output 0.00823 0.99080 0.00000 0.00803 
  Training Pattern: 3
  Input 1 1   Target 1 0 0 0   Output 0.98688 0.00892 0.01061 0.00020 

TrainingCycle: 6000  Error = 0.00045

  Training Pattern: 0
  Input 0 0   Target 0 0 0 1   Output 0.00000 0.00544 0.00717 0.99040 
  Training Pattern: 1
  Input 0 1   Target 0 0 1 0   Output 0.00766 0.00002 0.98938 0.00890 
  Training Pattern: 2
  Input 1 0   Target 0 1 0 0   Output 0.00749 0.99163 0.00000 0.00728 
  Training Pattern: 3
  Input 1 1   Target 1 0 0 0   Output 0.98806 0.00814 0.00964 0.00017 

TrainingCycle: 6756  Error = 0.00040

  Training Pattern: 0
  Input 0 0   Target 0 0 0 1   Output 0.00000 0.00511 0.00675 0.99099 
  Training Pattern: 1
  Input 0 1   Target 0 0 1 0   Output 0.00721 0.00002 0.99001 0.00836 
  Training Pattern: 2
  Input 1 0   Target 0 1 0 0   Output 0.00704 0.99213 0.00000 0.00683 
  Training Pattern: 3
  Input 1 1   Target 1 0 0 0   Output 0.98877 0.00767 0.00906 0.00016 

Обучение завершено! Точность достигнута.
--------
*/

// **************************************************** WorkSet-Mil_Grau.hh ***

// Arduino C/C++                             *** WorkSet-Ralph-Heymsfeld.hh ***

// ****************************************************************************
// * ArduinoANNtve                   Искусственная нейронная сеть для Arduino *
// *                            http://robotics.hobbizine.com/arduinoann.html *
// *                                                                          *
// *     Тренировочные матрицы и параметры для обучения, которые обеспечивают *
// *      преобразование семи сегментов светодиодного цифрового дисплея (0-9) *
// *                                           в двоичное число (0000 - 1001).*
// *                                                                          *
// * v2.0, 11.12.2023            Авторы: Inteligencia Mil Grau, Труфанов В.Е. *
// * Copyright © 2022 tve        Дата создания:                    23.03.2012 *
// ****************************************************************************


static const int PatternCount = 10;         // Количество шаблонов - количество обучающих элементов или строк в таблице истинности. 
static const int InputNodes = 7;            // Входные узлы - количество входных нейронов. 
static const int OutputNodes = 4;           // Выходные узлы - количество выходных нейронов.
static const int HiddenNodes = 8;           // Скрытые узлы - количество скрытых нейронов. 

static const float LearningRate = 0.3;      // Скорость обучения - параметр, который определяет, какая часть ошибки фактически передается обратно. 
static const float Momentum = 0.9;          // Импульс - регулирует, насколько результаты предыдущей итерации влияют на текущую итерацию.
static const float InitialWeightMax = 0.5;  // Начальный максимальный вес - устанавливает максимальные начальные значения для весов.
static const float Success = 0.0004;        // Успех - конечное значение порога ошибки, при котором будет считаться, что сеть решила обучающий набор.

// Матрица входов
const byte Input[PatternCount][InputNodes]= 
{
  { 1, 1, 1, 1, 1, 1, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1 },  // 2
  { 1, 1, 1, 1, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 1 },  // 4
  { 1, 0, 1, 1, 0, 1, 1 },  // 5
  { 0, 0, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 0, 0, 0, 0 },  // 7 
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 0, 0, 1, 1 }   // 9
}; 

// Матрица выходов    
const byte Target[PatternCount][OutputNodes] = 
{
  { 0, 0, 0, 0 },  
  { 0, 0, 0, 1 }, 
  { 0, 0, 1, 0 }, 
  { 0, 0, 1, 1 }, 
  { 0, 1, 0, 0 }, 
  { 0, 1, 0, 1 }, 
  { 0, 1, 1, 0 }, 
  { 0, 1, 1, 1 }, 
  { 1, 0, 0, 0 }, 
  { 1, 0, 0, 1 } 
};

/*
ОРИГИНАЛЬНЫЕ ТАБЛИЦЫ:
Исходные/нетренированные результаты (initial/untrained outputs):

  Training Pattern: 0
  Input 1 1 1 1 1 1 0   Target 0 0 0 0   Output 0.32768 0.56201 0.50242 0.44359 
  Training Pattern: 1
  Input 0 1 1 0 0 0 0   Target 0 0 0 1   Output 0.34117 0.56378 0.51421 0.43965 
  Training Pattern: 2
  Input 1 1 0 1 1 0 1   Target 0 0 1 0   Output 0.31159 0.52596 0.51601 0.46980 
  Training Pattern: 3
  Input 1 1 1 1 0 0 1   Target 0 0 1 1   Output 0.32732 0.54722 0.52441 0.46224 
  Training Pattern: 4
  Input 0 1 1 0 0 1 1   Target 0 1 0 0   Output 0.34308 0.51968 0.49464 0.45977 
  Training Pattern: 5
  Input 1 0 1 1 0 1 1   Target 0 1 0 1   Output 0.34513 0.54778 0.47954 0.47940 
  Training Pattern: 6
  Input 0 0 1 1 1 1 1   Target 0 1 1 0   Output 0.35079 0.51188 0.50075 0.45963 
  Training Pattern: 7
  Input 1 1 1 0 0 0 0   Target 0 1 1 1   Output 0.32728 0.58248 0.50341 0.44962 
  Training Pattern: 8
  Input 1 1 1 1 1 1 1   Target 1 0 0 0   Output 0.32639 0.52396 0.50802 0.45736 
  Training Pattern: 9
  Input 1 1 1 0 0 1 1   Target 1 0 0 1   Output 0.32989 0.53719 0.48215 0.47018 

TrainingCycle: 1  Error = 5.30862

  Training Pattern: 0
  Input 1 1 1 1 1 1 0   Target 0 0 0 0   Output 0.22604 0.19572 0.33742 0.42772 
  Training Pattern: 1
  Input 0 1 1 0 0 0 0   Target 0 0 0 1   Output 0.23242 0.21270 0.34442 0.42804 
  Training Pattern: 2
  Input 1 1 0 1 1 0 1   Target 0 0 1 0   Output 0.20888 0.17140 0.35869 0.45143 
  Training Pattern: 3
  Input 1 1 1 1 0 0 1   Target 0 0 1 1   Output 0.22307 0.18975 0.36465 0.45835 
  Training Pattern: 4
  Input 0 1 1 0 0 1 1   Target 0 1 0 0   Output 0.23864 0.18826 0.32311 0.44692 
  Training Pattern: 5
  Input 1 0 1 1 0 1 1   Target 0 1 0 1   Output 0.24261 0.20362 0.32247 0.46946 
  Training Pattern: 6
  Input 0 0 1 1 1 1 1   Target 0 1 1 0   Output 0.24668 0.18853 0.34229 0.43362 
  Training Pattern: 7
  Input 1 1 1 0 0 0 0   Target 0 1 1 1   Output 0.22180 0.21219 0.33374 0.44586 
  Training Pattern: 8
  Input 1 1 1 1 1 1 1   Target 1 0 0 0   Output 0.22567 0.17483 0.34380 0.44264 
  Training Pattern: 9
  Input 1 1 1 0 0 1 1   Target 1 0 0 1   Output 0.22812 0.18668 0.31092 0.46448 

TrainingCycle: 1000  Error = 0.00257

  Training Pattern: 0
  Input 1 1 1 1 1 1 0   Target 0 0 0 0   Output 0.01188 0.00081 0.00605 0.01343 
  Training Pattern: 1
  Input 0 1 1 0 0 0 0   Target 0 0 0 1   Output 0.00204 0.01627 0.01419 0.98575 
  Training Pattern: 2
  Input 1 1 0 1 1 0 1   Target 0 0 1 0   Output 0.00803 0.00025 0.99590 0.00791 
  Training Pattern: 3
  Input 1 1 1 1 0 0 1   Target 0 0 1 1   Output 0.00983 0.01359 0.99246 0.99263 
  Training Pattern: 4
  Input 0 1 1 0 0 1 1   Target 0 1 0 0   Output 0.01393 0.98170 0.00303 0.01544 
  Training Pattern: 5
  Input 1 0 1 1 0 1 1   Target 0 1 0 1   Output 0.01057 0.99448 0.01343 0.98976 
  Training Pattern: 6
  Input 0 0 1 1 1 1 1   Target 0 1 1 0   Output 0.00056 0.99310 0.98476 0.00016 
  Training Pattern: 7
  Input 1 1 1 0 0 0 0   Target 0 1 1 1   Output 0.00020 0.98020 0.98320 1.00000 
  Training Pattern: 8
  Input 1 1 1 1 1 1 1   Target 1 0 0 0   Output 0.97940 0.00029 0.01019 0.00746 
  Training Pattern: 9
  Input 1 1 1 0 0 1 1   Target 1 0 0 1   Output 0.98320 0.01904 0.00360 0.98731 

TrainingCycle: 2000  Error = 0.00120

  Training Pattern: 0
  Input 1 1 1 1 1 1 0   Target 0 0 0 0   Output 0.00792 0.00049 0.00404 0.00921 
  Training Pattern: 1
  Input 0 1 1 0 0 0 0   Target 0 0 0 1   Output 0.00146 0.01108 0.00981 0.99020 
  Training Pattern: 2
  Input 1 1 0 1 1 0 1   Target 0 0 1 0   Output 0.00534 0.00018 0.99728 0.00532 
  Training Pattern: 3
  Input 1 1 1 1 0 0 1   Target 0 0 1 1   Output 0.00668 0.00928 0.99463 0.99489 
  Training Pattern: 4
  Input 0 1 1 0 0 1 1   Target 0 1 0 0   Output 0.00934 0.98746 0.00192 0.01052 
  Training Pattern: 5
  Input 1 0 1 1 0 1 1   Target 0 1 0 1   Output 0.00755 0.99623 0.00941 0.99278 
  Training Pattern: 6
  Input 0 0 1 1 1 1 1   Target 0 1 1 0   Output 0.00038 0.99527 0.98945 0.00009 
  Training Pattern: 7
  Input 1 1 1 0 0 0 0   Target 0 1 1 1   Output 0.00012 0.98646 0.98836 1.00000 
  Training Pattern: 8
  Input 1 1 1 1 1 1 1   Target 1 0 0 0   Output 0.98622 0.00017 0.00696 0.00578 
  Training Pattern: 9
  Input 1 1 1 0 0 1 1   Target 1 0 0 1   Output 0.98857 0.01305 0.00257 0.99154 

TrainingCycle: 3000  Error = 0.00078

  Training Pattern: 0
  Input 1 1 1 1 1 1 0   Target 0 0 0 0   Output 0.00624 0.00037 0.00319 0.00738 
  Training Pattern: 1
  Input 0 1 1 0 0 0 0   Target 0 0 0 1   Output 0.00121 0.00887 0.00795 0.99208 
  Training Pattern: 2
  Input 1 1 0 1 1 0 1   Target 0 0 1 0   Output 0.00421 0.00016 0.99786 0.00421 
  Training Pattern: 3
  Input 1 1 1 1 0 0 1   Target 0 0 1 1   Output 0.00533 0.00743 0.99563 0.99588 
  Training Pattern: 4
  Input 0 1 1 0 0 1 1   Target 0 1 0 0   Output 0.00742 0.98992 0.00146 0.00841 
  Training Pattern: 5
  Input 1 0 1 1 0 1 1   Target 0 1 0 1   Output 0.00619 0.99698 0.00767 0.99410 
  Training Pattern: 6
  Input 0 0 1 1 1 1 1   Target 0 1 1 0   Output 0.00031 0.99618 0.99147 0.00006 
  Training Pattern: 7
  Input 1 1 1 0 0 0 0   Target 0 1 1 1   Output 0.00009 0.98910 0.99057 1.00000 
  Training Pattern: 8
  Input 1 1 1 1 1 1 1   Target 1 0 0 0   Output 0.98899 0.00012 0.00558 0.00497 
  Training Pattern: 9
  Input 1 1 1 0 0 1 1   Target 1 0 0 1   Output 0.99080 0.01050 0.00211 0.99329 

TrainingCycle: 4000  Error = 0.00057

  Training Pattern: 0
  Input 1 1 1 1 1 1 0   Target 0 0 0 0   Output 0.00528 0.00030 0.00269 0.00632 
  Training Pattern: 1
  Input 0 1 1 0 0 0 0   Target 0 0 0 1   Output 0.00106 0.00759 0.00684 0.99319 
  Training Pattern: 2
  Input 1 1 0 1 1 0 1   Target 0 0 1 0   Output 0.00357 0.00014 0.99819 0.00357 
  Training Pattern: 3
  Input 1 1 1 1 0 0 1   Target 0 0 1 1   Output 0.00457 0.00635 0.99622 0.99647 
  Training Pattern: 4
  Input 0 1 1 0 0 1 1   Target 0 1 0 0   Output 0.00632 0.99137 0.00120 0.00719 
  Training Pattern: 5
  Input 1 0 1 1 0 1 1   Target 0 1 0 1   Output 0.00538 0.99741 0.00663 0.99488 
  Training Pattern: 6
  Input 0 0 1 1 1 1 1   Target 0 1 1 0   Output 0.00026 0.99671 0.99266 0.00005 
  Training Pattern: 7
  Input 1 1 1 0 0 0 0   Target 0 1 1 1   Output 0.00008 0.99064 0.99187 1.00000 
  Training Pattern: 8
  Input 1 1 1 1 1 1 1   Target 1 0 0 0   Output 0.99061 0.00010 0.00477 0.00446 
  Training Pattern: 9
  Input 1 1 1 0 0 1 1   Target 1 0 0 1   Output 0.99210 0.00901 0.00184 0.99429 

TrainingCycle: 5000  Error = 0.00045

  Training Pattern: 0
  Input 1 1 1 1 1 1 0   Target 0 0 0 0   Output 0.00465 0.00026 0.00236 0.00560 
  Training Pattern: 1
  Input 0 1 1 0 0 0 0   Target 0 0 0 1   Output 0.00097 0.00674 0.00610 0.99394 
  Training Pattern: 2
  Input 1 1 0 1 1 0 1   Target 0 0 1 0   Output 0.00314 0.00013 0.99841 0.00314 
  Training Pattern: 3
  Input 1 1 1 1 0 0 1   Target 0 0 1 1   Output 0.00405 0.00564 0.99663 0.99687 
  Training Pattern: 4
  Input 0 1 1 0 0 1 1   Target 0 1 0 0   Output 0.00559 0.99234 0.00103 0.00637 
  Training Pattern: 5
  Input 1 0 1 1 0 1 1   Target 0 1 0 1   Output 0.00483 0.99771 0.00593 0.99541 
  Training Pattern: 6
  Input 0 0 1 1 1 1 1   Target 0 1 1 0   Output 0.00023 0.99707 0.99346 0.00004 
  Training Pattern: 7
  Input 1 1 1 0 0 0 0   Target 0 1 1 1   Output 0.00007 0.99169 0.99275 1.00000 
  Training Pattern: 8
  Input 1 1 1 1 1 1 1   Target 1 0 0 0   Output 0.99170 0.00008 0.00422 0.00410 
  Training Pattern: 9
  Input 1 1 1 0 0 1 1   Target 1 0 0 1   Output 0.99298 0.00802 0.00165 0.99496 

TrainingCycle: 5624  Error = 0.00040

  Training Pattern: 0
  Input 1 1 1 1 1 1 0   Target 0 0 0 0   Output 0.00435 0.00024 0.00220 0.00525 
  Training Pattern: 1
  Input 0 1 1 0 0 0 0   Target 0 0 0 1   Output 0.00092 0.00633 0.00575 0.99430 
  Training Pattern: 2
  Input 1 1 0 1 1 0 1   Target 0 0 1 0   Output 0.00293 0.00013 0.99852 0.00294 
  Training Pattern: 3
  Input 1 1 1 1 0 0 1   Target 0 0 1 1   Output 0.00381 0.00530 0.99683 0.99706 
  Training Pattern: 4
  Input 0 1 1 0 0 1 1   Target 0 1 0 0   Output 0.00525 0.99281 0.00095 0.00598 
  Training Pattern: 5
  Input 1 0 1 1 0 1 1   Target 0 1 0 1   Output 0.00456 0.99785 0.00559 0.99567 
  Training Pattern: 6
  Input 0 0 1 1 1 1 1   Target 0 1 1 0   Output 0.00022 0.99724 0.99385 0.00004 
  Training Pattern: 7
  Input 1 1 1 0 0 0 0   Target 0 1 1 1   Output 0.00006 0.99219 0.99317 1.00000 
  Training Pattern: 8
  Input 1 1 1 1 1 1 1   Target 1 0 0 0   Output 0.99222 0.00008 0.00396 0.00392 
  Training Pattern: 9
  Input 1 1 1 0 0 1 1   Target 1 0 0 1   Output 0.99340 0.00753 0.00156 0.99528 

Обучение завершено! Точность достигнута.
--------
*/

// ********************************************* WorkSet-Ralph-Heymsfeld.hh ***

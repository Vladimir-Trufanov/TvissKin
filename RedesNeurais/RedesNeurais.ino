// Arduino C/C++                                         *** ArduinoANN.ino ***

// ****************************************************************************
// * ArduinoANN                      Искусственная нейронная сеть для Arduino *
// *                                                                          *
// *  Материал взят из статьи:  http://robotics.hobbizine.com/arduinoann.html *
// *                                                                          *
// *   Нейронная сеть, реализованная в скетче, является всего демонстрацией и *
// *  на самом деле не выполняет никаких реальных функций. Код включает набор *
// *    обучающих входов и выходов, и сеть обучается этому набору до тех пор, *
// *   пока не достигнет заранее определенного уровня точности. В этот момент *
// * программа объявляет о победе и затем перезапускается. Попутно результаты *
// *     обучения периодически отправляются на последовательный порт, который *
// *           отслеживается с помощью последовательного монитора Arduino IDE *
// *                                                                          *
// * v2.0, 04.12.2023            Авторы:       Ralph Heymsfeld, Труфанов В.Е. *
// * Copyright © 2022 tve        Дата создания:                    23.03.2012 *
// ****************************************************************************


/*
#include <math.h>

const int PatternCount = 4;          // Количество шаблонов - количество обучающих элементов или строк в таблице истинности. 
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
*/


// Переключаемся при отладке на библиотечные файлы в каталоге
// #define isArduinoANNtve_lib
#if !defined(isArduinoANNtve_lib)
   #include "ArduinoANNtve.h"
#else
   #include <ArduinoANNtve.h>
#endif

#include "simplelib.h";
testClass tObj;
  
const int PatternCount=4;            // Количество шаблонов - количество обучающих элементов или строк в таблице истинности. 
const int InputNodes=2;              // Входные узлы - количество входных нейронов. 
const int OutputNodes = 4;           // Выходные узлы - количество выходных нейронов.
   
byte Input[]={
   0, 0,
   0, 1,
   1, 0,
   1, 1
};

byte Target[]={
   0, 0, 0, 1,  
   0, 0, 1, 0, 
   0, 1, 0, 0, 
   1, 0, 0, 0
};


  byte myArray[] = {2, 4, 8,};




const int RowNol=4;       
const int ColNol=3;           

byte Nol[RowNol][ColNol] = 
{
  { 1, 1, 1 },  
  { 1, 0, 1 }, 
  { 1, 0, 1 }, 
  { 1, 1, 1 }
};



// Инициируем счетчик проведенных тренировочных циклов (эпох)
int nEpoch = 0;
// Инициируем нейронную сеть
ArduinoANN myANN;

void setup()
{
   Serial.begin(9600);
  
   // делаем массив
   byte myArray[] = {5, 33, 58, 251, 91};

   Serial.println("myArray ");  
   Serial.print("myArray ");  
   for (int i = 0; i < 5; i++) 
   {
      Serial.print(myArray[i]);  Serial.print(' ');
   }
   Serial.println(' ');

   
   // передаём массив и его размер (в байтах)
   long arraySum = tObj.getSum((byte*)myArray, sizeof(myArray));
   // arraySum == 438
   Serial.println(" "); 
   Serial.print("setup:arraySum=");  Serial.println(arraySum);
}

// ---

//void tress(byte *arrayPtr, int nRow, int nCol) 
void tress(byte arrayPtr[], int nRow, int nCol) 
{  
   Serial.print("nRow = "); Serial.println(nRow);
   Serial.print("nCol = "); Serial.println(nCol);

   int RowNol=nRow;
   int ColNol=nCol;
   byte myArray[RowNol][ColNol];


   int k; int l;
   for (int i=0; i<nRow; i++)
   {
      k=nCol * i;
      for (int j=0; j<nCol; j++)
      {
         l=k + j;
         Serial.print(arrayPtr[l]); Serial.print(" ");
         myArray[i][j]=arrayPtr[l];
      }
       Serial.println(" ");
   }

   Serial.println("myArray: "); 
   for (int i=0; i<nRow; i++)
   {
      for (int j=0; j<nCol; j++)
      {
         Serial.print(myArray[i][j]); Serial.print(" ");
      }
      Serial.println(" ");
   }

}



long sumArray(byte *arrayPtr, int arrSize) 
{  

   Serial.print("arrSize="); Serial.println(arrSize);

   byte arrayPtrO[arrSize];
   
   long sum = 0;
   for (int i = 0; i < arrSize; i++)
   {
      sum += arrayPtr[i];
      arrayPtrO[i] = arrayPtr[i];
      Serial.print(arrayPtr[i]); Serial.print("  ");
   }
   Serial.println(" ");

   long sum2 = 0;
   for (int i = 0; i < arrSize; i++)
   {
      sum2 += arrayPtrO[i];
      Serial.print(arrayPtrO[i]); Serial.print("  ");
   }
   Serial.println(" ");

   
   
   return sum; // возвращаем
}

void loop()
{
   int x = 10; 
   int *p;
   p = &x; //p теперь содержит адрес x 
   Serial.print("Значение, сохраненное в адресе, указанном p, равно: "); Serial.println(*p);
   
   byte myArray[] = 
   {
     1, 2, 3, 4, 
     5, 6, 7, 8
   };
   Serial.println("36:");
   Serial.println("summa = "); Serial.println(sumArray(myArray, sizeof(myArray)/sizeof(byte)));

   tress(myArray,2,4); 

   /*
   Serial.println("myArray ");  
   Serial.print("myArray ");  
   for (int i = 0; i < 5; i++) 
   {
      Serial.print(myArray[i]);  Serial.print(' ');
   }
   Serial.println(' ');
   */

   //Serial.print("loop:arraySum=");  Serial.println(arraySum);
   tObj.SumTrain();
   nEpoch++;
   Serial.print (nEpoch);
   Serial.print (": ");
   Serial.println ("ArduinoANNtve");
   myANN.Train(Input, Target, PatternCount, InputNodes, OutputNodes);
   delay(2000);
}

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


//#include <math.h>

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

/*
const int PatternCount = 10;         // Количество шаблонов - количество обучающих элементов или строк в таблице истинности. 
const int InputNodes = 7;            // Входные узлы - количество входных нейронов. 
const int HiddenNodes = 8;           // Скрытые узлы - количество скрытых нейронов. 
const int OutputNodes = 4;           // Выходные узлы - количество выходных нейронов.
const float LearningRate = 0.3;      // Скорость обучения - параметр, который определяет, какая часть ошибки фактически передается обратно. 
const float Momentum = 0.9;          // Импульс - регулирует, насколько результаты предыдущей итерации влияют на текущую итерацию.
const float InitialWeightMax = 0.5;  // Начальный максимальный вес - устанавливает максимальные начальные значения для весов.
const float Success = 0.0004;        // Успех - конечное значение порога ошибки, при котором будет считаться, что сеть решила обучающий набор.

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
*/

/*
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

void setup()
{
   Serial.begin(9600);
   randomSeed(analogRead(3));
   ReportEvery1000 = 1;
   for(p=0; p<PatternCount; p++) 
   {    
      RandomizedIndex[p] = p ;
   }
}  

// Каждый входной и скрытый уровни содержат дополнительный нейрон ('смещение'), 
// который всегда срабатывает (другими словами, он всегда имеет подразумеваемую 
// активацию "1"). Значение смещения добавляет стабильности и расширяет количество 
// возможных решений. Самое главное, это исключает возможность того, что все 
// входные данные будут равны нулю и, следовательно, сигнал не будет распространяться 
// по сети. В объявлениях для массивов, которые содержат веса и значения изменений, 
// виден этот дополнительный нейрон. Кроме того, во вложенных циклах, которые 
// обрабатывают функции активации и обновления, вы увидите, что существуют 
// отдельные вычисления для нейронов смещения, 
// которые не зависят от входного значения

void loop ()
{
   // Инициализируем и изменяем скрытые веса 
   // (веса распространения входов в скрытый слой)
   for( i = 0 ; i < HiddenNodes ; i++ ) 
   {    
      for( j = 0 ; j <= InputNodes ; j++ ) 
      { 
         // Значения изменений для обратного распространения из скрытого слоя устанавливаем в нули
         ChangeHiddenWeights[j][i] = 0.0;
         // Веса, поступающие в промежуточный слой устанавливаем в случайные значения
         // (от -0.5 до +0.5)
         Rando = float(random(100))/100;
         HiddenWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;
      }
   }
   // Инициализируем и изменяем выходные веса 
   // (веса распространения из скрытого слоя на выходы)
   for( i = 0 ; i < OutputNodes ; i ++ ) 
   {    
      for( j = 0 ; j <= HiddenNodes ; j++ ) 
      {
         // Значения изменений для обратного распространения с выходов устанавливаем в нули
         ChangeOutputWeights[j][i] = 0.0;  
         // Веса, поступающие на выходы устанавливаем в случайные значения
         // (от -0.5 до +0.5)
         Rando = float(random(100))/100;        
         OutputWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax ;
      }
   }
   Serial.println("Исходные/нетренированные результаты (initial/untrained outputs):");
   toTerminal();

   // *************************************************************************
   // *                     Начать тренировку нейронной сети                  *
   // *************************************************************************
   for( TrainingCycle = 1 ; TrainingCycle < 2147483647 ; TrainingCycle++) 
   { 
      // Рандомизирем порядок обучающих шаблонов
      // (рандомизируем порядок обучающих наборов на каждой итерации для 
      // уменьшения колебаний и сходимости к локальным минимумам)
      for( p = 0 ; p < PatternCount ; p++) 
      {
         q = random(PatternCount);
         r = RandomizedIndex[p] ; 
         RandomizedIndex[p] = RandomizedIndex[q] ; 
         RandomizedIndex[q] = r ;
      }
      Error = 0.0 ;
    
      // Проходим каждый тренировочный шаблон в рандомизированном порядке
      for( q = 0 ; q < PatternCount; q++ ) 
      {    
         p = RandomizedIndex[q];
         // Вычисляем активации скрытого слоя
         for(i = 0 ; i < HiddenNodes; i++) 
         {    
            Accum = HiddenWeights[InputNodes][i];
            for( j = 0 ; j < InputNodes; j++ ) 
            {
               Accum += Input[p][j] * HiddenWeights[j][i];
            }
            Hidden[i] = 1.0/(1.0 + exp(-Accum));
         }
         // Вычисляем активации выходного слоя и рассчитываем ошибки
         for(i = 0; i < OutputNodes; i++) 
         {    
            // Функция активации вычисляет выходные данные нейрона на основе суммы 
            // взвешенных соединений, поступающих в этот нейрон. Функция называется 
            // сигмовидной. Особенностью функции является то, что независимо от 
            // входных данных выходные данные будут находиться в диапазоне 
            // от 0 до 1. Эта функция очень удобна при кодировании нейронной сети, 
            // поскольку выходные данные нейрона всегда могут быть выражены 
            // в диапазоне между полным включением и полным выключением. 
            // Её общий вид: output = 1.0/(1.0 + exp(-Accum)),
            // где output - переменная массива, представляющая выходные данные 
            // активируемого нейрона, а Accum - общее количество взвешенных 
            // входных данных для этого нейрона
            
            Accum = OutputWeights[HiddenNodes][i];
            for(j = 0; j < HiddenNodes; j++) 
            {
               Accum += Hidden[j] * OutputWeights[j][i];
            }
            Output[i] = 1.0/(1.0 + exp(-Accum));  
            
            // Градиентный спуск позволяет нам вычислять величину ошибки на каждом 
            // выходном нейроне, определять, насколько каждое соединение с этим 
            // нейроном внесло вклад в ошибку, и вносить постепенные корректировки 
            // в веса этих соединений, которые будут систематически уменьшать ошибку.
            
            // Первым шагом в градиентном спуске является вычисление значения, 
            // называемого дельтой, для каждого нейрона. Дельта отражает величину ошибки - 
            // чем больше разница между целевым значением для нейрона и его 
            // фактическим выходом, тем больше дельта. На выходном уровне вычисление дельты 
            // простое: delta = (target - actual) * actual * (1 - actual)
            // которая рассматривается в коде как
            // OutputDelta[i] = (Target[p][i] - Output[i]) * Output[i] * (1.0 - Output[i]) ;
            
            OutputDelta[i] = (Target[p][i] - Output[i]) * Output[i] * (1.0 - Output[i]);   
            Error += 0.5 * (Target[p][i] - Output[i]) * (Target[p][i] - Output[i]);
         }
         
         // Пересчитываем обратное распространение ошибок на скрытый слой
         for(i = 0; i < HiddenNodes; i++) 
         { 
         
            // Вычисление дельты на скрытом уровне становится немного сложнее, 
            // поскольку нет цели для измерения. Вместо этого величина ошибки для 
            // каждого скрытого нейрона выводится из соотношения между весами и дельтой, 
            // которое было рассчитано для выходного уровня. Для каждого скрытого 
            // нейрона код пошагово перебирает все выходные соединения, умножая 
            // веса на дельты и сохраняя текущую сумму:
            // Accum += OutputWeights[i][j] * OutputDelta[j] ;
   
            Accum = 0.0;
            for(j = 0; j < OutputNodes; j++) 
            {
               Accum += OutputWeights[i][j] * OutputDelta[j];
            }
            
            // Затем вычисляется дельта внутреннего слоя путем замены значения, 
            // сохраненного в Accum, на Target [p] [i] - Output [i] в формуле, 
            // показанной в первом вычислении, которое становится:
            // HiddenDelta[i] = Accum * Hidden[i] * (1.0 - Hidden[i]) ;
            
            HiddenDelta[i] = Accum * Hidden[i] * (1.0 - Hidden[i]);
         }
         
         // Обновляем веса от входов к скрытому слою:
         // здесь значения скорости обучения и импульса изменяют значения веса. 
         // Для каждого веса величина изменения определяется по этой формуле:
         // change = (learning rate * weight * delta) + (momentum * previous change)
         // и затем новый вес определяется путем добавления старого веса к 
         // измененному значению: weight = weight + change

         // Для весов между внутренним и скрытым слоями эта формула отображается в виде: 
         //   ChangeHiddenWeights[j][i]=LearningRate*Input[p][j]*HiddenDelta[i]+Momentum*ChangeHiddenWeights[j][i];
         //   HiddenWeights[j][i] += ChangeHiddenWeights[j][i];

         // Для весов между скрытым и выходным слоями формула отображается в виде:
         //   ChangeOutputWeights[j][i]=LearningRate*Hidden[j]*OutputDelta[i]+Momentum*ChangeOutputWeights[j][i];
         //   OutputWeights[j][i] += ChangeOutputWeights[j][i];
         
         for(i = 0; i < HiddenNodes; i++) 
         {     
            ChangeHiddenWeights[InputNodes][i] = LearningRate * HiddenDelta[i] + Momentum * ChangeHiddenWeights[InputNodes][i];
            HiddenWeights[InputNodes][i] += ChangeHiddenWeights[InputNodes][i];
            for(j = 0; j < InputNodes; j++) 
            {
               ChangeHiddenWeights[j][i] = LearningRate * Input[p][j] * HiddenDelta[i] + Momentum * ChangeHiddenWeights[j][i];
               HiddenWeights[j][i] += ChangeHiddenWeights[j][i];
            }
         }
         // Обновляем веса от скрытого слоя к выходам
         for( i = 0; i < OutputNodes; i ++) 
         {    
            ChangeOutputWeights[HiddenNodes][i] = LearningRate * OutputDelta[i] + Momentum * ChangeOutputWeights[HiddenNodes][i];
            OutputWeights[HiddenNodes][i] += ChangeOutputWeights[HiddenNodes][i];
            for(j = 0; j < HiddenNodes; j++) 
            {
               ChangeOutputWeights[j][i] = LearningRate * Hidden[j] * OutputDelta[i] + Momentum * ChangeOutputWeights[j][i];
               OutputWeights[j][i] += ChangeOutputWeights[j][i];
            }
         }
      }
      // Каждые 1000 циклов отправляем данные на терминал для отображения
      ReportEvery1000 = ReportEvery1000 - 1;
      if (ReportEvery1000 == 0)
      {
         Serial.println(); 
         Serial.println(); 
         Serial.print ("TrainingCycle: ");
         Serial.print (TrainingCycle);
         Serial.print ("  Error = ");
         Serial.println (Error, 5);

         toTerminal();

         if (TrainingCycle==1)
         {
            ReportEvery1000 = 999;
         }
         else
         {
            ReportEvery1000 = 1000;
         }
      }    
      // Если значение ошибки меньше заданного порогового значения, то завершаем тренировку
      // иначе запускаем следующую итерацию обучения данных  
      if(Error < Success ) break;
   }
   Serial.println ();
   Serial.println(); 
   Serial.print ("TrainingCycle: ");
   Serial.print (TrainingCycle);
   Serial.print ("  Error = ");
   Serial.println (Error, 5);

   toTerminal();

   Serial.println ();  
   Serial.println ();
   Serial.println ("Обучение завершено! Точность достигнута.");
   Serial.println ("--------"); 
   Serial.println ();
   Serial.println ();  
   ReportEvery1000 = 1;
}

void toTerminal()
{
   for(p = 0 ; p < PatternCount ; p++) 
   { 
      Serial.println(); 
      Serial.print ("  Training Pattern: ");
      Serial.println (p);      
      Serial.print ("  Input ");
      for(i = 0; i < InputNodes; i++) 
      {
         Serial.print (Input[p][i], DEC);
         Serial.print (" ");
      }
      Serial.print ("  Target ");
      for(i = 0; i < OutputNodes; i++) 
      {
         Serial.print (Target[p][i], DEC);
         Serial.print (" ");
      }
      // Вычисляем активации скрытого слоя
      for(i = 0; i < HiddenNodes; i++) 
      {    
         Accum = HiddenWeights[InputNodes][i];
         for(j = 0; j < InputNodes; j++) 
         {
            Accum += Input[p][j] * HiddenWeights[j][i];
         }
         Hidden[i] = 1.0/(1.0 + exp(-Accum));
      }
      // Вычисляем активации выходного слоя и определяем ошибки
      for(i = 0; i < OutputNodes; i++) 
      {    
         Accum = OutputWeights[HiddenNodes][i];
         for(j = 0; j < HiddenNodes; j++) 
         {
            Accum += Hidden[j] * OutputWeights[j][i];
         }
         Output[i] = 1.0/(1.0 + exp(-Accum)); 
      }
      Serial.print ("  Output ");
      for(i = 0; i < OutputNodes; i++) 
      {       
         Serial.print (Output[i], 5);
         Serial.print (" ");
      }
   }
}
*/
// ********************************************************* ArduinoANN.ino ***

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
// ****************************************************************************

#include <math.h>

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

int i, j, p, q, r;
int ReportEvery1000;
int RandomizedIndex[PatternCount];
long  TrainingCycle;
float Rando;
float Error;
float Accum;

float Hidden[HiddenNodes];
float Output[OutputNodes];
float HiddenWeights[InputNodes+1][HiddenNodes];       // Веса, поступающие в промежуточный слой  
float OutputWeights[HiddenNodes+1][OutputNodes];
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
            Accum = OutputWeights[HiddenNodes][i];
            for(j = 0; j < HiddenNodes; j++) 
            {
               Accum += Hidden[j] * OutputWeights[j][i];
            }
            Output[i] = 1.0/(1.0 + exp(-Accum));   
            OutputDelta[i] = (Target[p][i] - Output[i]) * Output[i] * (1.0 - Output[i]);   
            Error += 0.5 * (Target[p][i] - Output[i]) * (Target[p][i] - Output[i]);
         }
         // Пересчитываем обратное распространение ошибок на скрытый слой
         for(i = 0; i < HiddenNodes; i++) 
         {    
            Accum = 0.0;
            for(j = 0; j < OutputNodes; j++) 
            {
               Accum += OutputWeights[i][j] * OutputDelta[j];
            }
            HiddenDelta[i] = Accum * Hidden[i] * (1.0 - Hidden[i]);
         }
         // Обновляем веса от входов к скрытому слою
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
   Serial.println ("Training Set Solved! ");
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

// ********************************************************* ArduinoANN.ino ***




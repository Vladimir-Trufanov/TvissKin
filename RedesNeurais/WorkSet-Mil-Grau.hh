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

// **************************************************** WorkSet-Mil_Grau.hh ***

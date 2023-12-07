// Использование библиотеки для мигания азбуки Морзе

#include <Morse.h>

int n = 0;
Morse morse(13);

void setup()
{
  Serial.begin(9600);
  morse.begin();
}

void loop()
{
  morse.dot(); morse.dot(); morse.dot();
  morse.dash(); morse.dash(); morse.dash();
  morse.dot(); morse.dot(); morse.dot();

  n++;
  Serial.print (n);
  Serial.print (": ");
  Serial.println ("SOS по Морзе (по установленной библиотеке): dot dot dot - dash dash dash - dot dot dot");
  delay(3000);
}

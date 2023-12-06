#include "Morse.cpp"

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
  Serial.println ("dot dot dot - dash dash dash - dot dot dot");
  delay(3000);
}

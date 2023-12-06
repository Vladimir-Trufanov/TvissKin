#include "dotimi.cpp"
// У доти

int pin = 13;
int n = 0;
int mode = OUTPUT;

void setup()
{
  Serial.begin(9600);
  pinMode(pin, mode);
}

void loop()
{
  n++;
  doti(pin); doti(pin); doti(pin);
  dash(); dash(); dash();
  doti(pin); doti(pin); doti(pin);
  Serial.print (n);
  Serial.print (": ");
  Serial.println ("У doti dot dot - dash dash dash - dot dot doti Й");
  delay(3000);
}

void dash()
{
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(250);
}

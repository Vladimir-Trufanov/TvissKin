/*
  Morse.cpp - Библиотека для мигания азбуки Морзе.
  Created by David A. Mellis, November 2, 2007.
  Updated by Jason A. Cox, February 18, 2023.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Morse.h"

Morse::Morse(int pin)
{
  _pin = pin;
  //Serial obj1;
  //obj1.begin(9600);
}

void Morse::begin()
{
  pinMode(_pin, OUTPUT);
}

void Morse::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void Morse::dash()
{
  Serial.println("Dash");
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}
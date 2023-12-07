/*
  ArduinoANNtve.cpp - Библиотека для мигания азбуки Морзе.
  Created by David A. Mellis, November 2, 2007.
  Updated by Jason A. Cox, February 18, 2023.
  Released into the public domain.
*/

#include "Arduino.h"
#include "math.h"

#include "ArduinoANNtve.h"

Morse::Morse(int pin)
{
  _pin = pin;
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
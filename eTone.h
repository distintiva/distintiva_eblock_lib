/* ***********************************************************
    Distintiva Solutions (https://github.com/distintiva)

    For those situations when you can not use tone and noTone


    Idea based on the source of MeBuzzer.cpp from makeblock library 
**************************************************************/
#ifndef eTone_H
#define eTone_H

void eTone(int pin, uint16_t frq, uint32_t duration)
{
  int period = 1000000L / frq;
  int pulse = period / 2;
  uint32_t ms=0;
 
  for (long i = 0; i < duration * 1000L; i += period) 
  {
    
    ms = micros();
    digitalWrite(pin, HIGH);
    while(micros()-ms<pulse){};
    
    ms = micros();
    digitalWrite(pin, LOW);
    while(micros()-ms<pulse){};
  }

}


void eNoTone(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

#endif
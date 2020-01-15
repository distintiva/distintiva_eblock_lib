/* ***********************************************************
    Distintiva Solutions (https://github.com/distintiva)

    For those situations when you can not use tone and noTone

   Inspired in TimerFreeTone tone Library from  Tim Eckel 
   https://bitbucket.org/teckel12/arduino-timer-free-tone/wiki/Home


**************************************************************/
#ifndef eTone_H
#define eTone_H



void eTone(int pin, uint16_t frq, uint32_t duration)
{

  int period = 1000000L / frq;
  int pulse = period / 2 ;
  uint32_t ms=0;
 
  ms = millis();
  while(millis()-ms<duration)
  {
        
    digitalWrite(pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(pin, LOW);
    delayMicroseconds(pulse);

  }

}


void eNoTone(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

#endif
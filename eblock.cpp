#include "Arduino.h"
#include "eblock.h"


volatile int e_pin_states=0;


uint8_t e_get_mode(uint8_t pin)
{
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);


  if (NOT_A_PIN == port || 0 == bit || (bit & bit - 1)) return 0xFF;

  
  volatile uint8_t *reg, *out;
  reg = portModeRegister(port);
  out = portOutputRegister(port);

  if (*reg & bit)
    return OUTPUT;
  else if (*out & bit)
    return INPUT_PULLUP;
  else
    return INPUT;
}

// set mode if not already setted
void e_set_mode(uint8_t pin, uint8_t mode)
{
  if( e_get_mode(pin)!= mode ) {
    pinMode(pin, mode);
    //- if mode changes reset button state of that pin
    bitClear(e_pin_states, pin);
  }
}

uint8_t e_is_button(uint8_t pin){
  e_set_mode(pin, INPUT);

  return digitalRead(pin) == LOW;
}

uint8_t e_is_button_down(uint8_t pin){
  
  if( e_button(pin) && bitRead(e_pin_states, pin)==0 ) {
    bitSet(e_pin_states, pin);
    return 1;
  }
  return 0;
}

uint8_t e_is_button_up(uint8_t pin){
  
  if( !e_button(pin) && bitRead(e_pin_states, pin) ) {
    bitClear(e_pin_states, pin);
    return 1;
  }
  return 0;
}

void e_pin_set(uint8_t pin, uint8_t state){
  e_set_mode(pin, OUTPUT);
  digitalWrite(pin, state);  
}

void e_pin_on(uint8_t pin){
  e_set_pin(pin, HIGH);
}

void e_pin_off(uint8_t pin){
   e_set_pin(pin, LOW);
}




void e_rgb( uint8_t pinR, uint8_t pinG, uint8_t pinB,  uint8_t R, uint8_t G, uint8_t B ){
  e_set_mode(pinR, OUTPUT);
  e_set_mode(pinG, OUTPUT);
  e_set_mode(pinB, OUTPUT);

  analogWrite(pinR, R);
  analogWrite(pinG, G);
  analogWrite(pinB, B);
}

uint16_t e_get_analog(uint8_t pin){
  if(pin< A0) pin=A0+pin; //- if pin pased like a number 1,2,3  instead A1, A2, A3
  e_set_mode(pin, INPUT);
  return analogRead(pin);
}

uint8_t e_get_analog_perc(uint8_t pin){
  uint16_t val =  e_analog(pin);

  return map(val, 0,1023, 0,100);

}

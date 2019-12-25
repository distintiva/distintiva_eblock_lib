#include "Arduino.h"
#include "eblock.h"


volatile uint64_t e_pin_states=0;

//- To store mode values 0-3
volatile uint64_t e_mode64_0=0;
volatile uint64_t e_mode64_1=0;


typedef struct {
        uint8_t id;
        void (*event)(uint8_t id);
} E_T_EVENT;

E_T_EVENT* events_list = NULL;
uint8_t events_count =0; 

uint8_t e_event_exists( uint8_t event_id ){
    for(uint8_t e =0; e< events_count; e++){
        if( events_list[e].id == event_id ) return true;
    }
    return false;    
} 

void e_event_call( uint8_t event_id ){
  
    for(uint8_t e =0; e< events_count; e++){
        if( events_list[e].id == event_id ){
           
               events_list[e].event(event_id);  
               return;
        } 
    }
    
} 

void e_event( uint8_t event_id,   void (*callback_fn)(uint8_t id) ) {
  
//Serial.println("ADD" + event);

  if(e_event_exists(event_id)) return;

  //- Add callback to the event list
    if(events_list == NULL ){
      events_list = ( E_T_EVENT* ) calloc( ++events_count , sizeof(E_T_EVENT));
    }else{
       events_list = ( E_T_EVENT* ) realloc( events_list , ++events_count*sizeof(E_T_EVENT)  );
    }
     
    events_list[events_count-1].id = event_id;
    events_list[events_count-1].event = callback_fn;
}


uint8_t e_get_mode(uint8_t pin)
{
  
    uint8_t mode = bit2Read64( e_mode64_0, e_mode64_1, pin );
    return  mode;

 /* uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);


  if (NOT_A_PIN == port || 0 == bit || (bit & bit - 1)) return 0xFF;

  
  volatile uint8_t *reg, *out;
  reg =  portModeRegister(port);
  out =  portOutputRegister(port);

  if (*reg & bit)
    return OUTPUT;
  else if (*out & bit)
    return INPUT_PULLUP;
  else
    return INPUT;
 */
  
  
}

// set mode if not already setted
void e_set_mode(uint8_t pin, uint8_t mode)
{
  if( e_get_mode(pin)!= mode ) {
    pinMode(pin, mode);

    //- store mode for this pin
    bit2Write64(e_mode64_0, e_mode64_1, mode, pin);

    //- if mode changes reset button state of that pin
    bitClear64(e_pin_states, pin);
  }
}

uint8_t e_is_button(uint8_t pin){
   uint8_t pressed_state=1;
  if( e_get_mode(pin)==INPUT_PULLUP ) {
    pressed_state=0;
  }else{
    e_set_mode(pin, INPUT);
  }

  return digitalRead(pin)==pressed_state /*== LOW*/;
}

uint8_t e_is_button_up(uint8_t pin){
  
  if( !e_is_button(pin) && bitRead(e_pin_states, pin)==1 ) {
      bitClear64(e_pin_states, pin);
    return 1;
  }
  return 0;
}

uint8_t e_is_button_down(uint8_t pin){
  
  if( e_is_button(pin) && bitRead(e_pin_states, pin)==0 ) {
     bitSet64(e_pin_states, pin);
  
    return 1;
  }
  return 0;
}

void e_pin_set(uint8_t pin, uint8_t state){
  e_set_mode(pin, OUTPUT);
  digitalWrite(pin, state);  
}

void e_pin_on(uint8_t pin){
  e_pin_set(pin, HIGH);
}

void e_pin_off(uint8_t pin){
   e_pin_set(pin, LOW);
}


void e_pwm(uint8_t pin, uint8_t value){
   e_set_mode(pin, OUTPUT);
   analogWrite(pin, value);

}

uint8_t e_touching(uint8_t pin){
   return e_get_analog(pin)>10;
}

uint8_t e_touch_down(uint8_t pin){
  if(pin< A0) pin=A0+pin;

  if( e_touching(pin) && bitRead(e_pin_states, pin)==0 ) {
    bitSet(e_pin_states, pin);
    return 1;
  }

  return false;
}



uint8_t e_touch_up(uint8_t pin){
  if(pin< A0) pin=A0+pin;
  
  if( !e_touching(pin) && bitRead(e_pin_states, pin) ) {
    bitClear(e_pin_states, pin);
    return 1;
  }
  return 0;
}




uint16_t e_get_analog(uint8_t pin){
  if(pin< A0) pin=A0+pin; //- if pin pased like a number 1,2,3  instead A1, A2, A3
  e_set_mode(pin, INPUT);
  return analogRead(pin);
}

uint8_t e_get_analog_perc(uint8_t pin){
  uint16_t val =  e_get_analog(pin);

  return map(val, 0,1023, 0,100);

}

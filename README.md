# Distintiva eBlock Library
 
 This library is developed to generate easy arduino code for  [eBlock](https://github.com/distintiva/eBlock)


# API 

```c

//- Stores 1 bit[0-1] in a specific position of a uint64_t variable ( like arr[0-63]=[0-1] )
#define bitSet64(value, bit)   ((value) |= (1ULL << bit ))
#define bitClear64(value, bit) ((value) &= ~(sizeof(value)<5?1UL:1ULL) <<(bit))
#define bitWrite64(value, bit, bitvalue) (bitvalue ? bitSet64(value, bit) : bitClear64(value, bit))
#define bitRead64(value, bit)  (bitRead(value, bit))

//- Stores 2 bits value[0-3] in a specific position of a 2 given uint64_t variables ( like arr[0-63]=[0-3] )
#define bit2Write64( u64_t0, u64_t1, val, pos )  ({ bitWrite64(u64_t0, pos, bitRead(val,0)  ); bitWrite64(u64_t1, pos, bitRead(val,1)  ); })
#define bit2Read64( u64_t0, u64_t1, pos )        ( bitRead64(u64_t1, pos) <<1 | bitRead64(u64_t0, pos) )


// Get the current mode of a pin
extern uint8_t 	e_get_mode(uint8_t pin);
// Sets pinMode only if not already setted with passed mode
extern void 	e_set_mode(uint8_t pin, uint8_t mode);
// True if digital button(pin) pressed
extern uint8_t 	e_is_button(uint8_t pin);
// True if digital button(pin) goes from normal to pressed
extern uint8_t 	e_is_button_down(uint8_t pin);
// True if digital button(pin) goes from pressed to normal
extern uint8_t 	e_is_button_up(uint8_t pin);
// Sets pin = state (no need to setMode before)
extern void 	e_pin_set(uint8_t pin, uint8_t state);
// Sets pin HIGH (no need to setMode before)
extern void 	e_pin_on(uint8_t pin);
// Sets pin LOW (no need to setMode before)
extern void 	e_pin_off(uint8_t pin);
// Read analog Value (no need to setMode before)
extern uint16_t e_get_analog(uint8_t pin);
// Read analog Value in percent(0-100) (no need to setMode before)
extern uint8_t 	e_get_analog_perc(uint8_t pin);
// Sets PWM
extern void 	e_pwm(uint8_t pin, uint8_t value);
// True if touching an analog pin
extern uint8_t  e_touching(uint8_t pin);
// True if analog pin goes from normal to pressed
extern uint8_t e_touch_down(uint8_t pin);
// True if analog pin goes from pressed to normal
extern uint8_t e_touch_up(uint8_t pin);


//=== Events ===
// Add a function pointer to the events stack  (ex.: e_event(23, my_func) )
extern void e_event( uint8_t event,   void (*callback_fn)(uint8_t id) ) ;
// Check if exixts an event with a passed id
extern uint8_t e_event_exists( uint8_t event_id );
// Fire event by its id
extern void e_event_call( uint8_t event_id );


```




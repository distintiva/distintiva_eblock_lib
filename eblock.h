

#ifndef eblock_h
#define eblock_h


// Get the current mode of a pin
extern uint8_t 	e_get_mode(uint8_t pin);
// Sets pinMode only if not already setted with passed mode
extern void 	e_set_mode(uint8_t pin, uint8_t mode);
// True if digital button(pin) pressed
extern uint8_t 	e_button(uint8_t pin);
// True if digital button(pin) goes from normal to pressed
extern uint8_t 	e_button_up(uint8_t pin);
// True if digital button(pin) goes from pressed to normal
extern uint8_t 	e_button_down(uint8_t pin);
// Sets pin HIGH (no need to setMode before)
extern void 	e_pin_on(uint8_t pin);
// Sets pin LOW (no need to setMode before)
extern void 	e_pin_off(uint8_t pin);
// RGB led connected to 3 digital pins (R, G, B)
extern void 	e_rgb( uint8_t pinR, uint8_t pinG, uint8_t pinB,  uint8_t R, uint8_t G, uint8_t B );
// Read analog Value (no need to setMode before)
extern uint16_t e_analog(uint8_t pin);
// Read analog Value in percent(0-100) (no need to setMode before)
extern uint8_t 	e_analog_perc(uint8_t pin);






#endif
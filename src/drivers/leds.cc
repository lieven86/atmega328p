//#include <Arduino.h>
#include <avr/io.h>
#include <drivers/leds.h>

namespace lst {
  
using namespace std;
  
//const uint16_t led1 = PINB1;
//const uint16_t led2 = PINB0;

void Leds::Init() {
  	DDRB |= 1 << PINB2 | 1 << PINB1; // set pin 1 2 as outputs
	//PORTB |= 1 << PINB1;
}

void Leds::Write() {
	// todo: writefunction: check value high or low to determine shift unshift port
	// if (leds_[0] == LOW) {
	// 	PORTB &= ~PINB1;
	// } else {
	// 	PORTB |= PINB1;
	// }
}

}  // namespace lst

#include <avr/io.h>
#include <drivers/timer.h>

namespace lst {

void Timer::Init() {
    // pinMode(3, OUTPUT); // output pin for OCR2B
    // pinMode(5, OUTPUT); // output pin for OCR0B

    // // Set up the 250KHz output
    // TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    // TCCR2B = _BV(WGM22) | _BV(CS20);
    // OCR2A = 63;
    // OCR2B = 0;

    // // Set up the 8MHz output
    // TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    // TCCR0B = _BV(WGM02) | _BV(CS00);
    // OCR0A = 1;
    // OCR0B = 0;

    // setup timer 0 for millis()
    
}

void Timer::Run() {
  //
}

void Timer::Clear() {
	//
}


}  // namespace lst

#include <drivers/dac.h>

namespace lst {
  
void Dac::Init() {
    // r2r output
    DDRD |= 0b11111111;
    PORTD |= 0b11111111;

    // digital output
    DDRB |= (1 << PINB3);

    // pwm output
}

void Dac::Write() {
    PORTD = value_[0];
    
    if (value_[1] > 127) {
        PORTB |= (1 << PINB3);
    } else {
        PORTB &= ~(1 << PINB3);
    }
}

}  // namespace lst

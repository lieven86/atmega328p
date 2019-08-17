//#include <Arduino.h>
#define HIGH 0x1
#define LOW  0x0

#include <avr/io.h>
#include <avr/interrupt.h>

#include <drivers/system_clock.h>
#include <drivers/timer.h>
#include <drivers/adc.h>
#include <drivers/dac.h>
#include <ui.h>
#include <app/app.h>
//// Todo
// DRIVER FILES ADC, DAC, LEDS, SWTCHES, RESOURCES, TIMER
// UI FIle
// SETUP TIMERS, FAST PWM for audio, SLOW for UI
// adapt oscillator code to avr

using namespace lst;

//Timer timer;
Dac dac;
Adc adc;
Ui ui;
App app_;

void Init() {
  cli();
  TCCR1B = (TCCR1B & ~(1 << WGM13)) | (1 << WGM12);
  TCCR1A = TCCR1A & ~((1 << WGM11) | (1 << WGM10));    
  // No prescaler
  TCCR1B = (TCCR1B & ~((1 << CS12) | (1 << CS11))) | (1 << CS10);
  // Set the compare register (OCR1A).
  // OCR1A is a 16-bit register, so we have to do this with interrupts disabled to be safe.
  // OCR1A = F_CPU / SAMPLE_RATE; 
  // Enable interrupt when TCNT1 == OCR1A
  TIMSK1 |= (1 << OCIE1A);
  sei();
  //OCR1A = 490; //40KHz Samplefreq
  OCR1A = 1200; 

  system_clock.Init();
  dac.Init();
  adc.Init();
  ui.Init(&adc);
  app_.Init(&ui, &adc, &dac);

}

ISR (TIMER0_OVF_vect, ISR_NOBLOCK) {
  // slow timer for ui
  system_clock.Tick();
  ui.Poll();
}

// Interrupt service routine for the 1ms tick
ISR (TIMER2_COMPA_vect) {
 //TIFR2 = (1 << OCF2B);  // shouldn't be needed according to the documentation, but is (perhaps the ISR is too short without it?)
 // Kick off a new ADC conversion. We already set the multiplexer to the correct channel when the last conversion finished.
 ADCSRA = 0b11001111;   // ADC enable, ADC start, manual trigger mode, ADC interrupt enable, prescaler = 128
}

ISR (ADC_vect, ISR_NOBLOCK) {
  adc.Read();
}

ISR (TIMER1_COMPA_vect, ISR_BLOCK) {
  // fast timer for processing
  app_.Process();
  dac.Write();
}

int main(void) {
  Init();

  while(1) {
    //ui.DoEvents();
  }
}


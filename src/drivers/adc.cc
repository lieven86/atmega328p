#include <drivers/adc.h>

namespace lst {
  
void Adc::Init() {
    // setup digital inputs
    DDRC &= ~(1 << PINC3);
    DDRC &= ~(1 << PINC4);
    PORTC |= (1 << PINC3) | (1 << PINC4);

    divider = 0;
    // Set up the ADC. We need to read the mains voltage frequently in order to get a sufficiently accurate RMS reading.
    // To avoid using too much CPU time, we use the conversion-complete interrupt. This means we can't use analogRead(),
    // we have to access the ADC ports directly.
    current_adc_channel = ADC_POT_1;      // set up which analog input we will read first
    ADMUX = 0b01000000 | current_adc_channel;
    ADCSRB = 0b00000000; // Analog Input bank 1
    ADCSRA = 0b10011111; // ADC enable, manual trigger mode, ADC interrupt enable, prescaler = 128
    
    // Set up a timer 2 interrupt every 1ms to kick off ADC conversions etc.
    // Do this last after we have initialized everything else
    ASSR = 0;
    TCCR2A = (1 << WGM21);    // CTC mode
    TCCR2B = (1 << CS22);     // prescaler = 64
    TCNT2 = 0;                // restart counter
    OCR2A = 249;              // compare register = 249, will be reached after 1ms
    //OCR2A = 128; 
    TIMSK2 = (1 << OCIE2A);
}

void Adc::Read() {
    uint8_t adcl = ADCL;
    uint8_t adch = ADCH;
    uint16_t adcVal = (adch << 8) | adcl;

    switch (current_adc_channel) {
        case ADC_POT_2:
            values_[1] = adcVal;
            current_adc_channel = ADC_POT_3;
            break;
        case ADC_POT_3:
            values_[2] = adcVal;
            current_adc_channel = ADC_CV_1;
            break;
        case ADC_CV_1:
            values_[3] = adcVal;
            //current_adc_channel = ADC_POT_1;
            if (divider > 2) {
                current_adc_channel = ADC_POT_1;
                divider = 0;
            } else {
                current_adc_channel = ADC_CV_1;
                divider++;
            }
            break;
        case ADC_POT_1:
            values_[0] = adcVal;
            current_adc_channel = ADC_POT_2;  
            break;
        default:
            break;
    }
    
    ADMUX = (0b01000000 | current_adc_channel);   // Vcc reference, select current channel
}
}  // namespace lst

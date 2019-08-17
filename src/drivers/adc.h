#ifndef LST_DRIVERS_ADC_H_
#define LST_DRIVERS_ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <lib.h>

namespace lst {

enum AdcChannel {
  ADC_POT_2 = 0,
  ADC_POT_3 = 1, 
  ADC_CV_1 = 2, 
  ADC_POT_1 = 5,
  ADC_CHANNEL_LAST
};

// enum AdcChannel {
//   ADC_POT_2 = 0,
//   ADC_POT_3 = 1, 
//   ADC_CV_1 = 2, 
//   ADC_POT_1 = 5,
//   ADC_CHANNEL_LAST
// };

class Adc {
 public:
  Adc() { }
  ~Adc() { }
  
  void Init();
  void Read();
  inline uint16_t value(uint8_t channel) const { return values_[channel]; } // 10 bit value
  inline uint8_t value8(uint8_t channel) const { return values_[channel] >> 2; } // 8 bit value
  inline float float_value(uint8_t channel) const {
    return static_cast<float>(values_[channel] >> 2) / 256.0f;
  }
  inline const uint16_t* values() { return &values_[0]; }
  
 private:
  uint16_t values_[ADC_CHANNEL_LAST];
  uint8_t current_adc_channel;
  uint8_t divider;
  DISALLOW_COPY_AND_ASSIGN(Adc);
};

}  // namespace lst

#endif  // LST_DRIVERS_ADC_H_

#ifndef LST_DRIVERS_LEDS_H_
#define LST_DRIVERS_LEDS_H_

#include <lib.h>

namespace lst {

const uint8_t kNumLeds = 2;

class Leds {
 public:
  Leds() { }
  ~Leds() { }
  
  void Init();
  
  void set(uint8_t channel, bool value) {
    leds_[channel] = value;
  }

  void Write();

 private:
  bool leds_[kNumLeds];
   
  DISALLOW_COPY_AND_ASSIGN(Leds);
};

}  // namespace lst

#endif  // LST_DRIVERS_LEDS_H_

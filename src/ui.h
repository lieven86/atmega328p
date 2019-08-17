#ifndef LST_UI_H_
#define LST_UI_H_

#include <avr/io.h>
#include <lib.h>
#include <drivers/system_clock.h>
#include <drivers/adc.h>
#include <drivers/leds.h>
#include <drivers/switches.h>

namespace lst {

const uint8_t kFinePotDivider = 8;
const uint8_t kNumPots = 3;

enum FeatureMode {
  FEAT_MODE_3 = 0, // select osc mod
  FEAT_MODE_2 = 1, // select logic type between sync inputs
  FEAT_MODE_1 = 2, // select digital out
  FEAT_MODE_LAST
};

enum UiMode {
  UI_MODE_SPLASH,
  UI_MODE_NORMAL
};

class Ui {
 public:
  Ui() { }
  ~Ui() { }
  
  void Init(Adc* adc);
  //void Init();
  void Poll();

  uint16_t coarse(uint8_t channel) {
    return pot_coarse_value_[channel];
  }

  inline FeatureMode feat_mode() const { return feat_mode_; }
  inline UiMode mode() const { return mode_; }

 private:
  void OnSwitchPressed();
  void OnSwitchReleased(int32_t t);

  uint16_t pot_value_[6];
  uint16_t pot_filtered_value_[6];
  uint16_t pot_coarse_value_[6];

  uint32_t press_time_[kNumSwitches];
  bool detect_very_long_press_[kNumSwitches];
  bool catchup_state_[6];

  int32_t animation_counter_;
  int8_t ignore_releases_;
  uint8_t switchState;
  bool pressed;

  Leds leds_;
  Switches switches_;
  Adc *adc_;

  UiMode mode_;
  FeatureMode feat_mode_;
  //App* app_;

  uint8_t padding[2];

  uint16_t version_token_;

  DISALLOW_COPY_AND_ASSIGN(Ui);
};

}  // namespace lst

#endif  // LST_UI_H_

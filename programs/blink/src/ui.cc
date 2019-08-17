#include <ui.h>
#include <math.h>
//#include <stdlib.h>

namespace lst {

using namespace std;
using namespace lib;

const int32_t kLongPressDuration = 500;
const int32_t kVeryLongPressDuration = 2000;
const int32_t kPotMoveThreshold = 1; 
const uint16_t kCatchupThreshold = 1 << 10;
//const uint8_t kNumLeds = 2;

void Ui::Init(Adc* adc) {
  adc_ = adc;
  leds_.Init();
  switches_.Init();

  feat_mode_ = FEAT_MODE_3;
  mode_ = UI_MODE_NORMAL;

  animation_counter_ = 0;
  ignore_releases_ = 0;
  
  switchState = 1;
  pressed = false;
  press_time_[0] = 0;
  detect_very_long_press_[0] = false;
}

void Ui::Poll() {
  // switches_.Debounce();
  // check switches
  // if button is pressed & check how long
  switchState = PINB & (0x01<<0);
  if (switchState == 0x00 && !pressed) { // justPressed
    press_time_[0] = system_clock.milliseconds();
    detect_very_long_press_[0] = false;
    pressed = true;
  }

  if (!switchState && press_time_[0]) {
    int32_t pressed_time = system_clock.milliseconds() - press_time_[0];
    
    if (!detect_very_long_press_[0]) {
      if (pressed_time > kLongPressDuration) { // longPressed
        OnSwitchReleased(pressed_time);
        detect_very_long_press_[0] = true;
      }
    } else {
      if (pressed_time > kVeryLongPressDuration) { // veryLongPressed
        OnSwitchReleased(pressed_time);
        detect_very_long_press_[0] = false;
        press_time_[0] = 0;
        pressed = false;
      }
    }
  } 
  if ((switchState == 0x01) && press_time_[0] != 0 && !detect_very_long_press_[0]) { // pressRelease
    OnSwitchReleased(system_clock.milliseconds() - press_time_[0] + 1);
    press_time_[0] = 0;
    detect_very_long_press_[0] = false;
    pressed = false;
  }

  // filter the pot values and emit events when changed
  for (uint8_t i = 0; i < 4; ++i) {
    uint16_t adc_value = adc_->value(i);
    int32_t value = (31 * pot_filtered_value_[i] + adc_value) >> 5;
    pot_filtered_value_[i] = value;
    int32_t current_value = static_cast<int32_t>(pot_value_[i]);
    if ((value >= current_value + kPotMoveThreshold) || (value <= current_value - kPotMoveThreshold)) {
      //if (abs(value - pot_coarse_value_[i]) < kCatchupThreshold) {
        pot_coarse_value_[i] = value;
        //catchup_state_[i] = false;
      // }
      pot_value_[i] = value;
    }
  }

  // paint leds
  uint8_t pins[2] = {1, 2}; // set pinnumbers
  const uint8_t binaryCounter[][2] = {{1, 0}, {0, 1}, {1, 1}, {0, 0}};
  
  switch (mode_) { 
    case UI_MODE_SPLASH:
      break;
    case UI_MODE_NORMAL:
      for (uint8_t i=0; i < 2; i++) {
        if ((binaryCounter[feat_mode_][i] == 1)) {
          PORTB |= 1 << pins[i]; //leds_.set(i, i == page_mode_);
        } else {
          PORTB &= ~(1<< pins[i]);
        }
      }
      break;
  }
}

void Ui::OnSwitchPressed() {
  //
}

void Ui::OnSwitchReleased(int32_t t) {
  if (t > kVeryLongPressDuration) {
    //
  } else if (t > kLongPressDuration) {
    //
  } else {
    switch (mode_) { 
      case UI_MODE_SPLASH:
        break;
      case UI_MODE_NORMAL:
        feat_mode_ = static_cast<FeatureMode>((feat_mode_ + 1) % FEAT_MODE_LAST);
        break;
    }
  }
}

}  // namespace lst

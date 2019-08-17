#include <app/app.h>

namespace lst {

void App::Init(Ui *ui, Adc *adc, Dac *dac) {
    ui_ = ui;
    adc_ = adc; 
    dac_ = dac;

    delayCount = 0;
    value = false;
}

void App::Process() {
    //int16_t knob1 = adc_->value(0) << 4;
    //uint8_t knob2 = adc_->value8(2) >> 1;
    //uint8_t knob3 = adc_->value8(1) >> 5;
    //int16_t cv1 = adc_->value(3) << 2;

    // read gates
    //uint8_t dig_in_1 = !(PINC & (0x01 << 3));
    //uint8_t dig_in_2 = !(PINC & (0x01 << 4));

    if (delayCount == 5000) {
        delayCount = 0;
        value = !value;
    } else {
        delayCount++;
    }

    dac_->Set(0, value ? UINT8_MAX - 1 : 0);
    dac_->Set(1, value ? UINT8_MAX - 1 : 0);

}

}

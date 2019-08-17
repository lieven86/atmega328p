#ifndef LST_APP_H
#define LST_APP_H

#include <lib.h>
#include <drivers/adc.h>
#include <drivers/dac.h>
#include <ui.h>

namespace lst {

const uint8_t kNumtriggers = 1;

class App {
    public:
        App() { }
        ~App() { }

        void Init(Ui *ui, Adc *adc, Dac *dac);
        void Process();

    private:
        Ui *ui_;
        Adc *adc_;
        Dac *dac_;
        
        int16_t delayCount;
        bool value;
        
        DISALLOW_COPY_AND_ASSIGN(App);
};
}

#endif // LST_APP_H

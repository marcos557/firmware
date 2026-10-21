#pragma once
#include "Module.h"

class RainGaugeModule : public Module {
public:
    RainGaugeModule();
    void sendReport();
    static void onPulse();

private:
    static volatile uint32_t pulseCount;
    static RainGaugeModule* instance;
    volatile bool newPulse;
};

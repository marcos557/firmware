
#include "RainGaugeModule.h"
#include "Arduino.h"

#define PIN_PLUVIOMETRO 22

volatile uint32_t RainGaugeModule::pulseCount = 0;
RainGaugeModule* RainGaugeModule::instance = nullptr;

RainGaugeModule::RainGaugeModule() : Module("RainGauge"), newPulse(false) {
    instance = this;
    pinMode(PIN_PLUVIOMETRO, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_PLUVIOMETRO), onPulse, FALLING);
}

void RainGaugeModule::onPulse() {
    static unsigned long lastPulseTime = 0;
    unsigned long currentTime = millis();
    if (currentTime - lastPulseTime > 100) { // 100ms debounce
        pulseCount++;
        if (instance) instance->newPulse = true;
        lastPulseTime = currentTime;
    }
}


void RainGaugeModule::sendReport() {
    if (newPulse) {
        float totalRain = pulseCount * 0.4;
        String msg = "VAL: " + String(totalRain, 1) ;
     serviceMessages->sendText(msg.c_str());
        newPulse = false;
    }
}

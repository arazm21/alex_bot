#include <Arduino.h>
#include <esp32-hal-ledc.h>   // Provides ledcAttach, ledcWrite, ledcDetach, etc.
#include "DRV8871.h"

DRV8871::DRV8871(uint8_t in1Pin, uint8_t in2Pin, uint32_t freq, uint8_t res)
  : _in1Pin(in1Pin), _in2Pin(in2Pin),
    _frequency(freq), _resolution(res)
{
    // Compute duty-cycle limits
    _maxDutyCycle = (1UL << _resolution) - 1;
    _minDutyCycle = 0.45 * _maxDutyCycle;  // adjust to your motor/voltage
}

void DRV8871::init() {
    // Initialize pins low
    pinMode(_in1Pin, OUTPUT);
    pinMode(_in2Pin, OUTPUT);
    digitalWrite(_in1Pin, LOW);
    digitalWrite(_in2Pin, LOW);

    // ESP32-LEDC: attach both pins with the desired PWM settings :contentReference[oaicite:6]{index=6}
    ledcAttach(_in1Pin, _frequency, _resolution);
    ledcAttach(_in2Pin, _frequency, _resolution);
}

void DRV8871::setMotor(uint8_t direction, uint8_t speedPercent) {
    // Clamp speed and map to duty cycle
    speedPercent = constrain(speedPercent, 0, 100);
    uint32_t duty = map(speedPercent, 0, 100, _minDutyCycle, _maxDutyCycle);

    if (direction == MOTOR_FORWARD) {
        ledcWrite(_in1Pin, duty);   // new API uses pin, not channel :contentReference[oaicite:7]{index=7}
        ledcWrite(_in2Pin, 0);
    } else {
        ledcWrite(_in2Pin, duty);
        ledcWrite(_in1Pin, 0);
    }
}

void DRV8871::stopMotor() {
    // Detach both pins (optional) or just write zero :contentReference[oaicite:8]{index=8}
    ledcWrite(_in1Pin, 0);
    ledcWrite(_in2Pin, 0);
    // ledcDetach(_in1Pin);
    // ledcDetach(_in2Pin);
}


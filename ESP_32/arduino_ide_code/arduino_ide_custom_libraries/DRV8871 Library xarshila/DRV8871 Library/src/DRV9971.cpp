#include "DRV8871.h"

DRV8871::DRV8871(uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmChannel1, uint8_t pwmChannel2, uint32_t freq, uint8_t res)
  : _in1Pin(in1Pin), _in2Pin(in2Pin),
    _pwmChannel1(pwmChannel1), _pwmChannel2(pwmChannel2),
    _frequency(freq), _resolution(res)
{
    _maxDutyCycle = (1UL << _resolution) - 1;
    _minDutyCycle = 0.45 * _maxDutyCycle;
}

void DRV8871::init() {
    pinMode(_in1Pin, OUTPUT);
    pinMode(_in2Pin, OUTPUT);
    digitalWrite(_in1Pin, LOW);
    digitalWrite(_in2Pin, LOW);

#if defined(ESP32)
    ledcSetup(_pwmChannel1, _frequency, _resolution);
    ledcSetup(_pwmChannel2, _frequency, _resolution);

    ledcAttachPin(_in1Pin, _pwmChannel1);
    ledcAttachPin(_in2Pin, _pwmChannel2);
#else
    #error "DRV8871 library currently supports only ESP32 using LEDC PWM"
#endif
}

void DRV8871::setMotor(uint8_t direction, uint8_t speedPercent) {
    speedPercent = constrain(speedPercent, 0, 100);
    uint32_t dutyCycle = map(speedPercent, 0, 100, _minDutyCycle, _maxDutyCycle);

#if defined(ESP32)
    if (direction == MOTOR_FORWARD) {
        ledcWrite(_pwmChannel1, dutyCycle);
        ledcWrite(_pwmChannel2, 0);
    } else if (direction == MOTOR_REVERSE) {
        ledcWrite(_pwmChannel2, dutyCycle);
        ledcWrite(_pwmChannel1, 0);
    }
#endif
}

void DRV8871::stopMotor() {
#if defined(ESP32)
    ledcWrite(_pwmChannel1, 0);
    ledcWrite(_pwmChannel2, 0);
#endif
}


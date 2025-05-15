#ifndef DRV8871_H
#define DRV8871_H

#include <Arduino.h>

#if defined(ESP32)
  #include <driver/ledc.h>
#endif

#define MOTOR_FORWARD 0
#define MOTOR_REVERSE 1

class DRV8871 {
public:
    DRV8871(uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmChannel1, uint8_t pwmChannel2, uint32_t freq = 5000, uint8_t res = 10);
    void init();
    void setMotor(uint8_t direction, uint8_t speedPercent);
    void stopMotor();

private:
    uint8_t _in1Pin, _in2Pin;
    uint8_t _pwmChannel1, _pwmChannel2;
    uint32_t _frequency;
    uint8_t _resolution;
    uint32_t _maxDutyCycle;
    uint32_t _minDutyCycle;
};

#endif // DRV8871_H


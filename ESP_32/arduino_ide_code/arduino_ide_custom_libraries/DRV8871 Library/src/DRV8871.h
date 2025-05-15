#ifndef DRV8871_H
#define DRV8871_H

#include <Arduino.h>

// Direction constants
#define MOTOR_FORWARD 0
#define MOTOR_REVERSE 1

class DRV8871 {
public:
    // Constructor: supply two GPIO pins, PWM frequency (Hz), and resolution (bits)
    DRV8871(uint8_t in1Pin, uint8_t in2Pin, uint32_t freq = 5000, uint8_t res = 10);

    // Must be called in setup()
    void init();

    // direction: MOTOR_FORWARD or MOTOR_REVERSE; speedPercent: 0–100
    void setMotor(uint8_t direction, uint8_t speedPercent);

    // Immediately stops the motor
    void stopMotor();

private:
    uint8_t _in1Pin, _in2Pin;
    uint32_t _frequency;
    uint8_t _resolution;
    uint32_t _maxDutyCycle;
    uint32_t _minDutyCycle;
};

#endif // DRV8871_H


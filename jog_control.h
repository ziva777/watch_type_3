#ifndef _JOG_CONTROL_H_
#define _JOG_CONTROL_H_

#include "potentiometer.h"

class JogControl {
  public:
    enum STATE {
      MINIMUM,
      MINIMUM_HARD,
      MAXIMUM,
      MAXIMUM_HARD,
      MEDIUM
    };

    STATE state() const { return state_; }

    JogControl(uint8_t pin) : potentiometer_(pinouts::potentiometer) {
      potentiometer_.setup(potentiometer_.raw_read());
    }

    uint16_t value() const { return value_; }
    uint16_t max_value() const { return potentiometer_.max_value(); }

    void update() {
      value_ = potentiometer_.read();

      if (value_ == 0 and pressed_time_ == 0) {
        pressed_time_ = millis();
        state_ = MINIMUM;
      } else if (value_ == 0 and pressed_time_ != 0) {
        if (millis() - pressed_time_ > HARD_PRESS_TIMEOUT) {
          state_ = MINIMUM_HARD;
        }
      } else if (value_ == potentiometer_.max_value() and pressed_time_ == 0) {
        pressed_time_ = millis();
        state_ = MAXIMUM;
      } else if (value_ == potentiometer_.max_value() and pressed_time_ != 0) {
        if (millis() - pressed_time_ > HARD_PRESS_TIMEOUT) {
          state_ = MAXIMUM_HARD;
        }
      } else {
        pressed_time_ = 0;
        state_ = MEDIUM;
      }
    }

  private:
    const uint16_t HARD_PRESS_TIMEOUT = 1000; // mS
    Potentiometer<16, 1023> potentiometer_;
    uint32_t pressed_time_ {0};
    uint16_t value_ {0};
    STATE state_ {MEDIUM};
};

#endif // _JOG_CONTROL_H_

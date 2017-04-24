#ifndef _CLOCK_CONTROLLER_H_
#define _CLOCK_CONTROLLER_H_

#include "settings.h"
#include "clock.h"
#include "clock_oscillator.h"
#include "jog_control.h"

class ClockController {
  public:
    void update(Clock &clock, ClockOscillator &oscillator) {
      jog_control_.update();
      JogControl::STATE jog_control_state = jog_control_.state();

      if (clock.fsm().is_edit()) {
        handle_edit_modes_(clock, oscillator, jog_control_state);
      } else {
        handle_non_edit_modes_(clock, jog_control_state);
      }
    }

  private:
    JogControl jog_control_ {pinouts::potentiometer};
    JogControl::STATE jog_control_state_last_ {JogControl::MEDIUM};
    uint32_t delay_timer_ {0}; // for repeat timeout
    bool stop_inc_ {false}; // for once

    static const uint16_t JOG_CONTROL_THRESHOLD_1 = 5;
    static const uint16_t JOG_CONTROL_THRESHOLD_2 = 7;
    static const uint16_t JOG_CONTROL_THRESHOLD_3 = 14;
    static const uint16_t JOG_CONTROL_THRESHOLD_4 = 28;
    static const uint16_t JOG_CONTROL_THRESHOLD_5 = 40;
    static const uint16_t JOG_CONTROL_THRESHOLD_6 = 50;
    static const uint16_t JOG_CONTROL_THRESHOLD_7 = 60;
    static const uint16_t JOG_CONTROL_THRESHOLD_8 = 63;

    // static const uint16_t JOG_CONTROL_THRESHOLD_1_REPEAT_TIMEOUT = inf;
    // static const uint16_t JOG_CONTROL_THRESHOLD_2_REPEAT_TIMEOUT = inf;
    static const uint16_t JOG_CONTROL_THRESHOLD_3_REPEAT_TIMEOUT = 1000;
    static const uint16_t JOG_CONTROL_THRESHOLD_4_REPEAT_TIMEOUT = 500;
    static const uint16_t JOG_CONTROL_THRESHOLD_5_REPEAT_TIMEOUT = 250;
    static const uint16_t JOG_CONTROL_THRESHOLD_6_REPEAT_TIMEOUT = 100;
    static const uint16_t JOG_CONTROL_THRESHOLD_7_REPEAT_TIMEOUT = 100;
    static const uint16_t JOG_CONTROL_THRESHOLD_8_REPEAT_TIMEOUT = 10;

    void inc_time_once_(Clock &clock) {
      if (not stop_inc_) {
        clock.ts().inc_time();
        stop_inc_ = true;
      }
    }

    void reset_inc_time_once_() {
      stop_inc_ = false;
    }

    void inc_time_by_timeout_(Clock &clock, uint16_t timeout) {
      if (millis() - delay_timer_ > timeout) {
        delay_timer_ = millis();
        clock.ts().inc_time();
      }
    }

    void inc_date_once_(Clock &clock) {
      if (not stop_inc_) {
        clock.ts().inc_date();
        stop_inc_ = true;
      }
    }

    void reset_inc_date_once_() {
      stop_inc_ = false;
    }

    void inc_date_by_timeout_(Clock &clock, uint16_t timeout) {
      if (millis() - delay_timer_ > timeout) {
        delay_timer_ = millis();
        clock.ts().inc_date();
      }
    }

    void inc_year_once_(Clock &clock) {
      if (not stop_inc_) {
        clock.ts().inc_date_year();
        stop_inc_ = true;
      }
    }

    void reset_inc_year_once_() {
      stop_inc_ = false;
    }

    void inc_year_by_timeout_(Clock &clock, uint16_t timeout) {
      if (millis() - delay_timer_ > timeout) {
        delay_timer_ = millis();
        clock.ts().inc_date_year();
      }
    }

    void inc_timeshift_once_(ClockOscillator &oscillator) {
      if (not stop_inc_) {
        oscillator.inc_timeshift();
        stop_inc_ = true;
      }
    }

    void reset_inc_timeshift_once_() {
      stop_inc_ = false;
    }

    void inc_timeshift_by_timeout_(ClockOscillator &oscillator, uint16_t timeout) {
      if (millis() - delay_timer_ > timeout) {
        delay_timer_ = millis();
        oscillator.inc_timeshift();
      }
    }

    void handle_non_edit_modes_(Clock &clock, JogControl::STATE jog_control_state) {
        if (jog_control_state == JogControl::MAXIMUM) {
          if (jog_control_state_last_ != jog_control_state) {
            clock.fsm().next_state();
          }
        } else if (jog_control_state == JogControl::MINIMUM_HARD) {
          if (jog_control_state_last_ != jog_control_state) {
            clock.fsm().begin_edit();
          }
        }

        jog_control_state_last_ = jog_control_state;
    }

    void handle_edit_modes_(Clock &clock, ClockOscillator &oscillator, JogControl::STATE jog_control_state) {
      if (jog_control_state == JogControl::MINIMUM_HARD) {
        if (jog_control_state_last_ != jog_control_state) {
          clock.fsm().end_edit();
        }
      } else if (jog_control_state == JogControl::MINIMUM) {
        if (jog_control_state_last_ != jog_control_state) {
          clock.fsm().next_edit_state();
        }
      } else if (jog_control_state == JogControl::MEDIUM or
                 jog_control_state == JogControl::MAXIMUM or
                 jog_control_state == JogControl::MAXIMUM_HARD) 
      {
        uint16_t value = jog_control_.value();
        ClockFSM::STATE state = clock.fsm().state();

        if (value > JOG_CONTROL_THRESHOLD_1)
          clock.on_the_run();
        else
          clock.off_the_run();

        if (state == ClockFSM::MODE_EDIT_TIME) {
          inc_time_logic_(clock, value);
        } else if (state == ClockFSM::MODE_EDIT_SECONDS) {
          if (value > JOG_CONTROL_THRESHOLD_1) {
            clock.ts().freeze_seconds();
          }
        } else if (state == ClockFSM::MODE_EDIT_DATE) {
          inc_date_logic_(clock, value);
        } else if (state == ClockFSM::MODE_EDIT_DATE_YEAR) {
          inc_date_year_logic_(clock, value);
        } else if (state == ClockFSM::MODE_ACCURACY_TUNE) {
          inc_accuracy_tune_logic_(oscillator, value);
        }
      }

      jog_control_state_last_ = jog_control_state;
    }

    void inc_time_logic_(Clock &clock, uint16_t value) {
      if (value > JOG_CONTROL_THRESHOLD_1) {
        if (value == JOG_CONTROL_THRESHOLD_8) {
          inc_time_by_timeout_(clock, JOG_CONTROL_THRESHOLD_8_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_7) {
          inc_time_by_timeout_(clock, JOG_CONTROL_THRESHOLD_7_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_6) {
          inc_time_by_timeout_(clock, JOG_CONTROL_THRESHOLD_6_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_5) {
          inc_time_by_timeout_(clock, JOG_CONTROL_THRESHOLD_5_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_4) {
          inc_time_by_timeout_(clock, JOG_CONTROL_THRESHOLD_4_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_3) {
          inc_time_by_timeout_(clock, JOG_CONTROL_THRESHOLD_3_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_2) {
          inc_time_once_(clock);                  
        } else {
          reset_inc_time_once_();
        }
      }
    }

    void inc_date_logic_(Clock &clock, uint16_t value) {
      if (value > JOG_CONTROL_THRESHOLD_1) {
        if (value == JOG_CONTROL_THRESHOLD_8) {
          inc_date_by_timeout_(clock, JOG_CONTROL_THRESHOLD_8_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_7) {
          inc_date_by_timeout_(clock, JOG_CONTROL_THRESHOLD_7_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_6) {
          inc_date_by_timeout_(clock, JOG_CONTROL_THRESHOLD_6_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_5) {
          inc_date_by_timeout_(clock, JOG_CONTROL_THRESHOLD_5_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_4) {
          inc_date_by_timeout_(clock, JOG_CONTROL_THRESHOLD_4_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_3) {
          inc_date_by_timeout_(clock, JOG_CONTROL_THRESHOLD_3_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_2) {
          inc_date_once_(clock);                  
        } else {
          reset_inc_date_once_();
        }
      }
    }

    void inc_date_year_logic_(Clock &clock, uint16_t value) {
      if (value > JOG_CONTROL_THRESHOLD_1) {
        if (value == JOG_CONTROL_THRESHOLD_8) {
          inc_year_by_timeout_(clock, JOG_CONTROL_THRESHOLD_8_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_7) {
          inc_year_by_timeout_(clock, JOG_CONTROL_THRESHOLD_7_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_6) {
          inc_year_by_timeout_(clock, JOG_CONTROL_THRESHOLD_6_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_5) {
          inc_year_by_timeout_(clock, JOG_CONTROL_THRESHOLD_5_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_4) {
          inc_year_by_timeout_(clock, JOG_CONTROL_THRESHOLD_4_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_3) {
          inc_year_by_timeout_(clock, JOG_CONTROL_THRESHOLD_3_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_2) {
          inc_year_once_(clock);                  
        } else {
          reset_inc_year_once_();
        }
      }
    }

    void inc_accuracy_tune_logic_(ClockOscillator &oscillator, uint16_t value) {
      if (value > JOG_CONTROL_THRESHOLD_1) {
        if (value == JOG_CONTROL_THRESHOLD_8) {
          inc_timeshift_by_timeout_(oscillator, JOG_CONTROL_THRESHOLD_8_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_7) {
          inc_timeshift_by_timeout_(oscillator, JOG_CONTROL_THRESHOLD_7_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_6) {
          inc_timeshift_by_timeout_(oscillator, JOG_CONTROL_THRESHOLD_6_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_5) {
          inc_timeshift_by_timeout_(oscillator, JOG_CONTROL_THRESHOLD_5_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_4) {
          inc_timeshift_by_timeout_(oscillator, JOG_CONTROL_THRESHOLD_4_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_3) {
          inc_timeshift_by_timeout_(oscillator, JOG_CONTROL_THRESHOLD_3_REPEAT_TIMEOUT);
        } else if (value > JOG_CONTROL_THRESHOLD_2) {
          inc_timeshift_once_(oscillator);                  
        } else {
          reset_inc_timeshift_once_();
        }
      }
    }
};

#endif // _CLOCK_CONTROLLER_H_

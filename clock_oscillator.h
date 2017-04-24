#ifndef _CLOCK_OSCILLATOR_H_
#define _CLOCK_OSCILLATOR_H_

#include "clock.h"
#include "timestamp.h"

/*
1 day = 24 hour = 1 440 min = 86 400 sec = 86 400 000 msec
Max correction per day is 10 sec = 10 000 msec
*/

class ClockOscillator {
  public:
    void set_timestamp_swing_interval(uint16_t interval) {
      interval_ = interval;
    }

    uint16_t timestamp_swing_interval() const { return interval_; }

    void set_swing_step(uint16_t step) {
      step_ = step;
    }

    void set_timeshift(int32_t shift) {
      shift_ = shift;
      shift_specific_();
    }

    int32_t timeshift() const { return shift_; }
    int32_t shift_per_hour() const { return shift_per_hour_; };
    int32_t shift_per_day_tail() const { return shift_per_day_tail_; };

    void inc_timeshift() {
      if (++shift_ > SHIFT_ABS_MAX) {
        shift_ = -SHIFT_ABS_MAX;
      }
      shift_specific_();
    }

    void swing(Timestamp &ts) {
      tick_counter_ += step_;

      if (tick_counter_ == interval_) {
        tick_counter_ = 0;
        ts.inc();
      } else if (tick_counter_ >= interval_) {
        tick_counter_ %= interval_;
        ts.inc();
      }
    }

  private:
    uint16_t tick_counter_ {0};
    uint16_t interval_ {0};
    uint16_t step_ {0};

    const int32_t SHIFT_ABS_MAX = 9999;
    int32_t shift_ {0};
    int32_t shift_per_hour_ {0};
    int32_t shift_per_day_tail_ {0};

    void shift_specific_() {
      shift_per_hour_ = shift_ / 24;
      shift_per_day_tail_ = shift_ - shift_per_hour_ * 24;

      // Serial.print("shift_per_hour_ ");
      // Serial.println(shift_per_hour_);
      // Serial.print("shift_per_day_tail_ ");
      // Serial.println(shift_per_day_tail_);
      // Serial.println();
    }
};

#endif // _CLOCK_OSCILLATOR_H_



// #ifndef _CLOCK_OSCILLATOR_H_
// #define _CLOCK_OSCILLATOR_H_

// #include "clock.h"
// #include "timestamp.h"

// /*
// 1 day = 24 hour = 1 440 min = 86 400 sec = 86 400 000 msec
// Max correction per day is 10 sec = 10 000 msec
// */

// class ClockOscillator {
//   public:
//     void set_timestamp_swing_interval(uint16_t interval) {
//       interval_ = interval;
//     }

//     uint16_t timestamp_swing_interval() const { return interval_; }

//     void set_swing_step(uint16_t step) {
//       step_ = step;
//     }

//     void set_timeshift(int32_t shift) {
//       shift_ = shift;
//     }

//     int32_t timeshift() const { return shift_; }

//     void inc_timeshift() {
//       if (++shift_ > SHIFT_ABS_MAX) {
//         shift_ = -SHIFT_ABS_MAX;
//       }
//     }

//     void swing(Timestamp &ts) {
//       tick_counter_ += step_;

//       if (tick_counter_ == interval_) {
//         tick_counter_ = 0;
//         ts.inc();
//       } else if (tick_counter_ >= interval_) {
//         tick_counter_ %= interval_;
//         ts.inc();
//       } else {

//       }
//     }

//   private:
//     uint16_t tick_counter_ {0};
//     uint16_t interval_ {0};
//     uint16_t step_ {0};

//     const int32_t SHIFT_ABS_MAX = 9999;
//     int32_t shift_ {0};
// };

// #endif // _CLOCK_OSCILLATOR_H_

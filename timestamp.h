#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

namespace aux {
  const uint16_t msecond_per_second = 1000;
  const uint16_t msecond_per_half_second = msecond_per_second / 2;
  const uint8_t second_overflow = 60;
  const uint8_t minute_overflow = 60;
  const uint8_t hour_overflow = 24;
  const uint8_t month_min = 1;
  const uint8_t month_max = 12;

  const uint8_t MONTH_LENGTH[] = {
      0, // dymmy
      31, // 1   January   31 days
      28, // 2   February  28 days
      31, // 3   March     31 days
      30, // 4   April     30 days
      31, // 5   May       31 days
      30, // 6   June      30 days
      31, // 7   July      31 days
      31, // 8   August    31 days
      30, // 9   September 30 days
      31, // 10  October   31 days
      30, // 11  November  30 days
      31  // 12  December  31 days
  };

  const uint8_t MONTH_LENGTH_LEAP[] = {
      0, // dymmy
      31, // 1   January   31 days
      29, // 2   February  29 in leap years
      31, // 3   March     31 days
      30, // 4   April     30 days
      31, // 5   May       31 days
      30, // 6   June      30 days
      31, // 7   July      31 days
      31, // 8   August    31 days
      30, // 9   September 30 days
      31, // 10  October   31 days
      30, // 11  November  30 days
      31  // 12  December  31 days
  };

  inline uint8_t *month_day_count(bool leap) {
    return (leap ? MONTH_LENGTH_LEAP : MONTH_LENGTH);
  }

  inline bool is_leap(uint16_t y) {
    return ((y % 4) == 0) && (((y % 100)!=0) || ((y % 400) == 0));
  }

  uint8_t day_of_week(uint16_t d, uint16_t m, uint16_t y) {
    return (d += m<3 ? y-- : y-2, 23*m/9 + d + 4 + y/4 - y/100 + y/400) % 7;
  }
};

class Timestamp {
  public:
    Timestamp() {
      leap_ = aux::is_leap(year_);
      month_day_count_ = aux::month_day_count(leap_);
      day_of_week_ = aux::day_of_week(day_, month_, year_);
      Serial.println(month_day_count_[month_]);
    }

    uint8_t hour() { return hour_; }
    uint8_t minute() { return minute_; }
    uint8_t second() { return second_; }

    uint8_t day() { return day_; }
    uint8_t month() { return month_; }
    uint16_t year() { return year_; }

    void freeze_seconds() {
      msecond_ = 0;
      second_ = 0;
    }

    void inc_time() {
      msecond_ = 0;
      second_ = 0;

      inc_minute();

      if (minute_ == 0)
        inc_hour();
    }

    void inc_date() {
      inc_day();

      if (day_ == 1) {
          inc_month();
      }
    }

    void inc_date_year() {
      inc_year();

      if (year_ > YEAR_MAX) {
        year_ = YEAR_MIN - 1;
        inc_year();
      }
    }

    void inc(uint16_t ms_tick_size) {
      msecond_ += ms_tick_size;
      uint16_t tmp = msecond_ / aux::msecond_per_second;
      msecond_ %= aux::msecond_per_second;

      for(uint16_t i = 0; i != tmp; ++i) {
          inc_second();

          if (second_ == 0) {
              inc_minute();

              if (minute_ == 0) {
                  inc_hour();

                  if (hour_ == 0) {
                      inc_day();

                      if (day_ == 1) {
                          inc_month();

                          if (month_ == 1) {
                              inc_year();
                          }
                      }
                  }
              }
          }
      }
    }

    void inc() {
      inc(tick_size_);
    }

    bool pendel_1_hz() {
      return msecond_ >= aux::msecond_per_half_second;
    }

    void set_tick_size(uint16_t tick_size) {
      tick_size_ = tick_size;
    }

  private:
    static const uint16_t YEAR_MAX = 2099;
    static const uint16_t YEAR_MIN = 2017;

    uint8_t hour_ {0};
    uint8_t minute_ {0};
    uint8_t second_ {0};
    uint16_t msecond_ {0};

    uint8_t day_ {1};
    uint8_t month_ {1};
    uint16_t year_ {YEAR_MIN};
    bool leap_ {false};
    uint8_t day_of_week_;

    uint16_t tick_size_ {0}; // mS

    uint8_t *month_day_count_;

    uint8_t days_in_month() const {
      Serial.print(month_);
      Serial.print(" ");
      Serial.println(month_day_count_[month_]);
      return month_day_count_[month_];
    }

    void inc_second() {
      second_ = ++second_ % aux::second_overflow;
    }

    void inc_minute() {
      minute_ = ++minute_ % aux::minute_overflow;
    }

    void inc_hour() {
      hour_ = ++hour_ % aux::hour_overflow;
    }

    void inc_day() {
      day_ = day_ % days_in_month() + aux::month_min;
      day_of_week_ = aux::day_of_week(day_, month_, year_);
    }

    void inc_month() {
      month_ = month_ % aux::month_max + aux::month_min;
      day_of_week_ = aux::day_of_week(day_, month_, year_);
    }

    void inc_year() {
      leap_ = aux::is_leap(++year_);
      month_day_count_ = aux::month_day_count(leap_);
      day_of_week_ = aux::day_of_week(day_, month_, year_);
    }
};

#endif // _TIMESTAMP_H_

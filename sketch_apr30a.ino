
#define _BV16(val) ((val) << 8)
#define _HIGH_8(val) ((val) >> 8)
#define _LOW_8(val) ((val & 0x00FF))

enum TIMER_SCALES : uint8_t {
  TIMER_OFF  = 0, // timer1 off

  TIMER1_SCALE_1     =                         _BV(CS10), // 1 - 0.0625 uS
  TIMER1_SCALE_8     =             _BV(CS11)            , // 0.5 uS
  TIMER1_SCALE_64    =             _BV(CS11) | _BV(CS10), // 4 uS
  TIMER1_SCALE_256   = _BV(CS12)                        , // 16 uS
  TIMER1_SCALE_1024  = _BV(CS12)             | _BV(CS10), // 1024 - 64 uS

  TIMER3_SCALE_1     =                         _BV(CS30), // 1 - 0.0625 uS
  TIMER3_SCALE_8     =             _BV(CS31)            , // 0.5 uS
  TIMER3_SCALE_64    =             _BV(CS31) | _BV(CS30), // 4 uS
  TIMER3_SCALE_256   = _BV(CS32)                        , // 16 uS
  TIMER3_SCALE_1024  = _BV(CS32)             | _BV(CS30), // 1024 - 64 uS

  TIMER4_SCALE_1     =                                     _BV(CS40), // 1 - 0.0625 uS
  TIMER4_SCALE_2     =                         _BV(CS41)            , // 2 - 0.125 uS
  TIMER4_SCALE_4     =                         _BV(CS41) | _BV(CS40), // 4 - 0.250 uS
  TIMER4_SCALE_8     =             _BV(CS42)                        , // 8 - 0.5 uS
  TIMER4_SCALE_16    =             _BV(CS42)             | _BV(CS40), // 16 - 1 uS
  TIMER4_SCALE_32    =             _BV(CS42) | _BV(CS41)            , // 32 - 2 uS
  TIMER4_SCALE_64    =             _BV(CS42) | _BV(CS41) | _BV(CS40), // 64 - 4 uS
  TIMER4_SCALE_128   = _BV(CS43)                                    , // 128 - 8 uS
  TIMER4_SCALE_256   = _BV(CS43) |                         _BV(CS40), // 256 - 16 uS
  TIMER4_SCALE_512   = _BV(CS43) |             _BV(CS41)            , // 512 - 32 uS
  TIMER4_SCALE_1024  = _BV(CS43) |             _BV(CS41) | _BV(CS40), // 1024 - 64 uS
  TIMER4_SCALE_2048  = _BV(CS43) | _BV(CS42)                        , // 2048 - 128 uS
  TIMER4_SCALE_4094  = _BV(CS43) | _BV(CS42)             | _BV(CS40), // 4094 - 256 uS
  TIMER4_SCALE_8192  = _BV(CS43) | _BV(CS42) | _BV(CS41)            , // 8192 - 512 uS
  TIMER4_SCALE_16384 = _BV(CS43) | _BV(CS42) | _BV(CS41) | _BV(CS40), // 16384 - 1024 uS

  DUMMY_TIMER_SCALE
};

enum TIMER_MODES : uint16_t {
  // High 8 bit is WGM13, WGM12 (TCCRxB)
  // Low 8 bit is WGM11, WGM10 (TCCRxA)
  TIMER1_MODE_0  =                                                        0, // Normal
  TIMER1_MODE_1  =                                               _BV(WGM10), // PWM PhC 8-bit
  TIMER1_MODE_2  =                                  _BV(WGM11)             , // PWM PhC 9-bit
  TIMER1_MODE_3  =                                  _BV(WGM11) | _BV(WGM10), // PWM PhC 10-bit
  TIMER1_MODE_4  = _BV16(             _BV(WGM12))                          , // CTC
  TIMER1_MODE_5  = _BV16(             _BV(WGM12))              | _BV(WGM10), // Fast PWM PhC 8-bit
  TIMER1_MODE_6  = _BV16(             _BV(WGM12)) | _BV(WGM11)             , // Fast PWM PhC 9-bit
  TIMER1_MODE_7  = _BV16(             _BV(WGM12)) | _BV(WGM11) | _BV(WGM10), // Fast PWM PhC 10-bit
  TIMER1_MODE_8  = _BV16(_BV(WGM13)             )                          , // PWM PhFC
  TIMER1_MODE_9  = _BV16(_BV(WGM13)             )              | _BV(WGM10), // PWM PhFC
  TIMER1_MODE_10 = _BV16(_BV(WGM13)             ) | _BV(WGM11)             , // PWM PhC
  TIMER1_MODE_11 = _BV16(_BV(WGM13)             ) | _BV(WGM11) | _BV(WGM10), // PWM PhC
  TIMER1_MODE_12 = _BV16(_BV(WGM13) | _BV(WGM12))                          , // CTC
  TIMER1_MODE_13 = _BV16(_BV(WGM13) | _BV(WGM12))              | _BV(WGM10), // Reserved
  TIMER1_MODE_14 = _BV16(_BV(WGM13) | _BV(WGM12)) | _BV(WGM11)             , // Fast PWM
  TIMER1_MODE_15 = _BV16(_BV(WGM13) | _BV(WGM12)) | _BV(WGM11) | _BV(WGM10), // Fast PWM

  // High 8 bit is WGM33, WGM32 (TCCRxB)
  // Low 8 bit is WGM31, WGM30 (TCCRxA)
  TIMER3_MODE_0  =                                                        0, // Normal
  TIMER3_MODE_1  =                                               _BV(WGM30), // PWM PhC 8-bit
  TIMER3_MODE_2  =                                  _BV(WGM31)             , // PWM PhC 9-bit
  TIMER3_MODE_3  =                                  _BV(WGM31) | _BV(WGM30), // PWM PhC 10-bit
  TIMER3_MODE_4  = _BV16(             _BV(WGM32))                          , // CTC
  TIMER3_MODE_5  = _BV16(             _BV(WGM32))              | _BV(WGM30), // Fast PWM PhC 8-bit
  TIMER3_MODE_6  = _BV16(             _BV(WGM32)) | _BV(WGM31)             , // Fast PWM PhC 9-bit
  TIMER3_MODE_7  = _BV16(             _BV(WGM32)) | _BV(WGM31) | _BV(WGM30), // Fast PWM PhC 10-bit
  TIMER3_MODE_8  = _BV16(_BV(WGM33)             )                          , // PWM PhFC
  TIMER3_MODE_9  = _BV16(_BV(WGM33)             )              | _BV(WGM30), // PWM PhFC
  TIMER3_MODE_10 = _BV16(_BV(WGM33)             ) | _BV(WGM31)             , // PWM PhC
  TIMER3_MODE_11 = _BV16(_BV(WGM33)             ) | _BV(WGM31) | _BV(WGM30), // PWM PhC
  TIMER3_MODE_12 = _BV16(_BV(WGM33) | _BV(WGM32))                          , // CTC
  TIMER3_MODE_13 = _BV16(_BV(WGM33) | _BV(WGM32))              | _BV(WGM30), // Reserved
  TIMER3_MODE_14 = _BV16(_BV(WGM33) | _BV(WGM32)) | _BV(WGM31)             , // Fast PWM
  TIMER3_MODE_15 = _BV16(_BV(WGM33) | _BV(WGM32)) | _BV(WGM31) | _BV(WGM30), // Fast PWM

  DUMMY_TIMER_MODE
};

namespace pinouts {
  const uint8_t digt1_anode = 16;
  const uint8_t digt2_anode = 8;
  const uint8_t digt3_anode = 10;
  const uint8_t digt4_anode = 9;

  const uint8_t digt_a = 15;
  const uint8_t digt_b = 14;
  const uint8_t digt_c = 4;
  const uint8_t digt_d = 7;
  const uint8_t digt_e = 5;
  const uint8_t digt_f = A0;
  const uint8_t digt_g = A1;

  const uint8_t digt_dot = 6;

  const uint8_t potentiometer = A3;
}

namespace display {
  inline
  void high(uint8_t pin) {
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *out = portOutputRegister(port);
    *out |= digitalPinToBitMask(pin);
  }

  inline
  void low(uint8_t pin) {
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *out = portOutputRegister(port);
    *out &= ~digitalPinToBitMask(pin);
  }

  inline
  void highlight_segment(uint8_t pin) {
    low(pin);
  }

  inline
  void obscure_segment(uint8_t pin) {
    high(pin);
  }

  inline
  void engeage_anode(uint8_t pin) {
    high(pin);
  }

  inline
  void disengeage_anode(uint8_t pin) {
    low(pin);
  }

  namespace digit {
    // segments  dot, g, f, e, d, c, b, a
    const uint8_t empty = B00000000;
    const uint8_t zero = B00111111;
    const uint8_t one = B00000110;
    const uint8_t two = B1011011;
    const uint8_t three = B01001111;
    const uint8_t four = B01100110;
    const uint8_t five = B01101101;
    const uint8_t six = B01111101;
    const uint8_t seven = B00000111;
    const uint8_t eight = B01111111;
    const uint8_t nine = B01101111;

    const uint8_t empty_dot = _BV(7) | empty;
    const uint8_t zero_dot = _BV(7) | zero;
    const uint8_t one_dot = _BV(7) | one;
    const uint8_t two_dot = _BV(7) | two;
    const uint8_t three_dot = _BV(7) | three;
    const uint8_t four_dot = _BV(7) | four;
    const uint8_t five_dot = _BV(7) | five;
    const uint8_t six_dot = _BV(7) | six;
    const uint8_t seven_dot = _BV(7) | seven;
    const uint8_t eight_dot = _BV(7) | eight;
    const uint8_t nine_dot = _BV(7) | nine;

    inline
    bool segment_in_digit(uint8_t digit, uint8_t no) {
      return _BV(no) & digit;
    }

    inline
    int bit_count(unsigned int n) {
        n = ((0xaaaaaaaa & n) >> 1) + (0x55555555 & n);
        n = ((0xcccccccc & n) >> 2) + (0x33333333 & n);
        n = ((0xf0f0f0f0 & n) >> 4) + (0x0f0f0f0f & n);
        n = ((0xff00ff00 & n) >> 8) + (0x00ff00ff & n);
        n = ((0xffff0000 & n) >> 16) + (0x0000ffff & n);
        return n;
    }
  }
}

namespace scale {
  // Minutes consts 
  namespace minutes_per {
    const uint16_t DAY = 24U * 60U;
  }

  // Seconds consts
  namespace mseconds_per {
    const uint32_t SECOND = 1000U;
    const uint32_t MINUTE = 60U * SECOND;
    const uint32_t HOUR = 60U * MINUTE;
    const uint32_t DAY = 24U * HOUR;
  }

  // Mseconds consts
  namespace seconds_per {
    const uint32_t MINUTE = 60UL;
    const uint32_t HOUR = 60UL * MINUTE;
    const uint32_t DAY = 24U * HOUR;
  }
}

namespace defines {
  const uint8_t SECONDS_MAX = 59U;
  const uint8_t MINUTES_MAX = 59U;
  const uint8_t HOURS_MAX = 23U;

  const uint8_t SECONDS_OVERFLOW = SECONDS_MAX + 1U;
  const uint8_t MINUTES_OVERFLOW = MINUTES_MAX + 1U;
  const uint8_t HOURS_OVERFLOW = HOURS_MAX + 1U;
}

class SegmentDisplay {
  public:
    void setup() {
      pinMode(pinouts::digt1_anode, OUTPUT);
      pinMode(pinouts::digt2_anode, OUTPUT);
      pinMode(pinouts::digt3_anode, OUTPUT);
      pinMode(pinouts::digt4_anode, OUTPUT);
      pinMode(pinouts::digt_a, OUTPUT);
      pinMode(pinouts::digt_b, OUTPUT);
      pinMode(pinouts::digt_c, OUTPUT);
      pinMode(pinouts::digt_d, OUTPUT);
      pinMode(pinouts::digt_e, OUTPUT);
      pinMode(pinouts::digt_f, OUTPUT);
      pinMode(pinouts::digt_g, OUTPUT);
      pinMode(pinouts::digt_dot, OUTPUT);

      display::disengeage_anode(pinouts::digt1_anode);
      display::obscure_segment(pinouts::digt_a);
      display::obscure_segment(pinouts::digt_b);
      display::obscure_segment(pinouts::digt_c);
      display::obscure_segment(pinouts::digt_d);
      display::obscure_segment(pinouts::digt_e);
      display::obscure_segment(pinouts::digt_f);
      display::obscure_segment(pinouts::digt_g);
      display::obscure_segment(pinouts::digt_dot);
    }

    void begin_strobe() {
      if (_strobe_counter_max == 0) {
        uint8_t bits = 0;
        _curr_anode_idx = ++_curr_anode_idx % (_max_anode_idx + 1);

        if (_curr_anode_idx == 0) {
          bits = display::digit::bit_count(_digit_by_value(_A));
        } else if (_curr_anode_idx == 1) {
          bits = display::digit::bit_count(_digit_by_value(_B));
        } else if (_curr_anode_idx == 2) {
          bits = display::digit::bit_count(_digit_by_value(_C));
        } else if (_curr_anode_idx == 3) {
          bits = display::digit::bit_count(_digit_by_value(_D));
        }

        _strobe_counter_max = bits;
        _strobe_counter = 0;
      }

      if (_curr_anode_idx == 0) {
        _highlight_segments(_digit_by_value(_A));
        _anode_pin = pinouts::digt1_anode;
      } else if (_curr_anode_idx == 1) {
        _highlight_segments(_digit_by_value(_B));
        _anode_pin = pinouts::digt2_anode;
      } else if (_curr_anode_idx == 2) {
        _highlight_segments(_digit_by_value(_C));
        _anode_pin = pinouts::digt3_anode;
      } else if (_curr_anode_idx == 3) {
        _highlight_segments(_digit_by_value(_D));
        _anode_pin = pinouts::digt4_anode;
      }

      display::engeage_anode(_anode_pin);
    }

    void end_strobe() {
      display::obscure_segment(pinouts::digt_a);
      display::obscure_segment(pinouts::digt_b);
      display::obscure_segment(pinouts::digt_c);
      display::obscure_segment(pinouts::digt_d);
      display::obscure_segment(pinouts::digt_e);
      display::obscure_segment(pinouts::digt_f);
      display::obscure_segment(pinouts::digt_g);
      display::obscure_segment(pinouts::digt_dot);
      display::disengeage_anode(_anode_pin);

      if (++_strobe_counter == _strobe_counter_max) {
        _strobe_counter_max = 0;
      }
    }

    void set_A(uint8_t A) {
      _A = A % 10;
    }

    void set_B(uint8_t B) {
      _B = B % 10;
    }

    void set_C(uint8_t C) {
      _C = C % 10;
    }

    void set_D(uint8_t D) {
      _D = D % 10;
    }

    void set_ABCD(uint16_t ABCD) {
      ABCD %= 10000;

      _A = ABCD / 1000;
      _B = ABCD % 1000 / 100;
      _C = ABCD % 100 / 10;
      _D = ABCD % 10;
    }

    void set_AB(uint16_t AB) {
      AB %= 100;

      _A = AB / 10;
      _B = AB % 10;
    }

    void set_CD(uint16_t CD) {
      CD %= 100;

      _C = CD / 10;
      _D = CD % 10;
    }

    void set_dots(bool a, bool b, bool c, bool d) {
      _A = _A % 10 + (a ? 10 : 0);
      _B = _B % 10 + (b ? 10 : 0);
      _C = _C % 10 + (c ? 10 : 0);
      _D = _D % 10 + (d ? 10 : 0);
    }
  private:
    uint8_t _strobe_counter {0};
    uint8_t _strobe_counter_max {0};

    uint8_t _anode_pin {0};
    uint8_t _curr_anode_idx {3};
    const uint8_t _max_anode_idx {3};

    volatile uint8_t _A {8};
    volatile uint8_t _B {11};
    volatile uint8_t _C {2};
    volatile uint8_t _D {3};

    volatile bool _A_dot {false};
    volatile bool _B_dot {true};
    volatile bool _C_dot {false};
    volatile bool _D_dot {false};

    inline
    uint8_t _digit_by_value(uint8_t v) const {
      switch (v) {
        case 0: {
          return display::digit::zero;
          break;
        }
        case 1: {
          return display::digit::one;
          break;
        }
        case 2: {
          return display::digit::two;
          break;
        }
        case 3: {
          return display::digit::three;
          break;
        }
        case 4: {
          return display::digit::four;
          break;
        }
        case 5: {
          return display::digit::five;
          break;
        }
        case 6: {
          return display::digit::six;
          break;
        }
        case 7: {
          return display::digit::seven;
          break;
        }
        case 8: {
          return display::digit::eight;
          break;
        }
        case 9: {
          return display::digit::nine;
          break;
        }

        case 10: {
          return display::digit::zero_dot;
          break;
        }
        case 11: {
          return display::digit::one_dot;
          break;
        }
        case 12: {
          return display::digit::two_dot;
          break;
        }
        case 13: {
          return display::digit::three_dot;
          break;
        }
        case 14: {
          return display::digit::four_dot;
          break;
        }
        case 15: {
          return display::digit::five_dot;
          break;
        }
        case 16: {
          return display::digit::six_dot;
          break;
        }
        case 17: {
          return display::digit::seven_dot;
          break;
        }
        case 18: {
          return display::digit::eight_dot;
          break;
        }
        case 19: {
          return display::digit::nine_dot;
          break;
        }

        case 20: {
          return display::digit::empty;
          break;
        }

        case 30: {
          return display::digit::empty_dot;
          break;
        }

        default : {
          return display::digit::empty;
          break;
        }
      }
    }

    inline
    void _highlight_segments(uint8_t digit) {
      if (display::digit::segment_in_digit(digit, 0))
        display::highlight_segment(pinouts::digt_a);

      if (display::digit::segment_in_digit(digit, 1))
        display::highlight_segment(pinouts::digt_b);

      if (display::digit::segment_in_digit(digit, 2))
        display::highlight_segment(pinouts::digt_c);

      if (display::digit::segment_in_digit(digit, 3))
        display::highlight_segment(pinouts::digt_d);

      if (display::digit::segment_in_digit(digit, 4))
        display::highlight_segment(pinouts::digt_e);

      if (display::digit::segment_in_digit(digit, 5))
        display::highlight_segment(pinouts::digt_f);

      if (display::digit::segment_in_digit(digit, 6))
        display::highlight_segment(pinouts::digt_g);

      if (display::digit::segment_in_digit(digit, 7))
        display::highlight_segment(pinouts::digt_dot);
    }
};

class Timestamp {
  public:
    uint8_t hour() const { return _hour; };
    uint8_t minute() const { return _minute; };
    uint8_t second() const { return _second; };
    uint16_t msec() const { return _msec; };

    void set_hms(uint8_t h, uint8_t m, uint8_t s) {
      _hour = h;
      _minute = m;
      _second = s;
      _msec = 0;
    }

    void add_msecs(uint16_t ms) {
      uint16_t sec_ovf;

      _msec += ms;
      sec_ovf = _msec / scale::mseconds_per::SECOND;
      _msec %= scale::mseconds_per::SECOND;

      for(uint16_t i = 0; i != sec_ovf; ++i) {
        if (++_second == defines::SECONDS_OVERFLOW) {
          _second = 0;

          if (++_minute == defines::MINUTES_OVERFLOW) {
            _minute = 0;

            if (++_hour == defines::HOURS_OVERFLOW) {
              _hour = 0;
            }
          }
        }
      }
    }
  private:
    volatile uint8_t _hour {0};
    volatile uint8_t _minute {0};
    volatile uint8_t _second {0};
    volatile uint16_t _msec {0};
};

class Oscillator {
  public:
    void bind(Timestamp *ts) {
      _timestamp = ts;
    }

    void set_day_drift(int16_t ms) {
      _day_drift = ms;
    }

    void set_step(uint16_t ms) {
      _step = ms;
    }

    void calc_shift() {
      if (_day_drift)
        _step_counter_max = scale::mseconds_per::DAY / abs(_day_drift);
    }

    void swing() {
      if (_day_drift) {
        if (++_step_counter >= _step_counter_max) {
          _step_counter -= _step_counter_max;

          if (_day_drift < 0) {
            return;
          } else {
            _timestamp->add_msecs(_step);
          }
        }
      }

      _timestamp->add_msecs(_step);
    }
  private:
    int16_t _day_drift {0};
    uint16_t _step {1};
    uint32_t _step_counter {0};
    uint32_t _step_counter_max {0};
    Timestamp *_timestamp {NULL};
};

class AlarmClockGadget {
  public:
    AlarmClockGadget() {
      _timestamp.set_hms(12, 15, 01);
      _oscillator.set_step(100);
      _oscillator.set_day_drift(0);
      _oscillator.calc_shift();
      _oscillator.bind(&_timestamp);
    }

    SegmentDisplay & display() {
      return _display;
    }

    Timestamp & timestamp() {
      return _timestamp;
    }

    void sync() {
      _oscillator.swing();
      _display.set_AB(_timestamp.hour());
      _display.set_CD(_timestamp.minute());
    }
  private:
    SegmentDisplay _display;
    Timestamp _timestamp;
    Oscillator _oscillator;
};

AlarmClockGadget gadget;

// Timer 1 int handlers
ISR(TIMER1_COMPA_vect) {
  gadget.display().begin_strobe();
}

ISR(TIMER1_COMPB_vect) {
  gadget.display().end_strobe();
}

ISR(TIMER1_COMPC_vect) {
  // RXLED0;
}

// Timer 4 int handlers
ISR(TIMER4_COMPA_vect) {
  gadget.sync();
}

ISR(TIMER4_COMPB_vect) {

}

ISR(TIMER4_COMPD_vect) {

}

void setup_timer1(TIMER_SCALES scale, TIMER_MODES mode, uint16_t top,
                  uint16_t top_b, uint16_t top_c) 
{
  uint8_t mode_a = _LOW_8(mode);
  uint8_t mode_b = _HIGH_8(mode);

  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 0;
  OCR1B = 0;
  OCR1C = 0;

  TCNT1 = 0;

  TCCR1A |= mode_a;
  TCCR1B |= mode_b;
  TCCR1B |= scale;

  OCR1A = top;
  OCR1B = top_b;
  OCR1C = top_c;

  TIMSK1 = _BV(OCIE1A) | _BV(OCIE1B) | _BV(OCIE1C);
  sei();
}

void setup_timer4(TIMER_SCALES scale, uint16_t top, 
                  uint16_t top_a, uint16_t top_b, uint16_t top_c) 
{
  cli();
  TCCR4A = 0;
  TCCR4B = 0;
  TCCR4C = 0;
  TCCR4D = 0;
  TCCR4E = 0;

  TCNT4 = 0;

  OCR4A = 0;
  OCR4B = 0;
  OCR4C = 0;
  OCR4D = 0;

  TCCR4B |= scale;

  TC4H = top >> 8;
  OCR4C = top & 0xFF;

  TC4H = top_a >> 8;
  OCR4A = top_a & 0xFF;

  TC4H = top_b >> 8;
  OCR4B = top_b & 0xFF;

  TC4H = top_c >> 8;
  OCR4D = top_c & 0xFF;

  TIMSK4 = _BV(OCIE4A) | _BV(OCIE4B) | _BV(OCIE4D);
  sei();
}

void setup() {
  gadget.display().setup();
  setup_timer1(TIMER1_SCALE_64, TIMER1_MODE_4,
               // 32-1, 30-1, 0);
               // 64-1, 60-1, 0);
               128-1, 120-1, 0);
               // 256-1, 200-1, 0);
               // 512-1, 500-1, 0);
               // 1023-1, 1000-1, 0);
  setup_timer4(TIMER4_SCALE_64, 25000-1, 00, 0, 0);
}

uint16_t v = 0;
uint8_t d = 0;

void loop() {
  // gadget.display().set_ABCD(v);
  // gadget.display().set_dots(0, d++, 0, 0);
  // v = ++v % 10000;
  // d %= 2;
  // delay(1000);
}

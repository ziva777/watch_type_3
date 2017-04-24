#ifndef _CLOCK_DISPLAY_H_
#define _CLOCK_DISPLAY_H_

#include "settings.h"

class Display {
  public:
    void setup() {
      pinMode(pinouts::dig1_anode, OUTPUT);
      pinMode(pinouts::dig2_anode, OUTPUT);
      pinMode(pinouts::dig3_anode, OUTPUT);
      pinMode(pinouts::dig4_anode, OUTPUT);

      pinMode(pinouts::dig1_a, OUTPUT);
      pinMode(pinouts::dig1_b, OUTPUT);
      pinMode(pinouts::dig1_c, OUTPUT);
      pinMode(pinouts::dig1_d, OUTPUT);
      pinMode(pinouts::dig1_e, OUTPUT);
      pinMode(pinouts::dig1_f, OUTPUT);
      pinMode(pinouts::dig1_g, OUTPUT);

      pinMode(pinouts::dig1_dot, OUTPUT);
    }

    void warm_up() {
      // warm up the anodes
      digitalWrite(pinouts::dig1_anode, HIGH);
      digitalWrite(pinouts::dig2_anode, HIGH);
      digitalWrite(pinouts::dig3_anode, HIGH);
      digitalWrite(pinouts::dig4_anode, HIGH);

      // warm up the katodes
      digitalWrite(pinouts::dig1_a, HIGH);
      digitalWrite(pinouts::dig1_b, HIGH);
      digitalWrite(pinouts::dig1_c, HIGH);
      digitalWrite(pinouts::dig1_d, HIGH);
      digitalWrite(pinouts::dig1_e, HIGH);
      digitalWrite(pinouts::dig1_f, HIGH);
      digitalWrite(pinouts::dig1_g, HIGH);

      digitalWrite(pinouts::dig1_dot, HIGH);
    }

    void print_value(uint16_t value) {
      value %= 10000;
      uint8_t A = value / 1000;
      value %= 1000;
      uint8_t B = value / 100;
      value %= 100;
      uint8_t C = value / 10;
      value %= 10;
      uint8_t D = value;

      print_symbols(A, B, C, D);
    }

    void print_symbols(uint8_t A, uint8_t B, uint8_t C, uint8_t D) {
      A_ = A;
      B_ = B;
      C_ = C;
      D_ = D;
    }

    void print_dots(bool A_dot, bool B_dot, bool C_dot, bool D_dot) {
      A_dot_ = A_dot;
      B_dot_ = B_dot;
      C_dot_ = C_dot;
      D_dot_ = D_dot;
    }

    uint8_t strobe_symbol(uint8_t s) {
      uint8_t segments = 0;
      if (s == 0) {
        digitalWrite(pinouts::dig1_a, LOW);
        digitalWrite(pinouts::dig1_b, LOW);
        digitalWrite(pinouts::dig1_c, LOW);
        digitalWrite(pinouts::dig1_d, LOW);
        digitalWrite(pinouts::dig1_e, LOW);
        digitalWrite(pinouts::dig1_f, LOW);
        segments = 6;
      } else if (s == 1) {
        digitalWrite(pinouts::dig1_b, LOW);
        digitalWrite(pinouts::dig1_c, LOW);
        segments = 2;
      } else if (s == 2) {
        digitalWrite(pinouts::dig1_a, LOW);
        digitalWrite(pinouts::dig1_b, LOW);
        digitalWrite(pinouts::dig1_g, LOW);
        digitalWrite(pinouts::dig1_e, LOW);
        digitalWrite(pinouts::dig1_d, LOW);
        segments = 5;
      } else if (s == 3) {
        digitalWrite(pinouts::dig1_a, LOW);
        digitalWrite(pinouts::dig1_b, LOW);
        digitalWrite(pinouts::dig1_c, LOW);
        digitalWrite(pinouts::dig1_d, LOW);
        digitalWrite(pinouts::dig1_g, LOW);
        segments = 5;
      } else if (s == 4) {
        digitalWrite(pinouts::dig1_f, LOW);
        digitalWrite(pinouts::dig1_g, LOW);
        digitalWrite(pinouts::dig1_b, LOW);
        digitalWrite(pinouts::dig1_c, LOW);
        segments = 4;
      } else if (s == 5) {
        digitalWrite(pinouts::dig1_a, LOW);
        digitalWrite(pinouts::dig1_f, LOW);
        digitalWrite(pinouts::dig1_g, LOW);
        digitalWrite(pinouts::dig1_c, LOW);
        digitalWrite(pinouts::dig1_d, LOW);
        segments = 5;
      } else if (s == 6) {
        digitalWrite(pinouts::dig1_a, LOW);
        digitalWrite(pinouts::dig1_c, LOW);
        digitalWrite(pinouts::dig1_d, LOW);
        digitalWrite(pinouts::dig1_e, LOW);
        digitalWrite(pinouts::dig1_f, LOW);
        digitalWrite(pinouts::dig1_g, LOW);
        segments = 6;
      } else if (s == 7) {
        digitalWrite(pinouts::dig1_a, LOW);
        digitalWrite(pinouts::dig1_b, LOW);
        digitalWrite(pinouts::dig1_c, LOW);
        segments = 3;
      } else if (s == 8) {
        digitalWrite(pinouts::dig1_a, LOW);
        digitalWrite(pinouts::dig1_b, LOW);
        digitalWrite(pinouts::dig1_c, LOW);
        digitalWrite(pinouts::dig1_d, LOW);
        digitalWrite(pinouts::dig1_e, LOW);
        digitalWrite(pinouts::dig1_f, LOW);
        digitalWrite(pinouts::dig1_g, LOW);
        segments = 7;
      } else if (s == 9) {
        digitalWrite(pinouts::dig1_a, LOW);
        digitalWrite(pinouts::dig1_b, LOW);
        digitalWrite(pinouts::dig1_c, LOW);
        digitalWrite(pinouts::dig1_d, LOW);
        digitalWrite(pinouts::dig1_f, LOW);
        digitalWrite(pinouts::dig1_g, LOW);
        segments = 6;
      }
      return segments;
    }

    uint8_t strobe_dot(bool visible) {
      if (visible)
        digitalWrite(pinouts::dig1_dot, LOW);

      return (visible ? 1 : 0);
    }

    void strobe() {
      digitalWrite(pinouts::dig1_a, HIGH);
      digitalWrite(pinouts::dig1_b, HIGH);
      digitalWrite(pinouts::dig1_c, HIGH);
      digitalWrite(pinouts::dig1_d, HIGH);
      digitalWrite(pinouts::dig1_e, HIGH);
      digitalWrite(pinouts::dig1_f, HIGH);
      digitalWrite(pinouts::dig1_g, HIGH);
      digitalWrite(pinouts::dig1_dot, HIGH);
      // delay(100);

      uint8_t n_segments = 0;

      if (symbol_pos_ == 0) {
        digitalWrite(pinouts::dig4_anode, LOW);
        digitalWrite(pinouts::dig1_anode, HIGH);
        n_segments += strobe_symbol(A_);
        n_segments += strobe_dot(A_dot_);
      } else if (symbol_pos_ == 1) {
        digitalWrite(pinouts::dig1_anode, LOW);
        digitalWrite(pinouts::dig2_anode, HIGH);
        n_segments += strobe_symbol(B_);
        n_segments += strobe_dot(B_dot_);
      } else if (symbol_pos_ == 2) {
        digitalWrite(pinouts::dig2_anode, LOW);
        digitalWrite(pinouts::dig3_anode, HIGH);
        n_segments += strobe_symbol(C_);
        n_segments += strobe_dot(C_dot_);
      } else if (symbol_pos_ == 3) {
        digitalWrite(pinouts::dig3_anode, LOW);
        digitalWrite(pinouts::dig4_anode, HIGH);
        n_segments += strobe_symbol(D_);
        n_segments += strobe_dot(D_dot_);
      }

      // if (n_segments < 3)
      //   delay(1);
      // else if (n_segments < 5)
      //   delay(2);
      // else if (n_segments < 7)
      //   delay(3);
      // else
      //   delay(4);

      if (n_segments)
        delayMicroseconds(n_segments * 750);
      else
        delayMicroseconds(8 * 750);

      symbol_pos_ = ++symbol_pos_ % 4;
    }

  private:
    uint8_t A_ {0};
    uint8_t B_ {0};
    uint8_t C_ {0};
    uint8_t D_ {0};
    bool A_dot_ {false};
    bool B_dot_ {false};
    bool C_dot_ {false};
    bool D_dot_ {false};
    uint8_t symbol_pos_ {0};
};

class ClockDisplay {
  public:
    void setup() {
      display_.setup();
      display_.warm_up();
    }

    void view(const Clock &clock, const ClockOscillator &oscillator) {
      ClockFSM::STATE state = clock.fsm().state();

      // Base mode's
      if (state == ClockFSM::MODE_TIME) {
        display_.print_value(clock.ts().hour() * 100 + clock.ts().minute());
        display_.print_dots(0, (clock.ts().pendel_1_hz() ? 1 : 0), 0, 0);
      } else if (state == ClockFSM::MODE_DATE) {
        display_.print_value(clock.ts().day() * 100 + clock.ts().month());
        display_.print_dots(0, 0, 0, 0);
      } else if (state == ClockFSM::MODE_SECONDS) {
        display_.print_symbols('_', '_', clock.ts().second() / 10, clock.ts().second() % 10);
        display_.print_dots(0, 0, 0, 0);
      } else
      // Edit mode's
      if (state == ClockFSM::MODE_EDIT_TIME) {
        if (clock.running()) {
          display_.print_value(clock.ts().hour() * 100 + clock.ts().minute());
        } else {
          if (dimmed_()) {
            display_.print_value(clock.ts().hour() * 100 + clock.ts().minute());
          } else {
            display_.print_symbols('_', '_', '_', '_');
          }
        }
        display_.print_dots(0, 1, 0, 0);
      } else if (state == ClockFSM::MODE_EDIT_SECONDS) {
        if (clock.running()) {
          display_.print_symbols('_', '_', clock.ts().second() / 10, clock.ts().second() % 10);
        } else {
          if (dimmed_()) {
            display_.print_symbols('_', '_', clock.ts().second() / 10, clock.ts().second() % 10);
          } else {
            display_.print_symbols('_', '_', '_', '_');
          }
        }
        display_.print_dots(0, 0, 0, 0);
      } else if (state == ClockFSM::MODE_EDIT_DATE) {
        if (clock.running()) {
          display_.print_value(clock.ts().day() * 100 + clock.ts().month());
        } else {
          if (dimmed_()) {
            display_.print_value(clock.ts().day() * 100 + clock.ts().month());
          } else {
            display_.print_symbols('_', '_', '_', '_');
          }
        }
        display_.print_dots(0, 0, 0, 0);
      } else if (state == ClockFSM::MODE_EDIT_DATE_YEAR) {
        if (clock.running()) {
          display_.print_value(clock.ts().year());
        } else {
          if (dimmed_()) {
            display_.print_value(clock.ts().year());
          } else {
            display_.print_symbols('_', '_', '_', '_');
          }
        }
        display_.print_dots(0, 0, 0, 0);
      } else if (state == ClockFSM::MODE_ACCURACY_TUNE) {
        if (clock.running()) {
          display_.print_value(abs(oscillator.timeshift()));
          display_.print_dots(1, 0, 0, (oscillator.timeshift() < 0 ? 1 : 0));
        } else {
          if (dimmed_()) {
            display_.print_value(abs(oscillator.timeshift()));
            display_.print_dots(1, 0, 0, (oscillator.timeshift() < 0 ? 1 : 0));
          } else {
            display_.print_symbols('_', '_', '_', '_');
          }
        }
      }

      display_.strobe();
    }

  private:
    Display display_;

    bool dimmed_() const {
      // return (millis() % 1000 / 500) % 2;
      return millis() % 1000 > 500;
    }
};

#endif // _CLOCK_DISPLAY_H_

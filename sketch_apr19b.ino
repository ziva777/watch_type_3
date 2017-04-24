
// #include "timestamp.h"
#include "clock_oscillator.h"
#include "clock.h"
#include "clock_display.h"
#include "clock_controller.h"

Clock clock;
ClockDisplay display;
ClockController controller;
ClockOscillator oscillator;

// void rx_led_blink() {
//   static bool rx_led_on = false;
//   (rx_led_on ? RXLED0 : RXLED1);
//   rx_led_on = !rx_led_on;
// }

const uint32_t MSECONDS_PER_HOUR = 60UL * 60UL * 1000UL;
const uint32_t MSECONDS_PER_DAY = 24UL * MSECONDS_PER_HOUR;

uint32_t mseconds_day_counter = 0;
uint32_t mseconds_hour_counter = 0;
int32_t pass_counter = 0;

void make_time_wrap(int32_t shift) {
  if (shift > 0) {
    for (shift; shift != 0; --shift)
      oscillator.swing(clock.ts());
  } else if (shift < 0) {
      pass_counter = shift;
  }
}

ISR(TIMER4_COMPA_vect) {
  // 1 mS call

  if (pass_counter < 0) {
    ++pass_counter;
    return;
  }

  if (++mseconds_hour_counter == MSECONDS_PER_HOUR) {
    mseconds_hour_counter = 0;
    int32_t shift = oscillator.shift_per_hour();
    make_time_wrap(shift);
    Serial.print("occure shift_per_hour ");
    Serial.println(shift);
  }

  if (++mseconds_day_counter == MSECONDS_PER_DAY) {
    mseconds_day_counter = 0;
    int32_t shift = oscillator.shift_per_day_tail();
    make_time_wrap(shift);
    Serial.print("occure shift_per_day ");
    Serial.println(shift);
  }

  oscillator.swing(clock.ts());
}

void setup_timer4() {
  // uint8_t scaler =_BV(CS42) | _BV(CS40); // CK/16
  uint8_t scaler =_BV(CS42) | _BV(CS41); // CK/32 - 2uS
  // uint8_t scaler = _BV(CS43) | _BV(CS42) | _BV(CS41) | _BV(CS40); // CK/16384

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

  TCCR4B |= scaler;

  // // 1000 steps
  // TC4H = 3;
  // OCR4C = 232 - 1;

  // 500 steps
  TC4H = 1;
  OCR4C = 244 - 1;

  // // 10 steps
  // TC4H = 0;
  // OCR4C = 10 - 1;

  TIMSK4 = _BV(OCIE4A);
}

void setup() {
  Serial.begin(9600);
  display.setup();

  oscillator.set_swing_step(1); // mS
  oscillator.set_timestamp_swing_interval(100); // mS
  oscillator.set_timeshift(0); // mS

  clock.ts().set_tick_size(oscillator.timestamp_swing_interval()); // mS
  setup_timer4(); // for 1 mS call of oscillator.swing
}

void loop() {
  controller.update(clock, oscillator);
  display.view(clock, oscillator);
}

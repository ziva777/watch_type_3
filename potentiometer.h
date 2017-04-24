#ifndef _POTENTIOMETER_H_
#define _POTENTIOMETER_H_

template <uint8_t SIZE>
class CMA {
  public:
    CMA() {
      memset(value_chain_, 0, sizeof(value_chain_));
    }

    CMA(uint8_t scaler) : scaler_(scaler) {
      memset(value_chain_, 0, sizeof(value_chain_));
    }

    void set_scaler(uint8_t scaler) {
      scaler_ = scaler;
    }

    void push(uint16_t value) {
      value_chain_[value_chain_index_++] = value;
      value_chain_index_ %= CHAIN_SIZE;
    }

    uint16_t value() {
      uint32_t v = 0;

      for (int i = 0; i != CHAIN_SIZE; ++i)
        v += value_chain_[i];

      v /= CHAIN_SIZE;
      return v / scaler_;
    }

    void setup(uint16_t value) {
      for (int i = 0; i != CHAIN_SIZE; ++i)
        value_chain_[i] = value;
    }

  private:
    static const uint8_t CHAIN_SIZE {SIZE};
    uint16_t value_chain_[CHAIN_SIZE];
    uint8_t value_chain_index_ {0};
    uint8_t scaler_ {1};
};

template <uint8_t SCALER, uint16_t MAX_VALUE>
class Potentiometer {
  public:
    Potentiometer(uint8_t pin) : pin_(pin) {

    }

    void setup(uint16_t value) {
      cma_.setup(value);
    }

    uint16_t read() {
      last_value_ = raw_read();
      cma_.push(last_value_);
      return cma_.value();
    }

    uint16_t raw_read() {
      return analogRead(pin_);
    }

    uint16_t max_value() const { return max_value_ / cma_scaler_; }

  private:
    uint8_t pin_ {0};
    const uint8_t cma_scaler_ {SCALER};
    const uint16_t max_value_ = MAX_VALUE;
    CMA<50> cma_ {cma_scaler_};
    uint16_t last_value_ = {0};
};

#endif // _POTENTIOMETER_H_

#ifndef _CLOCK_FSM_H_
#define _CLOCK_FSM_H_

class ClockFSM {
  public:
    enum STATE {
      MODE_TIME, // time
      MODE_DATE, // date
      MODE_SECONDS, // seconds

      MODE_EDIT_TIME,
      MODE_EDIT_SECONDS,
      MODE_EDIT_DATE,
      MODE_EDIT_DATE_YEAR,

      MODE_ACCURACY_TUNE
    };

    STATE state() const { return state_; }

    void next_state() {
      if (state_ == MODE_TIME) {
        state_ = MODE_DATE;
      } else if (state_ == MODE_DATE) {
        state_ = MODE_SECONDS;
      } else if (state_ == MODE_SECONDS) {
        state_ = MODE_TIME;
      }
    }

    void begin_edit() {
      state_ = MODE_EDIT_TIME;
    }

    void end_edit() {
      state_ = MODE_TIME;
    }

    bool is_edit() const {
      return state_ == MODE_EDIT_TIME or 
              state_ == MODE_EDIT_SECONDS or
                state_ == MODE_EDIT_DATE or
                  state_ == MODE_EDIT_DATE_YEAR or
                    state_ == MODE_ACCURACY_TUNE;
    }

    void next_edit_state() {
      if (state_ == MODE_EDIT_TIME) {
        state_ = MODE_EDIT_SECONDS;
      } else if (state_ == MODE_EDIT_SECONDS) {
        state_ = MODE_EDIT_DATE;
      } else if (state_ == MODE_EDIT_DATE) {
        state_ = MODE_EDIT_DATE_YEAR;
      } else if (state_ == MODE_EDIT_DATE_YEAR) {
        state_ = MODE_ACCURACY_TUNE;
      } else if (state_ == MODE_ACCURACY_TUNE) {
        state_ = MODE_EDIT_TIME;
      }
    }

  private:
    STATE state_ {MODE_TIME};
};

#endif // _CLOCK_FSM_H_

#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "timestamp.h"
#include "clock_FSM.h"

class Clock {
  public:
    ClockFSM & fsm() { return fsm_; }
    Timestamp & ts() { return ts_; }

    void on_the_run() { on_the_run_ = true; }
    void off_the_run() { on_the_run_ = false; }
    bool running() const { return on_the_run_; }

  private:
    ClockFSM fsm_;
    Timestamp ts_;
    bool on_the_run_ {false}; // adjust by user
};

#endif // _CLOCK_H_

/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

#include "precision.h"

/////////////
//         //
//  Timer  //
//         //
/////////////
class Timer {
  public:
    Timer();
    void start(); /* for global */
    void stop();  /* fot global */
    void start(const std::string fname); /* for local */
    void stop(const std::string fname);  /* for local */
    real elapsed_s();
    void report();
    void report_separate();

  private:
    bool               is_running;
    int                i_stopped;
    std::clock_t       start_time;
    std::clock_t       total_time;
    std::string        name;
    std::vector<Timer> sub; /* local (subroutine) timers */
};

/*---------------+
|  global timer  |
+---------------*/
namespace easy {
  extern Timer timer;
}

#endif


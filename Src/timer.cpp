/*---------------------------------------------------------------------------+
|   EasyMesh - A Two-Dimensional Quality Mesh Generator                      |
|                                                                            |
|   Copyright (C) 2008 Bojan Niceno - bojan.niceno@psi.ch                    |
+---------------------------------------------------------------------------*/
#include "timer.h" 

using namespace std;

/*---------------+
|  global timer  |
+---------------*/
namespace easy {
  Timer timer;
}

/****************************************************************************/
Timer :: Timer() {
/*--------------------+
|  basic constructor  |
+--------------------*/
  is_running = false;
  i_stopped  = -1;
  total_time = 0;
  name       = "";
}

/****************************************************************************/
void Timer :: start() {
/*--------------------------+
|  this starts the counter  |
+--------------------------*/
  if(is_running)
    std::cout << "timer " << name << " is allready running !" << std::endl;
  else {
    is_running = true; 
    start_time = clock();
  }
}

/****************************************************************************/
void Timer :: stop() {
/*--------------------------------+
|  this stops the global counter  |
+--------------------------------*/
  if(!is_running)
    std::cout << "timer " << name << " is not running !" << std::endl;
  else {
    total_time += (clock() - start_time);
    is_running = false;
  }
}

/****************************************************************************/
void Timer :: start(const std::string fname) {
/*-------------------------------------------------------+
|  creates and starts local timer if it does not exist,  |
|  only starts it if it does exist and                   |
|  stops other local timer, if it runs.                  |
+-------------------------------------------------------*/

  /* find it */
  int it=-1;
  for(int i=0; i<(int)sub.size(); i++) {
    if( sub[i].name == fname ) {
      it=i;
      break;
    }
  }

  /* if it doesn't exist, create it */
  if(it == -1) {
    Timer newt;          /* new timer */
    newt.name = fname;   /* set its name */
    sub.push_back(newt);
    it = sub.size()-1;
  }

  /* stop the others, storing the stopped one */
  sub[it].i_stopped = -1;
  for(int i=0; i<(int)sub.size(); i++) {
    if( sub[i].is_running ) {
      sub[i].stop();
      sub[it].i_stopped = i;
      break;
    }
  }

  /* start it */
  sub[it].start();
}

/****************************************************************************/
void Timer :: stop(const std::string fname) {
/*--------------------------------------+
|  stops the local (subroutine) timer,  |
|   and restarts the one you stopped.   |
+--------------------------------------*/

  /* if present stop it ... */
  for(int it=0; it<(int)sub.size(); it++) {
    if( sub[it].name == fname ) { /* found it */

      sub[it].stop(); /* stop it */

      /* ... and start the one it stopped */
      if(sub[it].i_stopped != -1) {
        sub[sub[it].i_stopped].start();
        sub[it].i_stopped = -1;
      }
      return;
    }
  }

  /* if not present, give a warning message */
  std::cout << "timer " << fname << " isn't running !" << std::endl;
}

/****************************************************************************/
real Timer :: elapsed_s() {
  real e = (real)total_time / (real)CLOCKS_PER_SEC;
  return e;
}

/****************************************************************************/
void Timer :: report_separate() {
/*----------------------------------------+
|  reports the time spent in the program  |
+----------------------------------------*/

  /* total time */
  real total = elapsed_s();
  std::cout << "+==========================================" << std::endl;
  std::cout << "| Total execution time: " << total << " [s]" << std::endl;
  std::cout << "+------------------------------------------" << std::endl;

  if(total < 0.01) return;

  int longest(0);
  for(int i=0; i<(int)sub.size(); i++) 
    longest=std::max(longest, (int)sub[i].name.length());
  for(int i=0; i<(int)sub.size(); i++) sub[i].name.resize(longest, ' ');

  real acum = 0.0; 
  for(int i=0; i<(int)sub.size(); i++) {
    real here = sub[i].elapsed_s();
    std::cout << "| Time spent in " << sub[i].name << ": " 
               << here << " [s]    (" 
               << here * 100.0 / total << "%)" << std::endl;
    acum += here;
  }
  if(sub.size()) {
    std::cout << "| Time spent elsewhere: " 
               << total - acum << " [s]    ("
               << (total - acum) * 100.0 / total << "%)" << std::endl;
    std::cout << "+------------------------------------------" << std::endl;
  }
}

/****************************************************************************/
void Timer :: report() {
/*----------------------------------------+
|  reports the time spent in the program  | -> some averaging over processors!
+----------------------------------------*/

  /* total time */
  real total = elapsed_s();

  std::cout << "+==========================================" << std::endl;
  std::cout << "| Total execution time: " << total << " [s]" << std::endl;
  std::cout << "+------------------------------------------" << std::endl;

  if(total < 0.01) return;

  int longest(0);
  for(int i=0; i<(int)sub.size(); i++) 
    longest=std::max(longest, (int)sub[i].name.length());
  for(int i=0; i<(int)sub.size(); i++) sub[i].name.resize(longest, ' ');

  real acum = 0.0; 
  for(int i=0; i<(int)sub.size(); i++) {
    real here = sub[i].elapsed_s();

    std::cout << "| Time spent in " << sub[i].name << ": " 
               << here << " [s]    (" 
               << here * 100.0 / total << "%)" << std::endl;
    acum += here;
  }
  if(sub.size()) {
    std::cout << "| Time spent elsewhere: " 
               << total - acum << " [s]    ("
               << (total - acum) * 100.0 / total << "%)" << std::endl;
    std::cout << "+------------------------------------------" << std::endl;
  }
}


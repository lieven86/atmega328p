#ifndef LST_DRIVERS_TIMER_H_
#define LST_DRIVERS_TIMER_H_

#include <lib.h>

namespace lst {

class Timer {
 public:
  Timer() { }
  ~Timer() { }
  
  void Init();
  void Clear();
  void Run();

 private:

  DISALLOW_COPY_AND_ASSIGN(Timer);
};

}  // namespace lst

#endif  // LST_DRIVERS_TIMER_H_

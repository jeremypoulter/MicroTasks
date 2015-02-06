// Task.h

#ifndef _TASK_h
#define _TASK_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Task;
#include "MicroTasks.h"

enum WakeReason
{
  WakeReason_Scheduled,
  WakeReason_Event,
  WakeReason_Message
};

class MicroTasks;

class Task
{
  friend class MicroTasksClass;

  private:
    Task *oPrev;
    Task *oNext;
    unsigned long ulNextLoop;

  protected:

  public:
    Task();
    virtual ~Task();

    virtual void setup() = 0;
    virtual unsigned long loop(WakeReason reason) = 0;
};

#endif


// MicroTasks.h

#ifndef _MICROTASKS_h
#define _MICROTASKS_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Task.h"

class MicroTasksClass
{
  private:
    Task *oFirstTask;
    Task *oLastTask;

  protected:

  public:
    MicroTasksClass();

    void init();
    void update();

    void startTask(Task *oTask);
    void stopTask(Task *oTask);
};

extern MicroTasksClass MicroTasks;

#endif


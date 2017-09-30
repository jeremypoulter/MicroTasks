// EventListner.h

#ifndef _EVENTLISTNER_h
#define _EVENTLISTNER_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MicroTasksNode.h"
#include "MicroTasksTask.h"

namespace MicroTasks
{
  class EventListener : public Node
  {
    friend class MicroTasksClass;

  private:
    Task *oTask;
    int triggered;
  public:
    EventListener(Task *oTask) :
      Node(), oTask(oTask) {
    }

    Task *GetTask() {
      return oTask;
    }

    bool IsTriggered() {
      return triggered ? true : false;
    }
  };
}

#endif

// EventListner.h

#ifndef _EVENTLISTNER_h
#define _EVENTLISTNER_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Node.h"
#include "Task.h"

class EventListener : public Node
{
  private:
    Task *oTask;
  public:
    EventListener(Task *oTask) : 
      oTask(oTask), Node() {
    }

    Task *GetTask() {
      return oTask;
    }
};

#endif


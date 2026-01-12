// Event.h

#ifndef _EVENT_h
#define _EVENT_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MicroTasksNode.h"
#include "MicroTasksList.h"
#include "MicroTasksEventListener.h"

namespace MicroTasks
{
  class Event : public Node
  {
    friend class MicroTasksClass;

  private:
    List oClients;
    static List& GetEvents() {
      static List oEvents;
      return oEvents;
    }

    volatile int triggered;

  protected:
    void Trigger(bool fromInterrupt);
    virtual void Trigger() {
      Trigger(false);
    }

  public:
    Event() : oClients(), triggered(0) {
      GetEvents().Add(this);
    }
    ~Event() {
      GetEvents().Remove(this);
    }

    void Register(EventListener *oListener);
    void Deregister(EventListener *oListener);
    bool IsTriggered() {
      return triggered ? true : false;
    }
  };
}

#endif


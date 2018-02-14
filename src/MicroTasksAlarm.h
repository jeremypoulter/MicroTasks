// Alarm.h

#ifndef _ALARM_h
#define _ALARM_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MicroTasksNode.h"
#include "MicroTasksList.h"

namespace MicroTasks
{
  class Alarm : public Node
  {
    friend class MicroTasksClass;

  private:
    List oClients;
    static List oAlarms;

    uint32_t uiDelay;
    bool bRepeat;

    uint32_t uiTime;

  protected:
    virtual void Trigger() = 0;

  public:
    Alarm() : oClients(), uiDelay(0), bRepeat(false), uiTime(0) {
      oAlarms.Add(this);
    }
    ~Alarm() {
      oAlarms.Remove(this);
    }

    void Set(uint32_t uiDelay, bool bRepeat);
    void Reset();
    void Clear();    
  };
}

#endif


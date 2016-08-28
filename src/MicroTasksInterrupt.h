// Interupt.h

#ifndef _INTERUPT_h
#define _INTERUPT_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MicroTasksEvent.h"

namespace MicroTasks
{
  typedef void(*InterruptCallback)(void);

  class Interrupt : public Event
  {
  private:
    uint8_t interrupt;
    int mode;

    static void TriggerInt0();
    static void TriggerInt1();

    static InterruptCallback Triggers[];
  public:
    Interrupt(uint8_t interrupt, int mode) :
      interrupt(interrupt),
      mode(mode)
    {
    }

    bool Attach();
    void Dettach();
  };
}

#endif


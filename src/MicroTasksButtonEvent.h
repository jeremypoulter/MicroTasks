// ButtonEvent.h

#ifndef _BUTTONEVENT_h
#define _BUTTONEVENT_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "Interrupt.h"

namespace MicroTasks
{
  class ButtonEvent : public Interrupt
  {
  private:
    int debounce;
    unsigned long lastTime;

  protected:
    virtual void Trigger();

  public:
    ButtonEvent(uint8_t interrupt, int mode, int debounce = 20) :
      debounce(debounce), lastTime(0), Interrupt(interrupt, mode)
    {
    }
  };
}

#endif


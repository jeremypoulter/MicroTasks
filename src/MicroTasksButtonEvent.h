// ButtonEvent.h

#ifndef _BUTTONEVENT_h
#define _BUTTONEVENT_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MicroTasksInterrupt.h"

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
    ButtonEvent(uint8_t pin, int mode, int inputMode = INPUT, int debounce = 20) :
      Interrupt(pin, mode, inputMode), debounce(debounce), lastTime(0)
    {
    }
  };
}

#endif


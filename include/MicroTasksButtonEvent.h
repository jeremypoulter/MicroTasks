// ButtonEvent.h

#ifndef _BUTTONEVENT_h
#define _BUTTONEVENT_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MicroTasksInterrupt.h"
#include "MicroTasksAlarm.h"

namespace MicroTasks
{
  class ButtonEvent : public Interrupt
  {
  private:
    int debounce;
    unsigned long lastTime;
    bool state;
    int mode;
    int pressed;
    class ButtonTriggerDebounce : public Alarm
    {
    private:
      ButtonEvent &event;
    public:
      ButtonTriggerDebounce(ButtonEvent &event) : event(event) {
      }
      void Trigger();
    } debounceAlarm;
    void triggerInterrupt();

  protected:
    virtual void Trigger();

  public:
    ButtonEvent(uint8_t pin, int mode, int inputMode = INPUT, int debounce = 20, int pressed = LOW);

    bool IsPressed() {
      return state;
    }
  };
}

#endif


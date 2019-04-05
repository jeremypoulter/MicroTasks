// Interupt.h

#ifndef _INTERUPT_h
#define _INTERUPT_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MicroTasksEvent.h"

#define MICROTASKS_MAX_INTERUPTS 5

namespace MicroTasks
{
  typedef void(*InterruptCallback)(void);

  class Interrupt : public Event
  {
    protected:
      uint8_t pin;
    private:
      int mode;
      int inputMode;
      int index;

      static void TriggerInt0();
      static void TriggerInt1();
      static void TriggerInt2();
      static void TriggerInt3();
      static void TriggerInt4();

      static InterruptCallback Triggers[];

    protected:
      virtual void Trigger() {
        Event::Trigger(true);
      }

    public:
      Interrupt(uint8_t pin, int mode, int inputMode = INPUT) :
        Event(), pin(pin), mode(mode), inputMode(inputMode), index(-1)
      {
      }

      bool Attach();
      void Dettach();
  };
}

#endif


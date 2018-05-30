//
//
//

#include "MicroTasksButtonEvent.h"

using namespace MicroTasks;

ButtonEvent::ButtonEvent(uint8_t pin, int mode, int inputMode, int debounce) :
  Interrupt(pin, CHANGE, inputMode), debounce(debounce), lastTime(0), state(false), mode(mode),
  debounceAlarm(*this)
{
  pinMode(pin, inputMode);
  state = LOW == digitalRead(pin);
}

void ButtonEvent::Trigger()
{
  unsigned long timeNow = millis();
  if (timeNow >= lastTime + debounce)
  {
    state = LOW == digitalRead(pin);
    triggerInterrupt();
  }
  else 
  {
    debounceAlarm.Set(debounce, false);
  }

  lastTime = timeNow;
}

void ButtonEvent::ButtonTriggerDebounce::Trigger()
{
  bool newState = LOW == digitalRead(event.pin);
  if(newState != event.state) 
  {
    event.state = newState;
    event.lastTime = millis();
    event.triggerInterrupt();
  }
}

void ButtonEvent::triggerInterrupt()
{
  if((true == state && (RISING == mode || CHANGE == mode)) ||
      (false == state && (FALLING == mode || CHANGE == mode)))
  {
    Interrupt::Trigger();
  }
}

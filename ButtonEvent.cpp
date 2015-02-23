// 
// 
// 

#include "ButtonEvent.h"

void ButtonEvent::Trigger()
{
  unsigned long timeNow = millis();
  if (timeNow >= lastTime + debounce)
  {
    Interrupt::Trigger();
    lastTime = timeNow;
  }
}

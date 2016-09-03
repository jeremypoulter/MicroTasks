//
//
//

#include "MicroTasksButtonEvent.h"

using namespace MicroTasks;

void ButtonEvent::Trigger()
{
  unsigned long timeNow = millis();
  if (timeNow >= lastTime + debounce)
  {
    Interrupt::Trigger();
  }
  lastTime = timeNow;
}

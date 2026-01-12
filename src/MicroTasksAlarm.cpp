//
//
//

#include "MicroTasksAlarm.h"

using namespace MicroTasks;

void Alarm::Set(uint32_t uiDelay, bool bRepeat)
{
  this->uiDelay = uiDelay;
  this->bRepeat = bRepeat;

  Reset();
}

void Alarm::Reset()
{
  noInterrupts();
  if(!GetAlarms().Contains(this)) {
    GetAlarms().Add(this);
  }
  interrupts();

  uiTime = millis() + uiDelay;
}

void Alarm::Clear()
{
  noInterrupts();
  GetAlarms().Remove(this);
  interrupts();
}

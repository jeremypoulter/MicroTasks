//
//
//

#include "MicroTasksAlarm.h"

using namespace MicroTasks;

List Alarm::oAlarms = List();

void Alarm::Set(uint32_t uiDelay, bool bRepeat)
{
  this->uiDelay = uiDelay;
  this->bRepeat = bRepeat;

  Reset();
}

void Alarm::Reset()
{
  if(!oAlarms.Contains(this)) {
    oAlarms.Add(this);
  }

  uiTime = millis() + uiDelay;
}

void Alarm::Clear()
{
  oAlarms.Remove(this);
}

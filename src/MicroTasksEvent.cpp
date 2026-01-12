//
//
//

#include "MicroTasks.h"
#include "MicroTasksEvent.h"

using namespace MicroTasks;

void Event::Register(EventListener *oListener)
{
  if(!GetEvents().Contains(this)) {
    GetEvents().Add(this);
  }
  oClients.Add(oListener);
}

void Event::Deregister(EventListener *oListener)
{
  oClients.Remove(oListener);
}

void Event::Trigger(bool fromInterrupt) {
  triggered = 1;
  MicroTask.wakeLoop(fromInterrupt);
}

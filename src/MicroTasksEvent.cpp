//
//
//

#include "MicroTasks.h"
#include "MicroTasksEvent.h"

using namespace MicroTasks;

List Event::oEvents = List();

void Event::Register(EventListener *oListener)
{
  if(!oEvents.Contains(this)) {
    oEvents.Add(this);
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

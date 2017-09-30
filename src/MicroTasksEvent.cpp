//
//
//

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

//
//
//

#include "MicroTasksEvent.h"

using namespace MicroTasks;

List Event::oEvents = List();

void Event::Register(EventListener *oListener)
{
  oClients.Add(oListener);
}

void Event::Deregister(EventListener *oListener)
{
  oClients.Remove(oListener);
}

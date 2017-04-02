//
//
//

#include "MicroTasksTask.h"
#include "MicroTasksEvent.h"
#include "MicroTasks.h"

using namespace MicroTasks;

uint32_t MicroTasksClass::WaitForEvent = (1 << 31);
uint32_t MicroTasksClass::WaitForMessage = (1 << 30);

uint32_t MicroTasksClass::WaitForMask = MicroTasksClass::WaitForEvent | WaitForMessage;

uint32_t MicroTasksClass::Infinate = ~MicroTasksClass::WaitForMask;

MicroTasksClass::MicroTasksClass()
{
}

void MicroTasksClass::init()
{
}

void MicroTasksClass::update()
{
  Event *oNextEvent;
  EventListener *oNextEventListener;
  Task *oNextTask;

  // Any events triggered?
  for (Event *oEvent = (Event *)Event::oEvents.GetFirst(); oEvent; oEvent = oNextEvent)
  {
    oNextEvent = (Event *)oEvent->GetNext();

    if (oEvent->triggered)
    {
      for (EventListener *oEventListener = (EventListener *)(oEvent->oClients.GetFirst()); oEventListener; oEventListener = oNextEventListener)
      {
        // Keep a pointer to the next task in case this on is stopped
        oNextEventListener = (EventListener *)(oEventListener->GetNext());
        wakeTask(oEventListener->GetTask(), WakeReason_Event);
      }

      oEvent->triggered = 0;
    }
  }

  // Any tasks waiting to be woken
  for (Task *oTask = (Task *)oTasks.GetFirst(); oTask; oTask = oNextTask)
  {
    // Keep a pointer to the next task in case this on is stopped
    oNextTask = (Task *)oTask->GetNext();

    if (oTask->ulNextLoop <= millis()) {
      wakeTask(oTask, WakeReason_Scheduled);
    }
  }
}

void MicroTasksClass::wakeTask(Task *oTask, WakeReason eReason)
{
//   Serial.print(millis());
//   Serial.print(": W ");
//   Serial.print((unsigned int)oTask);
//   Serial.print(" [");
//   Serial.print((int)eReason);
//   Serial.print("] -> ");

  unsigned long ulDelay = oTask->loop(eReason);

  oTask->uiFlags = ulDelay & MicroTask.WaitForMask;
  if (MicroTask.Infinate == (ulDelay & ~MicroTask.WaitForMask)) {
    oTask->ulNextLoop = 0xFFFFFFFF;
//     Serial.println("Forever");
  } else {
    oTask->ulNextLoop = millis() + (ulDelay & ~MicroTask.WaitForMask);
//     Serial.print(ulDelay & ~MicroTask.WaitForMask);
//     Serial.print(":");
//     Serial.println(oTask->ulNextLoop);
  }
}

void MicroTasksClass::startTask(Task *oTask)
{
  oTasks.Add(oTask);
  oTask->setup();
}

void MicroTasksClass::stopTask(Task *oTask)
{
  oTasks.Remove(oTask);
}

MicroTasksClass MicroTask;

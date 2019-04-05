//
//
//

#include "MicroTasksTask.h"
#include "MicroTasksEvent.h"
#include "MicroTasksAlarm.h"
#include "MicroTasks.h"

#ifdef ENABLE_DEBUG_MICROTASKS
#define ENABLE_DEBUG
#else 
#undef ENABLE_DEBUG
#endif
#include "MicroDebug.h"

using namespace MicroTasks;

uint32_t MicroTasksClass::WaitForEvent = (1 << 31);
uint32_t MicroTasksClass::WaitForMessage = (1 << 30);

uint32_t MicroTasksClass::WaitForMask = MicroTasksClass::WaitForEvent | WaitForMessage;

uint32_t MicroTasksClass::Infinate = ~MicroTasksClass::WaitForMask;

MicroTasksClass::MicroTasksClass() :
  oTasks(),
  fnLoopWakeCallback(NULL)
{
}

void MicroTasksClass::init()
{
}

uint32_t MicroTasksClass::update()
{
  uint32_t uiNextEvent = 0xFFFFFFFF;

  // Any events triggered?
  Event *oNextEvent;
  for (Event *oEvent = (Event *)Event::oEvents.GetFirst(); oEvent; oEvent = oNextEvent)
  {
    oNextEvent = (Event *)oEvent->GetNext();
    
    if (oEvent->triggered)
    {
      EventListener *oNextEventListener;
      for (EventListener *oEventListener = (EventListener *)(oEvent->oClients.GetFirst()); oEventListener; oEventListener = oNextEventListener)
      {
        // Keep a pointer to the next task in case this on is stopped
        oNextEventListener = (EventListener *)(oEventListener->GetNext());
        oEventListener->triggered = 1;
        wakeTask(oEventListener->GetTask(), WakeReason_Event);
        oEventListener->triggered = 0;
      }
      
      oEvent->triggered = 0;
    }
  }

  // Any alarms triggered?
  Alarm *oNextAlarm;
  for (Alarm *oAlarm = (Alarm *)Alarm::oAlarms.GetFirst(); oAlarm; oAlarm = oNextAlarm)
  {
    oNextAlarm = (Alarm *)oAlarm->GetNext();
    if(millis() >= oAlarm->uiTime) 
    {
      if(oAlarm->bRepeat) {
        oAlarm->Reset();
      } else {
        oAlarm->Clear();
      }

      oAlarm->Trigger();
    }

    if(oAlarm->IsValid() && oAlarm->uiTime < uiNextEvent) {
      uiNextEvent = oAlarm->uiTime;
    }
  }
  
  // Any tasks waiting to be woken
  Task *oNextTask;
  for (Task *oTask = (Task *)oTasks.GetFirst(); oTask; oTask = oNextTask)
  {
    // Keep a pointer to the next task in case this one is stopped
    oNextTask = (Task *)oTask->GetNext();
    if (oTask->ulNextLoop <= millis()) {
      wakeTask(oTask, WakeReason_Scheduled);
    }
    if(oTask->IsValid() && oTask->ulNextLoop < uiNextEvent) {
      uiNextEvent = oTask->ulNextLoop;
    }
  }

#ifdef ENABLE_DEBUG_MICROTASKS
  DEBUG_PORT.flush();
#endif
  return uiNextEvent;
}

void MicroTasksClass::wakeTask(Task *oTask, WakeReason eReason)
{
  DBUG(millis());
  DBUG(": W ");
  DBUG((unsigned int)oTask);
  DBUG(" [");
  DBUG((int)eReason);
  DBUG("] -> ");

#ifdef ENABLE_DEBUG_MICROTASKS
  uint32_t ulStart = micros();
#endif
  uint32_t ulDelay = oTask->loop(eReason);
  DBUG(micros() - ulStart);
  DBUG(":");
  uint32_t ulNext = ulDelay & ~MicroTask.WaitForMask;

  oTask->uiFlags = ulDelay & MicroTask.WaitForMask;
  if (MicroTask.Infinate == ulNext) {
    oTask->ulNextLoop = 0xFFFFFFFF;
    DBUGLN("Forever");
  } else {
    oTask->ulNextLoop = millis() + ulNext;
    DBUG(ulNext);
    DBUG(":");
    DBUGLN(oTask->ulNextLoop);
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
  oTask->ulNextLoop = 0xFFFFFFFF;
}

MicroTasksClass MicroTask;

// 
// 
// 

#include "Task.h"
#include "MicroTasks.h"

unsigned long MicroTasksClass::WaitForEvent = (1 << 31);
unsigned long MicroTasksClass::WaitForMessage = (1 << 30);

unsigned long MicroTasksClass::WaitForMask = MicroTasksClass::WaitForEvent | WaitForMessage;

unsigned long MicroTasksClass::Infinate = ~MicroTasksClass::WaitForMask;

MicroTasksClass::MicroTasksClass()
{
}

void MicroTasksClass::init()
{
}

void MicroTasksClass::update()
{
  Task *oNext;

  for (Task *oTask = (Task *)oTasks.GetFirst(); oTask; oTask = oNext)
  {
    // Keep a pointer to the next task in case this on is stopped
    oNext = (Task *)oTask->GetNext();

    if (oTask->ulNextLoop <= millis())
    {
      unsigned long ulDelay = oTask->loop(WakeReason_Scheduled);

      oTask->uiFlags = ulDelay & MicroTasks.WaitForMask;
      if (MicroTasks.Infinate == (ulDelay & ~MicroTasks.WaitForMask)) {
        oTask->ulNextLoop = 0xFFFFFFFF;
      } else {
        oTask->ulNextLoop += (ulDelay & ~MicroTasks.WaitForMask);
      }
    }
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

MicroTasksClass MicroTasks;


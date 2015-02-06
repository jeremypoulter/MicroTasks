// 
// 
// 

#include "Task.h"
#include "MicroTasks.h"

MicroTasksClass::MicroTasksClass()
{
  oFirstTask = NULL;
  oLastTask = NULL;
}

void MicroTasksClass::init()
{


}

void MicroTasksClass::update()
{
  Task *oNext;

  for (Task *oTask = oFirstTask; oTask; oTask = oNext)
  {
    // Keep a pointer to the next task in case this on is stopped
    oNext = oTask->oNext;

    if (oTask->ulNextLoop <= millis())
    {
      unsigned long ulDelay = oTask->loop(WakeReason_Scheduled);
      oTask->ulNextLoop += ulDelay;
    }
  }
}

void MicroTasksClass::startTask(Task *oTask)
{
  if (oLastTask) {
    oLastTask->oNext = oTask;
  }
  oTask->oPrev = oLastTask;
  oLastTask = oTask;
  if (NULL == oFirstTask)
  {
    oFirstTask = oTask;
  }

  oTask->setup();
}

void MicroTasksClass::stopTask(Task *oTask)
{
  if (oTask->oPrev)
  {
    oTask->oPrev->oNext = oTask->oNext;
  }
  if (oTask->oNext)
  {
    oTask->oNext->oPrev = oTask->oPrev;
  }
  if (oFirstTask == oTask) {
    oFirstTask = oTask->oNext;
  }
  if (oLastTask == oTask)
  {
    oLastTask = oTask->oPrev;
  }
}

MicroTasksClass MicroTasks;


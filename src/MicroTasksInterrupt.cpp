//
//
//

#include "MicroTasksInterrupt.h"

using namespace MicroTasks;

Interrupt *interrupts[MICROTASKS_MAX_INTERUPTS] = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};

InterruptCallback Interrupt::Triggers[MICROTASKS_MAX_INTERUPTS] = {
  Interrupt::TriggerInt0,
  Interrupt::TriggerInt1,
  Interrupt::TriggerInt2,
  Interrupt::TriggerInt3,
  Interrupt::TriggerInt4
};

bool Interrupt::Attach()
{
  for(int i = 0; i < MICROTASKS_MAX_INTERUPTS; i++)
  {
    if (NULL == interrupts[i])
    {
      index = i;
      pinMode(pin, inputMode);
      attachInterrupt(digitalPinToInterrupt(pin), Triggers[index], mode);
      interrupts[index] = this;
      return true;
    }
  }

  return false;
}

void Interrupt::Dettach()
{
  detachInterrupt(digitalPinToInterrupt(pin));
  interrupts[index] = NULL;
}

#define INTERRUPT_CALLBACK(intNum)  \
void Interrupt::TriggerInt ## intNum () \
{ \
  interrupts[intNum]->Trigger(); \
}

INTERRUPT_CALLBACK(0);
INTERRUPT_CALLBACK(1);
INTERRUPT_CALLBACK(2);
INTERRUPT_CALLBACK(3);
INTERRUPT_CALLBACK(4);

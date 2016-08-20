//
//
//

#include "MicroTasks/Interrupt.h"

Interrupt *interrupts[] = {
  NULL,
  NULL
};

uint8_t pins[] = {
  2, 3
};

InterruptCallback Interrupt::Triggers[] = {
  Interrupt::TriggerInt0,
  Interrupt::TriggerInt1
};

bool Interrupt::Attach()
{
  if (NULL == interrupts[interrupt])
  {
    pinMode(pins[interrupt], INPUT);
    attachInterrupt(interrupt, Triggers[interrupt], mode);
    interrupts[interrupt] = this;
    return true;
  }

  return false;
}

void Interrupt::Dettach()
{
  detachInterrupt(interrupt);
  interrupts[interrupt] = NULL;
}

#define INTERRUPT_CALLBACK(intNum)  \
void Interrupt::TriggerInt ## intNum () \
{ \
  interrupts[intNum]->Trigger(); \
}

INTERRUPT_CALLBACK(0);
INTERRUPT_CALLBACK(1);

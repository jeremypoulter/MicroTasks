/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#include "MicroTasks.h"
#include "MicroTasksTask.h"
#include "MicroTasksInterrupt.h"
#include "MicroTasksEventListener.h"

using namespace MicroTasks;

class Blink : public Task
{
  private:
    int state;
    int pin;
    int delay;

  public:
    Blink(int pin, int delay = 1000);
    void setup();
    unsigned long loop(WakeReason reason);
};

Blink::Blink(int pin, int delay) :
  Task(), state(LOW), pin(pin), delay(delay)
{
}

void Blink::setup()
{
  // initialize the digital pin as an output.
  pinMode(pin, OUTPUT);
}

unsigned long Blink::loop(WakeReason reason)
{
  // Update the LED
  digitalWrite(pin, state);

  // Update the state
  state = LOW == state ? HIGH : LOW;

  // return when we next want to be called
  return delay;
}

Blink blink1 = Blink(10, 125);
Blink blink2 = Blink(11, 250);
Blink blink3 = Blink(12, 500);

Interrupt buttonEvent(2, FALLING);

class BlinkOnButton : public Task
{
  private:
    int state;
    int pin;
    EventListener buttonEventListener;

  public:
    BlinkOnButton(int pin);

    void setup();
    unsigned long loop(WakeReason reason);
};

BlinkOnButton::BlinkOnButton(int pin) :
  state(LOW), pin(pin), buttonEventListener(this), Task()
{
}

void BlinkOnButton::setup()
{
  // initialize the digital pin as an output.
  pinMode(pin, OUTPUT);
  buttonEvent.Register(&buttonEventListener);
}

unsigned long BlinkOnButton::loop(WakeReason reason)
{
  if (WakeReason_Event == reason &&  buttonEvent.IsTriggered())
  {
    // Update the LED
    digitalWrite(pin, state);

    // Update the state
    state = LOW == state ? HIGH : LOW;
  }

  // return when we next want to be called
  return MicroTask.Infinate | MicroTask.WaitForEvent;
}

BlinkOnButton blinkOnButton1 = BlinkOnButton(13);
BlinkOnButton blinkOnButton2 = BlinkOnButton(9);

// the setup function runs once when you press reset or power the board
void setup() {
  MicroTask.startTask(blink1);
  MicroTask.startTask(blink2);
  MicroTask.startTask(blink3);
  MicroTask.startTask(blinkOnButton1);
  MicroTask.startTask(blinkOnButton2);

  buttonEvent.Attach();
}

// the loop function runs over and over again forever
void loop() {
  MicroTask.update();
}

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

using namespace MicroTasks;

class Blink : public Task
{
  private:
    int state;
    int pin;
    int delay;

  public:
    Blink(int pin, int delay = 1000)
    {
      this->state = LOW;
      this->pin = pin;
      this->delay = delay;
    }
    void setup();
    unsigned long loop(WakeReason reason);
};

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

class RandomBlink : public Task
{
  private:
    int state;
    int pin;

  public:
    RandomBlink(int pin)
    {
      this->state = LOW;
      this->pin = pin;
    }
    void setup();
    unsigned long loop(WakeReason reason);
};

void RandomBlink::setup()
{
  // initialize the digital pin as an output.
  pinMode(pin, OUTPUT);
}

unsigned long RandomBlink::loop(WakeReason reason)
{
  // Update the LED
  digitalWrite(pin, state);

  // Update the state
  state = LOW == state ? HIGH : LOW;

  // return when we next want to be called
  return random(1000);
}

Blink blink1 = Blink(9, 125);
Blink blink2 = Blink(10, 250);
Blink blink3 = Blink(11, 500);
Blink blink4 = Blink(12, 1000);
RandomBlink randomBlink = RandomBlink(13);

// the setup function runs once when you press reset or power the board
void setup() {
  MicroTask.startTask(blink1);
  MicroTask.startTask(blink2);
  MicroTask.startTask(blink3);
  MicroTask.startTask(blink4);
  MicroTask.startTask(randomBlink);
}

// the loop function runs over and over again forever
void loop() {
  MicroTask.update();
}

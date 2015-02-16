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

#include "MicroTasks\MicroTasks.h"
#include "MicroTasks\Task.h"
#include "MicroTasks\Interrupt.h"
#include "MicroTasks\EventListener.h"

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
  Serial.println("Blink::loop");
  Serial.println((unsigned long)this);

  // Update the LED
  Serial.println(state);
  digitalWrite(pin, state);
  
  // Update the state
  state = LOW == state ? HIGH : LOW;
  Serial.println(state);

  // return when we next want to be called
  return delay;
}

Blink blink1 = Blink(10, 125);
Blink blink2 = Blink(11, 250);
Blink blink3 = Blink(12, 500);

Interrupt buttonEvent(0, RISING);

class BlinkOnButton : public Task
{
  private:
    int state;
    int pin;
    EventListener buttonEventListener;

  public:
    BlinkOnButton(int pin) : 
      state(LOW), pin(pin), buttonEventListener(this)
    {
    }

    void setup();
    unsigned long loop(WakeReason reason);
};

void BlinkOnButton::setup()
{
  // initialize the digital pin as an output.
  pinMode(pin, OUTPUT);
  buttonEvent.Register(&buttonEventListener);
}

unsigned long BlinkOnButton::loop(WakeReason reason)
{
  Serial.println("BlinkOnButton::loop");
  Serial.println((unsigned long)this);

  /* if (WakeReason_Event == reason &&  buttonEvent.IsTriggered()) */
  {
    // Update the LED
    Serial.println(state);
    digitalWrite(pin, state);

    // Update the state
    state = LOW == state ? HIGH : LOW;
    Serial.println(state);
  }

  // return when we next want to be called
  return MicroTasks.Infinate | MicroTasks.WaitForEvent;
}

BlinkOnButton blinkOnButton1 = BlinkOnButton(13);
BlinkOnButton blinkOnButton2 = BlinkOnButton(9);

// the setup function runs once when you press reset or power the board
void setup() {
//  MicroTasks.startTask(&blink1);
//  MicroTasks.startTask(&blink2);
  MicroTasks.startTask(&blink3);
  MicroTasks.startTask(&blinkOnButton1);
  MicroTasks.startTask(&blinkOnButton2);

  buttonEvent.Attach();

  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  MicroTasks.update();
}

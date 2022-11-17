/*
  Alarm
  Turns on an LED on for one second, then off for one second, repeatedly, 
  but using the Alarm API.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#include "MicroTasks.h"
#include "MicroTasksAlarm.h"

using namespace MicroTasks;

class Blink : public Alarm
{
  private:
    int state;
    int pin;

  public:
    Blink(int pin) : 
      state(LOW),
      pin(pin)
    {
    }

    void Trigger() 
    {
      // Update the LED
      digitalWrite(pin, state);

      // Update the state
      state = LOW == state ? HIGH : LOW;
    }
};

Blink blinkAlarm = Blink(LED_BUILTIN);

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize the digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  blinkAlarm.Set(350, true);
}

// the loop function runs over and over again forever
void loop() {
  MicroTask.update();
}

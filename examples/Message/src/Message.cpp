/*
  Message
  Turns on an LED on for one second, then off for one second, repeatedly, 
  but using the Message API.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

 */

#include "MicroTasks.h"
#include "MicroTasksMessage.h"

using namespace MicroTasks;

class HelloMessage : public MessageBase<1>
{
  protected:
    virtual void receive() {
      Serial.println("Received Hello");
      digitalWrite(LED_BUILTIN, LOW);
    }
};


class WorldMessage : public MessageBase<2>
{
  protected:
    virtual void receive() {
      Serial.println("Received World");
      digitalWrite(LED_BUILTIN, HIGH);
    }
};

class OtherMessage : public MessageBase<3> {};

class ReceiveMessageTask : public Task
{
  public:
    ReceiveMessageTask();
    void setup();
    unsigned long loop(WakeReason reason);
};

ReceiveMessageTask::ReceiveMessageTask() :
  Task()
{
}

void ReceiveMessageTask::setup()
{
}

unsigned long ReceiveMessageTask::loop(WakeReason reason)
{
  Serial.print("ReceiveMessageTask woke: ");
  Serial.println(WakeReason_Scheduled == reason ? "WakeReason_Scheduled" :
                 WakeReason_Event == reason ? "WakeReason_Event" :
                 WakeReason_Message == reason ? "WakeReason_Message" :
                 WakeReason_Manual == reason ? "WakeReason_Manual" :
                 "UNKNOWN");

  if(WakeReason_Message == reason)
  {
    Message *msg;
    if(this->receive(msg))
    {
      Serial.print("Got message ");
      Serial.println(
        HelloMessage::ID == msg->id() ? "HelloMessage" :
        WorldMessage::ID == msg->id() ? "WorldMessage" :
        "UNKNOWN"
      );
      delete msg;
    }
  }

  return MicroTask.Infinate | MicroTask.WaitForMessage;
}

ReceiveMessageTask receiver;

class SendMessageTask : public Task
{
  private:
    int state;

  public:
    SendMessageTask();
    void setup();
    unsigned long loop(WakeReason reason);
};

SendMessageTask::SendMessageTask() :
  Task(), state(0)
{
}

void SendMessageTask::setup()
{
}

unsigned long SendMessageTask::loop(WakeReason reason)
{
  Serial.print("SendMessageTask woke: ");
  Serial.println(WakeReason_Scheduled == reason ? "WakeReason_Scheduled" :
                 WakeReason_Event == reason ? "WakeReason_Event" :
                 WakeReason_Message == reason ? "WakeReason_Message" :
                 WakeReason_Manual == reason ? "WakeReason_Manual" :
                 "UNKNOWN");

  Message *msg = (state++ % 2 )? 
      (Message *)(new HelloMessage()) :
      (Message *)(new WorldMessage());

  receiver.send(msg);

  return 1000;
}

SendMessageTask sender;

// the setup function runs once when you press reset or power the board
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  MicroTask.startTask(receiver);
  MicroTask.startTask(sender);
}

// the loop function runs over and over again forever
void loop() {
  MicroTask.update();
}

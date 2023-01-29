/*
  Message
  Turns on an LED on for one second, then off for one second, repeatedly, 
  but using the Message API.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

 */

#ifdef NRF52
#include "Adafruit_TinyUSB.h"s
#endif

#include "MicroTasks.h"
#include "MicroTasksMessage.h"

using namespace MicroTasks;

class HelloMessage : public Message
{
  protected:
    virtual void receive() {
      Serial.println("Received Hello");
      digitalWrite(LED_BUILTIN, LOW);
    }

  public: 
    static const uint32_t ID = 0;
    HelloMessage() : Message(ID) {}
};


class WorldMessage : public Message
{
  private:
    uint32_t _state;

  protected:
    virtual void receive() {
      Serial.println("Received World");
      digitalWrite(LED_BUILTIN, HIGH);
    }

  public: 
    static const uint32_t ID = 1;
    WorldMessage(uint32_t state) :
      Message(ID), _state(state) {}

    uint32_t getState() {
      return _state;
    }
};

class OtherMessage : public Message {
  public: 
    static const uint32_t ID = 2;
    OtherMessage() : Message(ID) {}
};

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
      if (WorldMessage::ID == msg->id())
      {
        WorldMessage *world = static_cast<WorldMessage *>(msg);
        Serial.print("state = ");
        Serial.println(world->getState());
      }
      
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
      static_cast<Message *>(new HelloMessage()) :
      static_cast<Message *>(new WorldMessage(state));

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

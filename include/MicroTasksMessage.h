// Message.h

#ifndef _MESSAGE_h
#define _MESSAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MicroTasksNode.h"
#include "MicroTasksTask.h"

namespace MicroTasks
{
  class Message : public Node
  {
    friend class Task;

    uint32_t _id;

  protected:
    virtual void receive() {
    }

  public:
    Message(uint32_t id) : 
      Node(), _id(id) { }

    uint32_t id() {
      return _id;
    }
  };
}


#endif


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
  template <uint32_t TYPE = 0>
  class MessageBase : public Node
  {
    friend class Task;

  protected:
    virtual void receive() {
    }

  public:
    MessageBase() : Node() {
    }
    ~MessageBase() {
    }

    static const uint32_t ID = TYPE;
    virtual uint32_t id() { return ID; }
  };
  
  typedef class MessageBase<> Message;
}


#endif


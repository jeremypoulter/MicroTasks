// List.h

#ifndef _LIST_h
#define _LIST_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MicroTasksNode.h"

namespace MicroTasks
{
  class List
  {
  private:
    Node *oFirst;
    Node *oLast;

  public:
    List();

    void Add(Node *oNode);
    void Remove(Node *oNode);

    Node *GetFirst() {
      return oFirst;
    }
    Node *GetLast() {
      return oLast;
    }
  };
}

#endif


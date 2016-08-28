// Node.h

#ifndef _NODE_H
#define _NODE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

namespace MicroTasks
{
  class Node;
  class List;

  class Node
  {
    friend List;

  private:
    Node *oPrev;
    Node *oNext;
    List *oList;

  protected:

  public:
    Node();
    virtual ~Node();

    Node *GetNext() {
      return oNext;
    }
    Node *GetPrev() {
      return oPrev;
    }
  };
}

#endif

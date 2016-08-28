#include "MicroTasks_Node.h"
#include "MicroTasks_List.h"

Node::Node()
{
  oNext = NULL;
  oPrev = NULL;
  oList = NULL;
}


Node::~Node()
{
  if (oNext || oPrev)
    oList->Remove(this);
}

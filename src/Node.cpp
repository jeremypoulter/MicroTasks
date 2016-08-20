#include "MicroTasks/Node.h"
#include "MicroTasks/List.h"

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

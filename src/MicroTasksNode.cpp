#include "MicroTasksNode.h"
#include "MicroTasksList.h"

using namespace MicroTasks;

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

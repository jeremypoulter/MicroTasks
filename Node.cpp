#include "Node.h"
#include "List.h"

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

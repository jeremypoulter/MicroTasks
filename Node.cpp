#include "Node.h"
#include "List.h"

Node::Node()
{
  oNext = NULL;
  oPrev = NULL;
}


Node::~Node()
{
  if (oNext || oPrev)
    oList->Remove(this);
}

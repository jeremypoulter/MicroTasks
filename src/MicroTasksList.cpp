//
//
//

#include "MicroTasksList.h"

using namespace MicroTasks;

List::List()
{
  oFirst = NULL;
  oLast = NULL;
}

void List::Add(Node *oNode)
{
  if (oLast) {
    oLast->oNext = oNode;
  }
  oNode->oPrev = oLast;
  oLast = oNode;
  if (NULL == oFirst)
  {
    oFirst = oNode;
  }
  oNode->oList = this;
}

void List::Remove(Node *oNode)
{
  if (oNode->oPrev)
  {
    oNode->oPrev->oNext = oNode->oNext;
  }
  if (oNode->oNext)
  {
    oNode->oNext->oPrev = oNode->oPrev;
  }
  if (oFirst == oNode) {
    oFirst = oNode->oNext;
  }
  if (oLast == oNode)
  {
    oLast = oNode->oPrev;
  }

  oNode->oNext = NULL;
  oNode->oPrev = NULL;
  oNode->oList = NULL;
}

bool List::Contains(Node *oNode)
{
  for(Node *n = oFirst; n; n = n->oNext) {
    if(oNode == n) {
      return true;
    }
  }

  return false;
}
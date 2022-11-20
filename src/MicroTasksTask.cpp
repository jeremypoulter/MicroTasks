//
//
//

#include "MicroTasksTask.h"

using namespace MicroTasks;

uint32_t Task::Wake = (1 << 0);

Task::Task() :
  Node(), ulNextLoop(millis()), uiFlags(0), oMessages()
{
}

Task::~Task()
{

}

bool Task::receive(Message *&msg)
{
  Node *node = oMessages.GetFirst();
  if(node) {
    oMessages.Remove(node);
    msg = static_cast<Message *>(node);
    msg->receive();
    return true;
  }

  return false;
}

void Task::send(Message *msg)
{
  oMessages.Add(msg);
}
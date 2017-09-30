//
//
//

#include "MicroTasksTask.h"

using namespace MicroTasks;

Task::Task() :
  Node(), ulNextLoop(millis()), uiFlags(0)
{
}

Task::~Task()
{

}

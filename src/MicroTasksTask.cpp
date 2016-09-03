//
//
//

#include "MicroTasksTask.h"

using namespace MicroTasks;

Task::Task() :
  ulNextLoop(millis()), uiFlags(0), Node()
{
}

Task::~Task()
{

}

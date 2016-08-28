//
//
//

#include "MicroTasksTask.h"

MicroTasks::Task::Task() :
  ulNextLoop(millis()), uiFlags(0), Node()
{
}

MicroTasks::Task::~Task()
{

}

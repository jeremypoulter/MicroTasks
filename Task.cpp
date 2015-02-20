// 
// 
// 

#include "Task.h"

Task::Task() : 
  ulNextLoop(millis()), uiFlags(0), Node()
{
}

Task::~Task()
{

}
// 
// 
// 

#include "Task.h"

Task::Task()
{
  oNext = NULL;
  oPrev = NULL;
  ulNextLoop = millis();
}

Task::~Task()
{

}
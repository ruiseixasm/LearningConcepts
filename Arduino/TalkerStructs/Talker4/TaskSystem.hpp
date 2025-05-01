#ifndef TASK_SYSTEM_HPP
#define TASK_SYSTEM_HPP

#include <Arduino.h>

// Structure Definition
struct TaskScheduler {
  void (*tasks[5])();          // Function pointer array (no args)
  void (*paramTasks[5])(int);  // Function pointer array (with int arg)
  uint8_t taskCount = 0;       // Using fixed-width type for Arduino
  uint8_t paramTaskCount = 0;
  
  // Helper method to add a task
  bool addTask(void (*task)()) {
    if (taskCount >= 5) return false;
    tasks[taskCount++] = task;
    return true;
  }
  
  // Helper method to add a parameterized task
  bool addParamTask(void (*task)(int)) {
    if (paramTaskCount >= 5) return false;
    paramTasks[paramTaskCount++] = task;
    return true;
  }
};

// Class Implementation
class TaskExecutor {
public:
  explicit TaskExecutor(const TaskScheduler& scheduler) 
    : scheduler_(scheduler) {}

  void execute() const {
    for (uint8_t i = 0; i < scheduler_.taskCount; ++i) {
      if (scheduler_.tasks[i]) scheduler_.tasks[i]();
    }
  }

  void executeWith(int value) const {
    for (uint8_t i = 0; i < scheduler_.paramTaskCount; ++i) {
      if (scheduler_.paramTasks[i]) scheduler_.paramTasks[i](value);
    }
  }

private:
  const TaskScheduler& scheduler_;
};

#endif

#include "TaskSystem.hpp"

// Function prototypes
void blinkLED() {
  static bool state = false;
  digitalWrite(LED_BUILTIN, state);
  state = !state;
  Serial.println(state ? "LED ON" : "LED OFF");
}

void printAnswer() {
  Serial.println("42");
}

void logNumber(int n) {
  Serial.print("Log: "); Serial.println(n);
}

TaskExecutor* executor = nullptr;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize scheduler
  static TaskScheduler scheduler;
  scheduler.addTask(blinkLED);
  scheduler.addTask(printAnswer);
  scheduler.addParamTask(logNumber);

  // Create executor
  executor = new TaskExecutor(scheduler);

  // Run tasks
  executor->execute();
  executor->executeWith(100);
}

void loop() {
  static uint32_t last = 0;
  if (millis() - last >= 1000) {
    executor->execute();
    executor->executeWith(millis() / 1000);
    last = millis();
  }
}

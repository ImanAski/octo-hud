#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>
#include "Time.h"

namespace pico_hud {
struct Task {
  uint32_t id;
  std::function<void()> func;
  uint32_t interval_ms;
  uint32_t last_run_ms;
  bool enabled;

  Task(uint32_t id, std::function<void()> func, uint32_t interval)
      : id(id), func(func), interval_ms(interval), last_run_ms(0), enabled(true) {}
};

class Scheduler {
public:
  Scheduler() : next_task_id(0) {}

  uint32_t addTask(std::function<void()> func, uint32_t interval_ms) {
    if (tasks.size() >= MAX_TASKS) {
      return 0;
    }

    uint32_t new_id = ++next_task_id;
    tasks.emplace_back(new_id, func, interval_ms);
    return new_id;
  }

  bool removeTask(uint32_t id) {
    auto it = std::remove_if(tasks.begin(), tasks.end(),
                             [id](const Task &t) { return t.id == id; });
    if (it != tasks.end()) {
      tasks.erase(it, tasks.end());
      return true;
    }

    return false;
  }

  bool setTaskEnabled(uint32_t id, bool enabled) {
    for (auto &task : tasks) {
      if (task.id == id) {
        task.enabled = enabled;
        return true;
      }
    }
    return false;
  }

  void run() {
    uint32_t current_ms = Time::millis();
    for (auto &task : tasks) {
      if (task.enabled) {
        if (current_ms - task.last_run_ms >= task.interval_ms) {
          task.func();
          task.last_run_ms = current_ms;
        }
      }
    }
  }

private:
  std::vector<Task> tasks;
  uint32_t next_task_id;
  static constexpr size_t MAX_TASKS = 32;
};
} // namespace pico_hud

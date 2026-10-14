#include "engine_telemetry.hpp"

void EngineTelemetry::record_task_submitted() noexcept {
  tasks_submitted_.fetch_add(1, std::memory_order_relaxed);
}

void EngineTelemetry::record_task_started() noexcept {
  active_workers_.fetch_add(1, std::memory_order_relaxed);
}

void EngineTelemetry::record_task_completed() noexcept {
  tasks_completed_.fetch_add(1, std::memory_order_relaxed);
  active_workers_.fetch_sub(1, std::memory_order_relaxed);
}

uint32_t EngineTelemetry::get_active_workers() const noexcept {
  return active_workers_.load(std::memory_order_relaxed);
}

uint64_t EngineTelemetry::get_submitted_count() const noexcept {
  return tasks_submitted_.load(std::memory_order_relaxed);
}

uint64_t EngineTelemetry::get_completed_count() const noexcept {
  return tasks_completed_.load(std::memory_order_relaxed);
}

void EngineTelemetry::reset() noexcept {
  active_workers_.store(0, std::memory_order_relaxed);
  tasks_submitted_.store(0, std::memory_order_relaxed);
  tasks_completed_.store(0, std::memory_order_relaxed);
}

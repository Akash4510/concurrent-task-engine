#pragma once

#include <atomic>
#include <cstdint>

class EngineTelemetry {
public:
  EngineTelemetry() = default;
  ~EngineTelemetry() = default;

  EngineTelemetry(const EngineTelemetry&) = delete;
  EngineTelemetry& operator=(const EngineTelemetry&) = delete;
  EngineTelemetry(EngineTelemetry&&) = delete;
  EngineTelemetry& operator=(EngineTelemetry&&) = delete;

  void record_task_submitted() noexcept;
  void record_task_started() noexcept;
  void record_task_completed() noexcept;

  uint32_t get_active_workers() const noexcept;
  uint64_t get_submitted_count() const noexcept;
  uint64_t get_completed_count() const noexcept;

  void reset() noexcept;

private:
  std::atomic<uint64_t> tasks_submitted_{ 0 };
  std::atomic<uint64_t> tasks_completed_{ 0 };
  std::atomic<uint32_t> active_workers_{ 0 };
};

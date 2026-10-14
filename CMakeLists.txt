cmake_minimum_required(VERSION 3.16)
project(concurrent_task_engine VERSION 1.0.0 LANGUAGES CXX)

# Enforce Modern C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable compiler warnings for code hygiene
add_compile_options(-Wall -Wextra -pedantic)

# Find OS threading support (pthread on Linux/macOS)
find_package(Threads REQUIRED)

# Expose the include directory so files can use #include "ThreadSafeQueue.hpp"
include_directories(include)

# Define our library / engine from its implementation translation units
add_library(task_engine_lib
    src/engine_telemetry.cpp
    src/worker_pool.cpp
)

# Link the threading library to our engine
target_link_libraries(task_engine_lib PUBLIC Threads::Threads)

# Build the main executable driver
add_executable(concurrent_task_engine src/main.cpp)

# Link the engine library to the executable
target_link_libraries(concurrent_task_engine PRIVATE task_engine_lib)

cmake_minimum_required(VERSION 3.18)

project(
  x13_egpu
  VERSION 0.1.0
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(LEVEL_DEBUG ON CACHE STRING "log_level" FORCE)
set(SYS_LOG_ENABLED ON CACHE STRING "sys_log_enabled" FORCE)
add_subdirectory(src/lib)
add_subdirectory(src/server)
add_subdirectory(src/client)

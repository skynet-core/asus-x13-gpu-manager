cmake_minimum_required(VERSION 3.18)

project(
  x13_egpu
  VERSION 0.1.0
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(LEVEL_DEBUG ON CACHE STRING "log_level" FORCE)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/conan_toolchain.cmake")
  include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/conan_toolchain.cmake")
endif()

find_package(fmt CONFIG REQUIRED)
find_package(sdbus-cpp CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(Poco CONFIG REQUIRED COMPONENTS Data)
find_package(kmod CONFIG REQUIRED)

add_custom_target(
  service_gen
  COMMAND
    sdbus-c++-xml2cpp ${CMAKE_CURRENT_SOURCE_DIR}/share/interfaces/interface.xml
    --adaptor=${CMAKE_CURRENT_SOURCE_DIR}/src/server/asus-manager-adapter-glue.h
    --proxy=${CMAKE_CURRENT_SOURCE_DIR}/src/client/asus-manager-proxy-glue.h
  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/share/interfaces/interface.xml)

add_custom_target(
  systemd_gen
  COMMAND
    sdbus-c++-xml2cpp ${CMAKE_CURRENT_SOURCE_DIR}/share/interfaces/systemd.xml
    --proxy=${CMAKE_CURRENT_SOURCE_DIR}/src/lib/systemd-manager-proxy-glue.h
  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/share/interfaces/systemd.xml)

add_subdirectory(src/lib)
add_subdirectory(src/server)
add_subdirectory(src/client)
